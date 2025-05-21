# TolSH: TOL Starkit Shell (`tol-master/tolsh/`)

## Overview

This directory contains the components for **TolSH**, a command-line shell or utility for interacting with the TOL environment. It is implemented as a **Tcl/Tk application** and packaged into a single, self-contained executable file (`sdx.kit`) using Starkit technology. This likely provides a more advanced command-line interface compared to the basic `tolcon` executable.

## Code Functionality

- **Core Logic (Tcl):** The primary source code resides within the `tolsh.vfs/` directory (which forms the virtual filesystem inside `sdx.kit`).
    - `main.tcl`: The entry point script for the TolSH application.
    - `lib/`: Contains supporting Tcl/Tk library scripts providing the shell's features (e.g., command history, input editing, interaction with the TOL interpreter).
- **Packaging:**
    - `sdx.kit`: The final Starkit executable containing the Tcl runtime, the TolSH scripts, and any necessary Tcl extensions.
    - `build.sh`/`build.bat`: Scripts potentially used to assemble the `sdx.kit` file.
- **Platform Components:** `Linux/` and `Windows/` might contain platform-specific resources, wrappers, or build artifacts related to TolSH.

## Potential API Functionality (Command-Line Interface)

The primary "API" is the command-line interface provided by the TolSH executable (`sdx.kit` or a wrapper):
- **Interactive TOL Session:** Allows users to type TOL commands and see results interactively.
- **Script Execution:** Likely allows executing `.tol` script files.
- **Shell Features:** May include features common to advanced shells:
    - Command history (up/down arrows).
    - Line editing.
    - Tab completion (potentially for TOL functions or variables).
    - Help commands.
- **Command-Line Arguments:** Might accept arguments for non-interactive execution, configuration, or passing parameters to TOL scripts.

## Appendix

- **Implementation Language:** Tcl/Tk.
- **Distribution:** Packaged as a Starkit (`sdx.kit`). Requires a compatible Tcl runtime (often bundled within the Starkit itself).
- **Dependencies:** Depends on the core TOL interpreter/library (`tol-master/tol/`) to execute TOL code.
- **Build:** Uses `build.sh`/`build.bat` and likely Tcl tools (like `sdx`) to create the Starkit. 