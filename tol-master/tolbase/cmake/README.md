# Tolbase CMake Support Files (`tol-master/tolbase/cmake/`)

## Overview

This directory contains helper files for the CMake build system specifically tailored for building the **Tolbase** GUI component (`tol-master/tolbase/`). It includes toolchain files and custom CMake modules.

## Contents

- **Toolchain Files (`linux-i686.toolchain.cmake`):** Provides CMake configuration for targeting 32-bit Linux builds. (Other toolchain files might be present in a full checkout or generated during the build).
- **Custom Modules (`modules/`):** This subdirectory likely contains Tolbase-specific CMake modules (`.cmake` files). These modules might define functions or macros to:
    - Find the required Tcl and Tk libraries and headers (`FindTCL.cmake`, `FindTK.cmake` - possibly custom versions).
    - Find the third-party Tcl/Tk extensions bundled in `tolbase/ThirdParty/` (e.g., `FindTkTable.cmake`, `FindImg.cmake`).
    - Configure build options specific to Tolbase or its C extension code (if any).
    - Handle the installation rules for Tolbase Tcl scripts and compiled extensions.

## Purpose

This directory supports the CMake build process for Tolbase by:
- Providing configurations for specific build targets (toolchain files).
- Encapsulating the logic needed to find Tcl/Tk and its specific extension dependencies required by Tolbase.
- Separating Tolbase-specific CMake logic from the core TOL engine's CMake files (`tol/cmake/`).

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the CMake build process when building Tolbase. Modules are likely added to `CMAKE_MODULE_PATH`. 