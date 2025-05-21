# app-tolsh Package

This directory contains the main application logic for `tolsh`, the TOL shell.

## Files

*   `tolsh.tcl`: This file likely contains the primary Tcl script that initializes the TOL shell environment, processes command-line arguments specific to `tolsh`, sets up the interactive loop (if applicable), and loads necessary TOL packages or Tcl libraries.
*   `pkgIndex.tcl`: The package index file, allowing this application-specific code to be potentially loaded as a package if needed, though it primarily serves as the entry point.

## Purpose

This package defines the core behavior and functionality of the `tolsh` application itself, acting as the bridge between the user, the Tcl interpreter hosting the shell, and the underlying TOL system.

## Usage

This is typically not used as a library via `package require`. Instead, `tolsh.tcl` is likely the main script executed when the `tolsh` command is invoked. 