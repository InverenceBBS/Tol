# Core TOL CMake Modules (`tol-master/tol/cmake/modules/`)

## Overview

This directory contains custom CMake modules (`.cmake` files), primarily **find-modules**, used by the core TOL build system (`tol-master/tol/CMakeLists.txt`) to locate and configure external library dependencies.

## Contents

These modules detect various libraries commonly used in scientific computing and required by TOL or its optional components:

- **Numerical Libraries:**
    - `FindCBLAS.cmake`: Finds a C Basic Linear Algebra Subprograms (CBLAS) implementation.
    - `FindCLAPACK.cmake`: Finds a C LAPACK (Linear Algebra PACKage) implementation.
    - `FindCHOLMOD.cmake`: Finds the CHOLMOD sparse Cholesky factorization library (part of SuiteSparse).
    - `FindFFTW.cmake`: Finds the Fastest Fourier Transform in the West (FFTW) library.
    - `FindGSL.cmake`: Finds the GNU Scientific Library (GSL).
- **Database Connectivity:**
    - `FindMySQL.cmake`: Finds MySQL client libraries and headers.
    - `FindODBC.cmake`: Finds ODBC (Open Database Connectivity) libraries and headers.
    - `FindPostgreSQL.cmake`: Finds PostgreSQL client libraries and headers.
- **Other Libraries:**
    - `FindLTDL.cmake`: Finds GNU Libtool's Libltdl library for dynamic library loading.
    - `FindZipArchive.cmake`: Finds a library for handling Zip archives (potentially libzip or a custom one).
- **Language/Framework Integration:**
    - `FindCintHeaders.cmake`: Finds headers for the CINT C/C++ interpreter (used by ROOT).
    - `FindR.cmake`: Finds an R installation (used when building the RTOL binding).
    - `FindROOT.cmake`: Finds the ROOT data analysis framework.
- **Helper Macros:**
    - `LibFindMacros.cmake`: General-purpose macros to aid in writing find-modules.
    - `MSysMacros.cmake`: Macros specifically for use in MSYS/MinGW environments on Windows.

## Purpose

These CMake modules allow the TOL build system to adapt to different system configurations by reliably finding required external dependencies. They ensure that TOL can be compiled and linked correctly against the necessary libraries if they are present on the user's system.

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the main CMake configuration process for the core TOL library. 