# README - cmdline Module (tcllib 1.10)

## Overview

This directory contains the `cmdline` module from Tcllib 1.10, located within the `tolsh` VFS. This module provides utilities for parsing command-line arguments passed to a Tcl script.

## Contents

### Files

- `cmdline.tcl`: The core implementation for command-line argument processing.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to simplify the handling of command-line options and arguments in Tcl scripts. It typically allows defining expected options (flags, options with values), parsing the `$argv` list, handling errors (like unknown options or missing arguments), and providing easy access to the parsed values. It supports common conventions like GNU-style long options.

## Appendix

N/A 