# Dynamic Library Loading (`tol-master/tol/LoadDynLib/`)

## Overview

This directory contains the C++ implementation for dynamically loading shared libraries (e.g., `.dll`, `.so`) within the TOL runtime environment.

## Code Functionality

- **Core Implementation (`LoadDynLib.cpp`, `tol_LoadDynLib.h`):** These files provide the C++ functions and classes responsible for:
    - Platform-specific library loading (e.g., using `dlopen` on POSIX systems, `LoadLibrary` on Windows).
    - Resolving symbols (function pointers) within the loaded library.
    - Managing loaded library handles.
    - Handling potential errors during loading or symbol resolution.
- **Build System Integration (`CMakeLists.txt`, `Jamfile`, `Makefile.am`):** These files ensure that the dynamic library loading code is compiled and linked into the main TOL executable or core library as part of the build process using different build systems.

## Purpose

This component enables the TOL interpreter or TOL applications to extend their functionality at runtime by loading external code modules compiled as shared libraries. This is commonly used for implementing plugin systems, optional features, or performance-critical extensions written in C/C++. The TOL language likely provides functions (e.g., `LoadLibrary`, `GetProcAddress` equivalents) that utilize this underlying C++ implementation.

## Appendix

- **Implementation Language:** C++.
- **Technology:** Dynamic library loading APIs (e.g., `dlfcn.h`, `windows.h`).
- **Build:** Compiled as part of the main `tol` library/executable. 