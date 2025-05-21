# Tolbase CMake Modules (`tol-master/tolbase/cmake/modules/`)

## Overview

This directory contains custom CMake modules (`.cmake` files) used to support the build configuration of the **Tolbase** Tcl/Tk GUI component.

## Contents

- **`FindTOL.cmake`:** A CMake find-module responsible for locating the core TOL library (`tollib`) which Tolbase depends on (likely via the TolTcl binding).
- **`LibFindMacros.cmake`:** Contains general-purpose CMake macros commonly used within find-modules to standardize the process of locating libraries and headers.
- **`MSysMacros.cmake`:** Contains CMake macros specifically helpful when building in an MSYS/MinGW environment on Windows.

(Note: Finding Tcl/Tk itself is likely handled by CMake's built-in `FindTCL` module, possibly invoked from the main `tolbase/CMakeLists.txt`.)

## Purpose

These modules help the CMake build system locate the essential TOL library dependency for Tolbase and provide common utility macros, contributing to a more robust and portable build process.

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the `CMakeLists.txt` in the parent `tolbase/` directory when configuring the Tolbase build. 