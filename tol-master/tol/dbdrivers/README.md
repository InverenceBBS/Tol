# TOL Database Drivers (`tol-master/tol/dbdrivers/`)

## Overview

This directory contains the source code for database drivers that allow the TOL language to connect to and interact with various external database systems.

## Code Functionality

- **Specific Database Drivers (`libtol*.c`):** C source files implementing connectivity for:
    - MySQL (`libtolmysql.c`)
    - PostgreSQL (`libtolpgsql.c`)
    - SQLite (`libtolsqlite.c`, uses embedded source from `sqlite/`)
    - ODBC (`libtolodbc.c`) - Provides generic connectivity to databases via ODBC drivers.
    - Potentially Berkeley DB (`libtolbdb.h`, implementation source unclear).
    These drivers likely wrap the native C APIs provided by the respective database client libraries.

    **ODBC Driver Details (`libtolodbc.c`):**
    *   **Connection:** Uses standard ODBC functions (`SQLAllocHandle`, `SQLSetEnvAttr`, `SQLConnect`) invoked via the TOL `DBOpen(dsn, user, pwd)` function. Requires a pre-configured ODBC Data Source Name (DSN) corresponding to the `dsn` parameter. Connection context is managed in the `odbcd` struct. Metadata (DBMS name/version, database name) can be retrieved using `SQLGetInfo`. The connection is closed via `DBClose(dsn)`, which calls `SQLDisconnect` and `SQLFreeHandle`.
    *   **Query Execution (No Results):** The TOL `DBExecQuery(sql)` function uses `SQLExecDirect` via the internal `odbc_ExecQuery` C function for statements like INSERT, UPDATE, DELETE. It retrieves the affected row count using `SQLRowCount` and immediately frees the statement handle.
    *   **Query Execution (With Results):** The TOL `DBTable(sql)` function (and potentially others) uses `SQLExecDirect` via `odbc_OpenQuery` to execute SELECT statements, leaving the statement handle open.
    *   **Result Handling:**
        *   Metadata (column count, names, types) is retrieved using `SQLNumResultCols` and `SQLDescribeCol` (`odbc_GetFieldsNumber`, `odbc_GetFieldName`, `odbc_GetFieldType`). Native SQL types are mapped to basic TOL types (Real, Text, Date).
        *   Rows are fetched iteratively using `SQLFetch` (`odbc_GetNext`).
        *   Data for each column in the current row is retrieved using `SQLGetData` via helper functions: `odbc_GetAsReal` (for numeric types), `odbc_GetAsDate` (for date/time types), and `odbc_GetAsText` (for character types).
        *   `odbc_GetAsText` includes logic to handle potentially large text/LOB data by fetching it in chunks (`ChunkOfTextType` helper).
        *   The statement handle is explicitly closed after fetching (likely within `DBTable`) using `odbc_CloseQuery`.
    *   **Error Handling:** Uses `SQLGetDiagRec` internally to retrieve diagnostic information, which is passed to a TOL-registered callback function (`stdOutWriter` set by `odbc_PutHCIWriter`).

    **SQLite Driver Details (`libtolsqlite.c`):**
    *   **Core:** Uses the embedded SQLite3 engine source from the `sqlite/` subdirectory.
    *   **Connection:** Opens a database file using `sqlite3_open_v2` invoked via `DBOpen(filepath, user, pwd)`. User/password/host are ignored. Context is stored in the `sqlited` struct. Connection closed via `DBClose(filepath)` which calls `sqlite3_close_v2`.
    *   **Query Execution (No Results):** `DBExecQuery(sql)` uses `sqlite3_exec` for non-SELECT statements. Retrieves affected rows via `sqlite3_changes`.
    *   **Query Execution (With Results):** `DBTable(sql)` likely uses `sqlite3_prepare_v2` (`sqlite_OpenQuery`) to prepare SELECT statements.
    *   **Result Handling:**
        *   Metadata (column count, names, types) retrieved using `sqlite3_column_count`, `sqlite3_column_name`, `sqlite3_column_type`. SQLite types (`INTEGER`, `FLOAT`, `TEXT`, `BLOB`, `NULL`) mapped to basic TOL types (Real, Text, Unknown).
        *   Rows fetched iteratively using `sqlite3_step` (`sqlite_GetNext`).
        *   Data retrieved using `sqlite3_column_*` functions: `sqlite3_column_double` (`sqlite_GetAsReal`), `sqlite3_column_text` (`sqlite_GetAsText`), and type-dependent logic for `sqlite_GetAsDate` (parsing text or Julian Day numbers).
        *   Prepared statements finalized using `sqlite3_finalize` (`sqlite_CloseQuery`).
    *   **Error Handling:** Uses `sqlite3_errmsg` to get error strings, passed to TOL via `stdOutWriter` callback (set by `sqlite_PutHCIWriter`).

    **PostgreSQL Driver Details (`libtolpgsql.c`):**
    *   **Core:** Uses the `libpq` C library to connect to PostgreSQL.
    *   **Connection:** Connects using `PQconnectdbParams` invoked via `DBOpen(dbname, user, pwd, host, port)`. Context stored in `pgsqld` struct (`PGconn` handle). Closed via `DBClose(...)` which calls `PQfinish`.
    *   **Query Execution (No Results):** `DBExecQuery(sql)` uses `PQexec` (`postgres_OpenQuery`), checks status (`PGRES_COMMAND_OK`), gets affected rows via `PQcmdTuples`, and clears the result (`postgres_CloseQuery`).
    *   **Query Execution (With Results):** `DBTable(sql)` likely uses `PQexec` (`postgres_OpenQuery`). Caches the `PGresult` handle and tuple count (`PQntuples`).
    *   **Result Handling:**
        *   Metadata (column count, names, types) retrieved from `PGresult` using `PQnfields`, `PQfname`, `PQftype`. PostgreSQL OIDs mapped to basic TOL types (Real, Text, Date).
        *   Row iteration managed internally by incrementing a counter (`postgres_GetNext`).
        *   Data retrieved *directly* from the cached `PGresult` using `PQgetvalue(result, row_index, col_index)` based on the current internal row counter. Handles NULLs via `PQgetisnull`.
        *   `postgres_GetAsReal` uses `sscanf` on the string value. `postgres_GetAsText` copies the string value. `postgres_GetAsDate` parses the string value.
        *   Result cleared using `PQclear` (`postgres_CloseQuery`).
    *   **Error Handling:** Uses `PQerrorMessage` / `PQresultErrorMessage` passed to `stdOutWriter` callback (set by `postgres_PutHCIWriter`).

    **MySQL Driver Details (`libtolmysql.c`):**
    *   **Core:** Uses the `libmysqlclient` C library.
    *   **Connection:** Connects using `mysql_real_connect` invoked via `DBOpen(database, user, pwd, host)`. Context stored in `mysqld` struct (`MYSQL` handle). Closed via `DBClose(...)` which calls `mysql_close`.
    *   **Query Execution (No Results):** `DBExecQuery(sql)` uses `mysql_real_query` (`mysql_OpenQuery`), tries `mysql_store_result`, checks `mysql_field_count`, and gets affected rows via `mysql_affected_rows`. Frees result immediately if applicable.
    *   **Query Execution (With Results):** `DBTable(sql)` likely uses `mysql_real_query` (`mysql_OpenQuery`). Result set handling is initiated later by `mysql_GetFirst`.
    *   **Result Handling:**
        *   `mysql_GetFirst` calls `mysql_use_result` (unbuffered) to start retrieval and fetches the first row via `mysql_GetNext`.
        *   Metadata (column count, names, types) retrieved using `mysql_num_fields` (from result) and `mysql_fetch_field_direct`. MySQL types mapped to basic TOL types (Real, Text, Date).
        *   Rows fetched iteratively using `mysql_fetch_row` (`mysql_GetNext`), which returns a `MYSQL_ROW` (array of strings).
        *   Data retrieved directly from the most recent `MYSQL_ROW`. `mysql_GetAsReal` uses `sscanf`. `mysql_GetAsText` copies the string. `mysql_GetAsDate` parses the string.
        *   Result set freed using `mysql_free_result` (`mysql_CloseQuery`).
    *   **Error Handling:** Uses `mysql_error` passed to `stdOutWriter` callback (set by `mysql_PutHCIWriter`).
