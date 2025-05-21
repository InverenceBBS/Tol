# TOL Base Implementation (`tol-master/tol/btol/`)

## Overview

This directory appears to contain fundamental C++ components of the TOL interpreter engine, focusing on the implementation of **core data types** and possibly other base functionalities (suggested by the 'b' prefix in several subdirectories).

## Code Functionality

The C++ code (`.h`, `.cpp` files within subdirectories) likely implements:
- **Core Data Types:** Each `*_type/` subdirectory seems dedicated to a specific data type supported by TOL:
    - `complex_type/`, `real_type/`: Numerical types.
    - `date_type/`, `ctime_type/`, `timeset_type/`: Time-related types.
    - `serie_type/`, `cseries_type/`: Time series or sequence types.
    - `matrix_type/`, `vmatrix_type/`, `polmat_type/`, `polynomial_type/`, `ratio_type/`: Mathematical/matrix types (including sparse matrices - `tol_bsparse.h`).
    - `set_type/`, `code_type/`, `text_type/`: Set, code representation, and text types.
- **Fundamental Engine Components:** Subdirectories like `bgrammar/`, `bmodel/`, `bmonte/`, `bkfilter/`, `bgsl/` probably house base implementations for grammar processing, model representation, statistical methods (Monte Carlo, Kalman Filter), and potentially integration with external libraries (like GSL).
- **Initialization Logic:** `delay_init.cpp` might be involved in TOL's lazy evaluation mechanism.
- **Build Integration:** Contains build script fragments (`CMakeLists.txt`, `Jamfile`, `Makefile.am`) to compile these components as part of the main TOL library.

## Potential API Functionality (Internal C++ API)

This directory defines the internal C++ classes and functions used by the rest of the TOL interpreter to work with its data types and core mechanisms. This is likely *not* a public API, but rather the internal building blocks. Key internal API aspects would include:
- **Class Definitions:** C++ classes for each data type (`TolComplex`, `TolMatrix`, `TolSerie`, `TolTimeSet`, etc.).
- **Methods:** Member functions for creating, manipulating, accessing, and performing operations on instances of these data types (e.g., arithmetic for numbers/matrices, time operations for dates/series, element access for sets/matrices).
- **Core Functions:** Helper functions or classes for internal engine tasks (parsing support, model execution, etc.).

## Appendix

- **Implementation Language:** C++.
- **Build:** Compiled as part of the main `tol` library via parent build scripts. 