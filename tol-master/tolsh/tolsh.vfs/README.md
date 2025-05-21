# TolSH Starkit Virtual File System (`tol-master/tolsh/tolsh.vfs/`)

## Overview

This directory contains the source files that are packaged into the **Virtual File System (VFS)** of the TolSH Starkit (`tol-master/tolsh/sdx.kit`). Starkit technology bundles these files into a single executable, which mounts this VFS internally when run.

## Contents

- **`main.tcl`:** The primary Tcl script that serves as the entry point when the `sdx.kit` Starkit is executed. It initializes the TolSH application.
- **`lib/`:** A subdirectory containing the Tcl library scripts that provide the core logic and features of the TolSH shell. This includes code for:
    - Parsing and handling user commands.
    - Interacting with the TOL engine via the TolTcl binding.
    - Implementing shell features like command history, completion, etc.
    - Defining any specific procedures or utilities for the TolSH environment.

## Purpose

These Tcl scripts constitute the actual implementation of the TolSH application. They are executed by the TclKit runtime when the user launches the `sdx.kit` file.

## Appendix

- **Implementation Language:** Tcl.
- **Packaging:** These files are bundled into `tol-master/tolsh/sdx.kit` using Starkit tools (like `sdx`). 