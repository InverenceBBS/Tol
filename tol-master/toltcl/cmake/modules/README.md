# TolTcl CMake Modules (`tol-master/toltcl/cmake/modules/`)

## Overview

This directory contains custom CMake modules (`.cmake` files) used to support the build configuration of the **TolTcl** Tcl binding component.

## Contents

- **`FindTOL.cmake`:** A CMake find-module responsible for locating the core TOL library (`tollib`) which the TolTcl binding links against.
- **`LibFindMacros.cmake`:** Contains general-purpose CMake macros commonly used within find-modules to standardize the process of locating libraries and headers.
- **`MSysMacros.cmake`:** Contains CMake macros specifically helpful when building in an MSYS/MinGW environment on Windows.

(Note: Finding the Tcl library itself is likely handled by CMake's built-in `FindTCL` module, possibly invoked from the main `toltcl/CMakeLists.txt`.)

## Purpose

These modules help the CMake build system locate the essential TOL library dependency for the TolTcl binding and provide common utility macros, contributing to a more robust and portable build process.

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the `CMakeLists.txt` in the parent `toltcl/` directory when configuring the TolTcl build. 