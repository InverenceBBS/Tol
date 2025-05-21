# TolSH Linux Runtime Files (`tol-master/tolsh/Linux/`)

## Overview

This directory contains executable files providing the necessary Tcl/Tk runtime environment for executing the TolSH Starkit (`tol-master/tolsh/sdx.kit`) on Linux systems.

## Contents

- **`tclkit-linux-x86.upx.bin`:** A binary executable, likely a **TclKit runtime** compressed with UPX for 32-bit (x86) Linux. TclKit is a self-contained executable bundling the Tcl interpreter and standard libraries.
- **`tclkitsh-8.5.8`:** Another binary executable, possibly an uncompressed or slightly different version of the TclKit runtime (specifically for Tcl version 8.5.8), potentially including shell-specific features.

## Purpose

These files provide the underlying Tcl interpreter needed to run the Tcl scripts packaged within the TolSH Starkit (`sdx.kit`) on Linux. The Starkit relies on one of these TclKit executables to function.

## Appendix

- **Technology:** TclKit, UPX (compression).
- **Platform:** Linux (likely 32-bit x86 focus). 