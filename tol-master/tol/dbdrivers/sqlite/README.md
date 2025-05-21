# SQLite Source Code (`tol-master/tol/dbdrivers/sqlite/`)

## Overview

This directory contains the core source code files for the SQLite 3 database engine.

## Contents

*   **`sqlite3.c`**: The main C source file for SQLite, often referred to as the "amalgamation" as it combines many individual source files into one for easier compilation.
*   **`sqlite3.h`**: The corresponding C header file containing declarations for the SQLite API functions and data structures.

## Purpose

The source code in this directory is included and compiled as part of the TOL build process. It provides the underlying database engine functionality for the TOL SQLite database driver (`libtolsqlite.c`) located in the parent `tol-master/tol/dbdrivers/` directory. Including the source directly simplifies the build process and avoids external dependencies on a pre-installed SQLite library.

## Appendix

*   **Source:** SQLite Database Engine (www.sqlite.org)
*   **Technology:** C 