# TolTcl CMake Support Files (`tol-master/toltcl/cmake/`)

## Overview

This directory contains helper files for the CMake build system specifically tailored for building the **TolTcl** binding layer (`tol-master/toltcl/`). It primarily consists of custom CMake modules.

## Contents

- **Custom Modules (`modules/`):** This subdirectory contains TolTcl-specific CMake modules (`.cmake` files). These modules likely define functions or macros to:
    - Find the required Tcl libraries and headers (`FindTCL.cmake` - possibly a custom version).
    - Find the TclCurl dependency (potentially `FindTclCurl.cmake` or similar, which might in turn require `FindCURL.cmake`).
    - Find the core TOL library dependency (`FindTOL.cmake` or similar).
    - Configure build options specific to the TolTcl C binding code (e.g., compiler flags, definitions).
    - Handle the installation rules for the TolTcl shared library.

## Purpose

This directory supports the CMake build process for the TolTcl binding by:
- Encapsulating the logic needed to find its specific dependencies (Tcl, core TOL, TclCurl).
- Separating TolTcl-specific CMake logic from the CMake files for other components like the core engine (`tol/cmake/`) or the GUI (`tolbase/cmake/`).

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the CMake build process when building TolTcl. Modules are likely added to `CMAKE_MODULE_PATH` by the main `toltcl/CMakeLists.txt`. 