# TOL Database Connectivity Tests (`tol-master/tol_tests/toldb/`)

## Overview

This directory contains test scripts (`.tol` files) and supporting files designed to verify the functionality of TOL's database connectivity drivers (implemented in `tol-master/tol/dbdrivers/`).

## Contents

- **`_tolTester.tol`:** The main TOL script used to execute the database tests in this directory.
- **`by_engine/`:** A subdirectory likely containing specific `.tol` test scripts organized by the database engine being tested (e.g., subdirectories or files named `mysql`, `pgsql`, `odbc`, `sqlite`). These scripts would test:
    - Establishing connections.
    - Executing various SQL commands (SELECT, INSERT, UPDATE, DELETE).
    - Handling data type conversions between TOL and SQL.
    - Querying database metadata.
- **`dbt.engine.type.bst`:** A supporting data file, possibly defining test parameters or expected results based on the database engine type.
- **`dbt.tol`:** A TOL script likely containing common functions or setup procedures used by the individual database tests.

## Purpose

These tests ensure that the database drivers provided with TOL allow users to reliably connect to and interact with different database systems from within TOL scripts. They verify the correct implementation of functions like `DBConnect`, `DBExecute`, `DBFetch`, etc., for each supported database backend.

## Appendix

- **Technology:** TOL scripting language, SQL.
- **Dependencies:** Requires access to configured database instances (MySQL, PostgreSQL, etc.) for the relevant tests to run successfully.
- **Execution:** Tests are run via `_tolTester.tol`, invoked by the top-level test suite runners (`tol-master/tol_tests/run_all_tests.*`). 