- **Embedded SQLite (`sqlite/`):** Contains the source code of the SQLite database engine, allowing direct linking for the SQLite driver without an external dependency.
- **Build System (`CMakeLists.txt`, `Jamfile`, `Makefile.am`, `configure.in`):** Configures the build process for the drivers. This involves:
    - Detecting required database client libraries (MySQL, PostgreSQL, ODBC).
    - Compiling the C driver code.
    - Likely building each driver as a separate shared library/plugin (e.g., `tolmysql.so`, `tolodbc.dll`) loadable by the main TOL interpreter (using the `LoadDynLib` component).
- **Utilities (`listDRV.c`, `listDSN.c`):** Small command-line tools potentially used to list detected drivers or configured ODBC data sources.
- **Testing (`tests/`, `testOCnn.c`):** Includes tests to verify database driver functionality.

## Purpose

This component provides database connectivity as a feature within the TOL language. It allows TOL scripts to:
- Establish connections to different SQL databases.
- Execute SQL queries (SELECT, INSERT, UPDATE, DELETE, etc.).
- Fetch results from queries into TOL data structures (e.g., matrices, sets).
- Potentially perform database metadata operations.

## Appendix

- **Implementation Language:** C.
- **Dependencies:** Requires client libraries for MySQL, PostgreSQL, and ODBC to build the respective drivers. SQLite is included.
- **Build:** Drivers are likely compiled as optional, dynamically loadable modules/plugins. 