# Custom CMake Modules (`tol-master/tolbaseBLT/cmake/modules/`)

## Overview

This subdirectory houses custom `Find*.cmake` modules and macro definitions used
by the tolbaseBLT build system. They extend CMake's module search capabilities
to locate third-party Tcl/Tk packages and tools.

## Contents

- `FindMkWidgets.cmake` – Example module for locating the MkWidgets package.
- Additional `Find<Package>.cmake` files as needed for optional dependencies.

## Purpose

These modules keep platform-specific search logic out of the main
`CMakeLists.txt` and make the build process more portable.

## Appendix

- **Technology:** CMake module syntax.
- **Usage:** Included automatically when running CMake from the `cmake/`
  directory.
