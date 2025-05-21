# Core TOL Language Tests (`tol-master/tol_tests/tol/`)

## Overview

This directory contains the main collection of test scripts (`.tol` files) for verifying the core functionality of the **TOL language interpreter** and its **standard library**.

## Contents

Tests are organized into subdirectories based on the feature or component being tested:

- **Language Features/Data Types:**
    - `BooleanAlgebra/`
    - `CreationAndCopy/`
    - `ImportExport/`
    - `LinearAlgebra/`
    - `NameBlock/`
    - `NumCalc/` (Numerical Calculations)
    - `OIS/` (Object Input/Output Streams)
    - `SetAlgebra/`
    - `Text/`
    - `kernel/` (Low-level interpreter features)
- **Standard Library Modules:**
    - `ARIMA/`
    - `BSR/` (Bayesian Structural Regression)
    - `KMeans/`
    - `Statistics/`
    - `database/`
    - `random_generation/`
    - `stdlib/` (General standard library functions)
    - `system/` (System interaction functions)
- **Other Test Categories:**
    - `Bugzilla/`: Tests specifically related to resolved bug reports.
    - `known_bugs/`: Tests demonstrating known, currently unresolved bugs.
    - `performance/`: Scripts used for performance testing.
    - `remind/`: Unknown purpose.
- **Test Runner/Helper Scripts:**
    - `_tolTester.tol`: Main test execution script for this directory.
    - `_bsrTester.tol`: Specific tester for BSR tests.
    - `_tolTester_knownbugs.tol`: Runner for known bug tests.
    - `test_template.tol`: A template for creating new test files.

## Purpose

These tests form the core regression suite for the TOL interpreter. They ensure that language syntax, built-in functions, data type operations, standard library modules, and core engine features work correctly and consistently across different builds and platforms.

## Appendix

- **Technology:** TOL scripting language.
- **Execution:** Tests are run via the helper scripts (`_tolTester.tol`, etc.), which are invoked by the top-level test suite runners (`tol-master/tol_tests/run_all_tests.*`). 