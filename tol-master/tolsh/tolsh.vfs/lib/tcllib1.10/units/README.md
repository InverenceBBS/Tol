# README - units Module (tcllib 1.10)

## Overview

This directory contains the `units` module from Tcllib 1.10, located within the `tolsh` VFS. This module provides utilities for parsing, converting, and manipulating quantities with associated physical units.

## Contents

### Files

- `units.tcl`: The core implementation for handling units and conversions.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to allow Tcl applications to work with physical quantities in a dimensionally-aware manner. It likely defines a database of common units (SI, imperial, etc.) and their relationships, allowing for conversion between compatible units (e.g., meters to feet, kilograms to pounds, seconds to hours) and potentially preventing dimensionally incorrect operations (e.g., adding meters and seconds).

## Appendix

N/A 