# Tcl Library (`tol-master/tolbaseBLT/lib/`)

## Overview

This directory contains the Tcl packages that implement the high-level API for
the BLT-based widgets used in Tolbase. The scripts here wrap the lower-level
widget definitions and provide convenient commands for application developers.

## Contents

Typical files include widget initialization scripts, package index files, and
support procedures shared across the toolkit.

## Purpose

These Tcl modules are installed as a package so applications can `package
require` the tolbaseBLT widgets and use them directly.

## Appendix

- **Technology:** Tcl package conventions.
- **Usage:** Loaded automatically when Tolbase or other applications request the
  `tolbaseBLT` package.
