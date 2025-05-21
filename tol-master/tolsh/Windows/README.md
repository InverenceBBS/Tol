# TolSH Windows Runtime Files (`tol-master/tolsh/Windows/`)

## Overview

This directory contains executable files (`.exe`) providing the necessary Tcl/Tk runtime environment for executing the TolSH Starkit (`tol-master/tolsh/sdx.kit`) on Microsoft Windows systems.

## Contents

- **`tclkit-rt.exe`, `tclkitsh.exe`, `tclkitsh858.exe`:** These are various **TclKit runtime executables** for Windows. TclKit is a self-contained executable bundling the Tcl interpreter and standard libraries. These different versions might correspond to different Tcl releases (e.g., `tclkitsh858.exe` for Tcl 8.5.8) or configurations (e.g., with or without Tk).

## Purpose

These files provide the underlying Tcl interpreter needed to run the Tcl scripts packaged within the TolSH Starkit (`sdx.kit`) on Windows. The Starkit relies on one of these TclKit executables to function.

## Appendix

- **Technology:** TclKit.
- **Platform:** Microsoft Windows. 