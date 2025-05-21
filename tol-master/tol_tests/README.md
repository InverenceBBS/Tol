# TOL Test Suite (`tol-master/tol_tests/`)

## Overview

This directory contains the automated test suite for the TOL project. It includes test cases for various components and functionalities, along with scripts to execute these tests.

## Contents

- **Test Case Subdirectories:** Tests appear to be organized by the component they target:
    - `gsl/`: Tests for the integration with the GNU Scientific Library (GSL).
    - `tol/`: Tests for the core TOL language features and interpreter behavior.
    - `toldb/`: Tests for the database connectivity features (`dbdrivers/`).
    - `toltcl/`: Tests for the Tcl binding layer (`toltcl/`) and potentially Tcl-based tools like `tolbase`.
    (These directories likely contain `.tol` test scripts, expected output files, and possibly C++ unit test code).
- **Test Execution Scripts:**
    - `run_all_tests.bat`: Batch script to run the entire test suite on Windows.
    - `run_all_tests.sh`: Shell script to run the entire test suite on Linux/Unix systems.
- **Test Documentation:**
    - `how_to.html`: HTML document providing instructions on how to run or potentially add new tests.
    - `notas_sobre_tests.txt`: Text file containing notes (in Spanish) about the test suite.

## Purpose

The test suite is crucial for verifying the correctness and stability of the TOL project. Running these tests helps ensure that:
- Existing functionality remains correct after code changes (regression testing).
- New features behave as expected.
- TOL works consistently across different platforms (via the `.bat` and `.sh` runners).

## Appendix

- **Technology:** TOL scripts, Shell scripts, Batch scripts, possibly C++ unit testing frameworks (e.g., CTest, Google Test - check subdirs).
- **Usage:** Run via `run_all_tests.bat` or `run_all_tests.sh` to check the health of the codebase. Also serves as a source of examples for using various TOL features. 