# TOL GSL Integration Tests (`tol-master/tol_tests/gsl/`)

## Overview

This directory contains test scripts (`.tol` files) designed to verify the integration and correct functioning of the GNU Scientific Library (GSL) features within the TOL environment.

## Contents

- **`ticket_001398/`:** A subdirectory containing test files specifically related to resolving issue or implementing feature #1398 in the project's bug tracking system. This likely tests a particular GSL function or behavior that was previously problematic or newly added.

(Other test files or subdirectories related to different GSL functionalities might also be present or added here.)

## Purpose

These tests ensure that the wrappers and bindings connecting TOL to GSL (likely implemented in `tol/btol/bgsl/` and `tol/bmath/gsl_ext/`) work as expected. They verify that TOL scripts can correctly call GSL functions and receive accurate results.

## Appendix

- **Technology:** TOL scripting language.
- **Execution:** These tests are typically run as part of the main test suite execution scripts (`tol-master/tol_tests/run_all_tests.*`). 