# README - treeql Module (tcllib 1.10)

## Overview

This directory contains the `treeql` (Tree Query Language) module from Tcllib 1.10, within the `tolsh` VFS. This module provides a query language for searching and extracting data from tree structures, likely those created using Tcllib's `struct::tree` module.

## Contents

### Files

- `treeql.tcl`: Main package file, possibly dispatching to version-specific implementations.
- `treeql84.tcl`: Implementation compatible with Tcl 8.4.
- `treeql85.tcl`: Implementation compatible with Tcl 8.5+.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to provide a declarative way to query tree data structures in Tcl. Instead of writing complex recursive procedures to traverse and search trees, users can formulate queries in the TreeQL language, which this module then executes against a given `struct::tree` object to retrieve matching nodes or values. This is analogous to using SQL for relational databases but adapted for tree structures.

## Appendix

N/A 