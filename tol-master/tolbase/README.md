# Tolbase: Tcl/Tk GUI for TOL (`tol-master/tolbase/`)

## Overview

This directory contains the source code, build system files, documentation, and dependencies for **Tolbase**, the primary Graphical User Interface (GUI) for the **TOL (Time-Oriented Language)** project. Tolbase is implemented using **Tcl/Tk** and interacts with the TOL engine via the **TolTcl** binding layer (`tol-master/toltcl/`).

It provides an interactive environment for TOL development and analysis, likely including features such as:
- An interactive TOL console.
- A script editor with syntax highlighting.
- An object browser to inspect TOL variables and data structures.
- Visualization capabilities (plotting).
- Debugging tools.

## Contents

This directory has a rich structure supporting multiple build systems and platforms:

- **Source Code (`generic/`, `lib/`):** Contains the core Tcl/Tk scripts that implement the Tolbase interface and functionality.
- **Binary Wrappers (`bin/`):** Scripts (`tolbase.sh`, `tolbase.bat`) for launching Tolbase, handling environment setup.
- **Build Systems:**
    - **CMake (`CMakeLists.txt`, `cmake/`):** Primary build configuration using CMake.
    - **Autotools (`configure.in`, `configure`, `Makefile.in`, `aclocal.m4`, `tclconfig/`):** Legacy GNU Autotools build configuration.
- **Dependencies (`ThirdParty/`):** Contains bundled third-party libraries or components used by Tolbase.
- **Documentation (`doc/`, `README`, `INSTALL`, `NEWS`, `ChangeLog`):** Contains user and developer documentation, installation instructions, and project history.
- **Tests (`tests/`):** Test scripts for verifying Tolbase functionality.
- **Windows Support (`win/`, `win-VC9/`):** Windows-specific resources and Visual Studio 2008 (VC9) project files.
- **Tcl Packaging (`conf.tcl`, `pkgIndex.tcl`, `pkgIndex.tcl.in`):** Files related to making Tolbase function as a Tcl package.

## Installation

Tolbase supports both CMake and standard GNU Autotools installation procedures (`./configure && make && make install`).

Please consult the **`INSTALL`** file within this directory for detailed build and installation instructions for your platform.

## Dependencies

- A working **Tcl/Tk** installation.
- The **core TOL library** and the **TolTcl binding** (usually built as part of the main TOL project build process).
- Any libraries included in `ThirdParty/`.

## License

Tolbase is free software distributed under the terms of the **GNU General Public License (GPL)**. See the `COPYING` file for details. The GPL does not permit redistribution in proprietary programs.

## Reporting Bugs

If you find a bug, please refer to the bug reporting guidelines in the original `README` file in this directory or check the project website (`http://www.tol-project.org`).

## Appendix

- **Implementation Language:** Tcl/Tk, C (for potential extensions).
- **Build Tools:** CMake, GNU Autotools.
- **Platforms:** Cross-platform (Linux, Windows, likely macOS). 