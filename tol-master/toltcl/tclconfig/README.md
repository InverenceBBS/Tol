# TolTcl Autotools Configuration Support (`tol-master/toltcl/tclconfig/`)

## Overview

This directory contains M4 macros and helper scripts used by the GNU Autotools build system (`autoconf`, `automake`) to configure the build process for the **TolTcl** binding layer (`tol-master/toltcl/`).

## Contents

- **Autoconf Macros (`.m4`):**
    - `tcl.m4`: A collection of Autoconf macros for detecting Tcl installations (headers, libraries, `tclConfig.sh`).
    - `toltcl.m4`: Custom Autoconf macros specific to the TolTcl binding. These likely implement checks for the core TOL library, the TclCurl dependency (if enabled), and any other specific requirements for compiling the TolTcl C/C++ code.
- **Autotools Helper Scripts:**
    - `install-sh`, `missing`: Standard portable helper scripts used during the `configure` and `make install` phases.
- **Documentation:**
    - `README.txt`, `ChangeLog`: Basic information and history about this configuration support directory.

## Purpose

This directory provides essential components for the `./configure` script of TolTcl when using Autotools. The M4 macros (`tcl.m4`, `toltcl.m4`) enable the `configure` script (generated from `toltcl/configure.in`) to correctly:
- Locate the required Tcl development environment.
- Detect necessary dependencies (core TOL library, TclCurl, etc.).
- Adapt the build configuration (Makefiles) based on the system environment and selected options.

## Appendix

- **Technology:** GNU Autotools (Autoconf), M4 macro language, Shell scripting.
- **Usage:** Used internally by the Autotools `./configure` process for TolTcl. Developers modifying the Autotools build for TolTcl would edit `toltcl/configure.in` and potentially these M4 files. 