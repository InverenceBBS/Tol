# TolTcl Tcl Script Library (`tol-master/toltcl/library/`)

## Overview

This directory contains Tcl scripts (`.tcl`) that provide higher-level procedures and utilities built on top of the core C-based **TolTcl** binding (`toltcl/generic/`). It also includes scripts supporting the `tolsh` application.

## Contents

- **Tcl Wrapper Scripts:**
    - `toltcl.tcl`: Contains Tcl procedures that likely offer a more convenient or abstracted interface to the TOL engine than the raw C commands exposed by the binding. For example, it might provide procedures for easier data conversion or common command sequences.
    - `tolsh.tcl`: Contains Tcl procedures specifically required by the `tolsh` Starkit shell application (`tol-master/tolsh/`). This could include implementations for shell features like command history, input handling, custom output formatting, or completion logic.
- **Tcl Packaging:**
    - `pkgIndex.tcl.in`: A template used by the build system (CMake) to generate the `pkgIndex.tcl` file. This file registers the Tcl scripts in this directory so they can be loaded as part of a Tcl package (likely named `toltcl` or a sub-package).
- **Build Integration (`CMakeLists.txt`):** CMake script responsible for installing these `.tcl` files into the correct Tcl library location on the target system and generating the `pkgIndex.tcl` file.

## Purpose

This library directory provides Tcl code that enhances the usability of the TolTcl binding:
- It offers convenience functions (`toltcl.tcl`) for Tcl developers interacting with TOL.
- It contains the necessary Tcl logic (`tolsh.tcl`) for the `tolsh` command-line application.
These scripts are intended to be loaded into a Tcl interpreter alongside the compiled TolTcl shared library.

## Appendix

- **Implementation Language:** Tcl.
- **Usage:** These scripts are automatically loaded when the corresponding Tcl package is required (e.g., `package require toltcl`). They are installed by the build process. 