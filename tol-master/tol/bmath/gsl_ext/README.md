# TOL GSL Extensions (`tol-master/tol/bmath/gsl_ext/`)

## Overview

This directory contains C/C++ source code providing extensions and wrappers around the **GNU Scientific Library (GSL)** for use within the TOL environment. It builds upon the base GSL integration found in `tol/btol/bgsl/`.

## Contents

- **Source Files (`.c`, `.cpp`):**
    - `gsl_linalg_ext.c`: Extensions related to GSL linear algebra routines.
    - `gsl_util_ext.c`: Utility functions leveraging GSL.
    - `rcmnorm.cpp`: Implementation possibly for Recursive Calculation of Multivariate Normal probabilities or related computations.
    - `rtnorm.c`: Implementation related to the Truncated Normal distribution.
    - `tmvnd.c`: Implementation related to the Truncated Multivariate Normal distribution density.
- **Header File (`gsl_ext.h`):** Declares the functions implemented in the source files, making them available to other parts of the TOL C++ codebase.
- **Test Files (`test_*.c`, `test_rcmnorm.tol`):** Unit tests and TOL scripts designed to verify the correctness of the GSL extensions implemented here.
- **Build System Files (`CMakeLists.txt`, `Jamfile`, `Makefile.am`):** Integrate the compilation of these source files into the main TOL library (`tollib`) build process.

## Purpose

This code extends TOL's capabilities by providing specialized numerical routines built upon GSL. It offers functions for advanced statistical distributions (truncated normal, multivariate normal) and potentially enhanced linear algebra features, making these available to TOL users via built-in functions or standard library packages.

## Appendix

- **Implementation Language:** C, C++.
- **Dependencies:** GNU Scientific Library (GSL).
- **Build:** Compiled as part of the main `tol` library. 