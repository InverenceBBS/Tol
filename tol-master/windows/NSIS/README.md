# NSIS Installer Scripts (`tol-master/windows/NSIS/`)

## Overview

This directory contains the Nullsoft Scriptable Install System (NSIS) scripts
and helper files used to produce Windows installer executables for TOL and its
related components.

## Contents

- `Tolbase.nsi.template` – Base template for creating the final installer
  definition. It is combined with build information using the `Tolbase.nsi.generate.tol`
  script.
- `Tolbase.nsi.generate.tol` – TOL script that fills in version numbers and file
  lists to produce the actual `.nsi` file fed to `makensis`.
- `build_setup.bat` – Convenience batch file that invokes the NSIS compiler to
  create the installer.
- Additional helper scripts (`send2web.bat`, `store_history.tol`, etc.) to
  publish installers or keep build logs.

## Purpose

These files automate the creation of self-contained Windows installers so users
can easily deploy TOL or Tolbase on their systems without needing a separate
development environment.

## Appendix

- **Technology:** NSIS scripting, Windows Batch, TOL scripts.
- **Usage:** Run `build_setup.bat` after building the binaries to generate an
  installer executable.
