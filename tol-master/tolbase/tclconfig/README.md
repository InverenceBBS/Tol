# Tolbase Autotools Configuration Support (`tol-master/tolbase/tclconfig/`)

## Overview

This directory contains M4 macros and helper scripts used by the GNU Autotools build system (`autoconf`, `automake`) to configure the build process for the **Tolbase** GUI component (`tol-master/tolbase/`).

## Contents

- **Autoconf Macros (`.m4`):**
    - `tcl.m4`: A collection of Autoconf macros specifically for detecting Tcl and Tk installations. These macros help the main `configure` script find the necessary Tcl/Tk headers, libraries, and configuration scripts (`tclConfig.sh`, `tkConfig.sh`) and set appropriate compiler and linker flags.
    - `tolbase.m4`: Custom Autoconf macros specific to Tolbase. These might be used to check for the third-party Tcl extensions bundled with Tolbase, define Tolbase-specific configuration options, or perform other checks needed for the Tolbase build.
- **Autotools Helper Scripts:**
    - `install-sh`, `missing`, `mkinstalldirs`: Standard portable helper scripts used during the `configure` and `make install` phases (likely copied from Autotools distributions).
- **Documentation:**
    - `README.txt`, `ChangeLog`: Basic information and history about this configuration support directory.

## Purpose

This directory provides essential components for the `./configure` script of Tolbase when using Autotools. The M4 macros (`tcl.m4`, `tolbase.m4`) enable the `configure` script (generated from `tolbase/configure.in`) to correctly:
- Locate the required Tcl/Tk development environment.
- Detect necessary dependencies (like TkTable, TclImg, etc.).
- Adapt the build configuration (Makefiles) based on the system environment.

## Appendix

- **Technology:** GNU Autotools (Autoconf), M4 macro language, Shell scripting.
- **Usage:** Used internally by the Autotools `./configure` process for Tolbase. Developers modifying the Autotools build for Tolbase would edit `tolbase/configure.in` and potentially these M4 files. 