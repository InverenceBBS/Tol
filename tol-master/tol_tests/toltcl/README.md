# TolTcl Binding Tests (`tol-master/tol_tests/toltcl/`)

## Overview

This directory contains test scripts designed to verify the functionality of the **TolTcl binding layer** (implemented in `tol-master/toltcl/`), which connects the Tcl scripting environment to the TOL engine.

## Contents

- **`_toltclTester.tol`:** The main TOL script responsible for executing the TolTcl tests.
- **`Bugzilla/`:** A subdirectory containing test cases related to specific bugs that have been fixed in the TolTcl binding.
- **`toltcl_test_template.tcl`:** A template Tcl script (`.tcl`) for creating new TolTcl tests. This suggests tests involve writing Tcl code that calls functions provided by the TolTcl binding.
- **`toltcl_test_template.tol`:** A template TOL script (`.tol`) potentially used in conjunction with the Tcl tests, perhaps to define helper functions or data within TOL for the Tcl script to interact with.

(Specific test files, likely `.tcl` scripts, would reside either directly here or within subdirectories like `Bugzilla/`.)

## Purpose

These tests ensure that the TolTcl binding correctly exposes TOL functionality to the Tcl environment. They verify that Tcl scripts can:
- Load the TolTcl package.
- Call functions like `tol::eval`, `tol::getvar`, `tol::setvar`.
- Exchange data (including complex types like Matrices or Sets) correctly between Tcl and TOL.
- Handle errors properly.

## Appendix

- **Technology:** Tcl, TOL scripting language.
- **Execution:** Tests are run via `_toltclTester.tol`, invoked by the top-level test suite runners (`tol-master/tol_tests/run_all_tests.*`). 