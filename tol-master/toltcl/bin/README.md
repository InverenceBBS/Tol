# TolSH Launch Script (`tol-master/toltcl/bin/`)

## Overview

This directory contains a utility shell script for launching the **TolSH** Starkit shell (`tol-master/tolsh/`) on Unix-like operating systems.

## Contents

- **`tolsh.sh`:** A shell script wrapper designed for Unix-like systems (Linux, macOS) to start the TolSH Starkit (`sdx.kit`). It likely performs tasks such as:
    - Setting up the environment required by TOL and Tcl/Tk (e.g., sourcing `confenv.sh` from `tol/bin/`, setting library paths).
    - Locating the `tolsh` Starkit executable (`sdx.kit`).
    - Executing the Starkit, possibly passing command-line arguments.
- **`CMakeLists.txt`:** A CMake script, probably used to install the `tolsh.sh` script into the system's executable path during the main TOL installation process.

## Purpose

This script provides a user-friendly way to start the TolSH Starkit shell from the command line on Unix-like systems, handling the necessary environment setup automatically. It complements the `tolcon.sh` (for the basic console) and `tolbase.sh` (for the GUI) wrappers.

## Appendix

- **Implementation Language:** Shell script (sh/bash).
- **Platform:** Unix-like systems (Linux, macOS, etc.).
- **Usage:** Execute `tolsh.sh` to start the TolSH interactive Starkit shell. 