# TolTcl: TOL to Tcl Binding (`tol-master/toltcl/`)

## Overview

This directory contains **TolTcl**, the binding layer that connects the core **TOL C++ engine** (`tol-master/tol/`) with the **Tcl scripting language**. It allows Tcl scripts to load and interact with the TOL interpreter, execute TOL code, and exchange data. This component is essential for Tcl-based tools like Tolbase (the GUI) and TolSH (the Starkit shell).

## Code Functionality

- **Tcl Command Implementation (C):** The `generic/` directory likely contains C source files (`.c`) that implement new commands for the Tcl interpreter. These C functions use the internal C++ API of the TOL engine to:
    - Initialize and manage the TOL environment.
    - Execute strings or files of TOL code.
    - Convert data types between Tcl (e.g., Tcl_Obj) and TOL's internal C++ representations (e.g., TolMatrix, TolSerie).
    - Expose specific TOL functionalities as Tcl commands.
- **Tcl Package Definition:** Files like `pkgIndex.tcl.in` and `configure.in` define TolTcl as a standard Tcl package, making it loadable via `package require TolTcl` in Tcl scripts. The build process generates the final `pkgIndex.tcl`.
- **Build System:** Utilizes Autotools (`configure`, `Makefile.in`) and CMake (`CMakeLists.txt`) to compile the C binding code into a shared library (e.g., `.dll` on Windows, `.so` on Linux) that Tcl can load.
- **Platform Support:** Includes build configurations and potentially specific code for different platforms (`win-vc*`, `linux-*.cmake`).

## Potential API Functionality (Tcl Commands)

The API provided by this package consists of Tcl commands available after `package require TolTcl`:
- **Interpreter Management:** Commands to initialize, reset, or shutdown the embedded TOL interpreter.
- **Code Execution:** `tol::eval {<TOL code string>}`, `tol::source <filename.tol>` (or similar).
- **Data Access/Manipulation:** Commands to:
    - Get/Set TOL variables from Tcl.
    - Create TOL data structures (matrices, series, etc.) from Tcl lists or variables.
    - Convert TOL data structures returned by TOL code into Tcl representations.
- **Function Calling:** Potentially commands to directly call specific TOL functions with arguments from Tcl.
- **Status/Error Reporting:** Commands to check the status of the TOL interpreter or retrieve error messages.

## Appendix

- **Implementation Language:** C (for Tcl bindings), Tcl (for package indexing).
- **Dependencies:** Requires a Tcl development environment (headers, libraries) and the compiled core TOL library (`tol-master/tol/`).
- **Build:** Compiled into a shared library loadable by Tcl. See `INSTALL`.
- **License:** GNU General Public License (GPL). See `COPYING`. 