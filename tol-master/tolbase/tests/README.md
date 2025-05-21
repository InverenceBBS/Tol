# Tolbase Test Scripts (`tol-master/tolbase/tests/`)

## Overview

This directory contains automated test scripts specifically for the **Tolbase** GUI component (`tol-master/tolbase/`).

## Contents

- **Test Scripts (`.tol`):** Contains test cases written in the TOL language (e.g., `030926.tol`, `031008.tol`). These scripts likely:
    - Load the Tolbase Tcl package.
    - Create or interact with Tolbase GUI elements using Tcl commands exposed by Tolbase.
    - Call underlying TOL functions via Tolbase/TolTcl.
    - Verify expected results or GUI states.
    The filenames might correspond to dates or issue tracking numbers.

## Purpose

These tests are used to verify the functionality of the Tolbase GUI and its interaction with the core TOL engine via the `TolTcl` binding. They help ensure that GUI components behave as expected and that changes to Tolbase or underlying libraries do not break existing features (regression testing). These tests are likely executed as part of a larger test suite (perhaps triggered by scripts in `tol-master/tol_tests/`).

## Appendix

- **Implementation Language:** TOL.
- **Usage:** Executed by a test runner script (e.g., `tol-master/tol_tests/run_all_tests.sh`) to verify Tolbase functionality. 