# Tolbase Generic C Code (`tol-master/tolbase/generic/`)

## Overview

This directory contains platform-independent C source code related to the initialization and core setup of the Tolbase Tcl/Tk application or package. It might also include resources used when building a standalone Tolbase executable.

## Code Functionality

- **Tcl Package Initialization (`tolbase.c`):** Contains the C function (likely `Tolbase_Init`) that is called by the Tcl interpreter when the Tolbase package is loaded (`package require tolbase`). This function registers any commands implemented in C that Tolbase provides to the Tcl environment.
- **Standalone Application Initialization (`tkAppInit.c`):** Provides a standard Tcl/Tk application entry point (`main`). This code creates a Tcl interpreter, initializes the Tk toolkit, loads required Tcl packages (including Tolbase and its dependencies like TkTable, Img, TclODBC), and typically sources the main Tolbase Tcl script to start the GUI. This is used if Tolbase is compiled into a custom `wish`-like executable.
- **Windows Resources (`*.rc`):** Resource definition files used when compiling the Tolbase executable on Windows. They embed metadata like version information, icons (specified here or elsewhere), and potentially dialogs into the `.exe` file. Separate versions are provided for GCC/MinGW (`-gnu`) and MSVC (`-msvc`) compilers.
- **Build Integration (`CMakeLists.txt`):** CMake script defining how to compile this C code and link it, either into a shared library (the Tolbase Tcl package) or a standalone executable.

## Purpose

This directory provides the C-level glue required for the Tolbase Tcl/Tk GUI. It initializes the Tcl package, potentially provides a main entry point for a standalone application build, and includes Windows-specific resources for better integration on that platform.

## Appendix

- **Implementation Language:** C.
- **Technology:** Tcl/Tk C API, Windows Resource Scripts.
- **Build:** Compiled into a shared library (Tcl package) or a standalone executable, depending on build configuration. 