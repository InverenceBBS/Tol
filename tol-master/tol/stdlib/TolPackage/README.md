# TOL Package Management System (`tol-master/tol/stdlib/TolPackage/`)

## Overview

This directory contains the TOL language (`.tol`) implementation of the **TOL Package Management System**. This system is part of the standard library and provides the mechanisms for organizing, distributing, finding, loading, and managing TOL code modules (packages).

## Contents

- **Core Package Logic:**
    - `TolPackage.tol`: Likely defines core functions for package handling (e.g., `Include`, `Require`, package definition syntax).
    - `builder.tol`: Script for building packages from source.
    - `packager.tol`: Script for creating distributable package archives.
    - `common.tol`: Contains common functions and utilities used throughout the package system.
- **Metadata and Configuration:**
    - `TolPlatform.tol`: Functions for determining the current platform (OS, architecture) for conditional package loading or building.
    - `TolVersion.tol`: Functions for handling TOL and package version information and compatibility.
    - `def_catalog.tol`: Script possibly defining or managing catalogs (lists) of available packages.
    - `def_localblock.tol`: Script related to defining local package blocks or namespaces.
- **Remote Package Handling:**
    - `client.tol`: Functions for interacting with package repositories from the client side (e.g., searching, downloading).
    - `server.tol`: Potential server-side logic if a TOL-based package server exists.
- **Data Files:**
    - `listA.oza`: A data archive (likely OIS format) possibly containing a default package list or catalog information.

## Purpose

This package system allows TOL code to be modularized and distributed effectively. It enables:
- Defining reusable code modules (packages).
- Managing dependencies between packages.
- Loading required packages into a TOL session (`Include`).
- Potentially building, distributing, and installing new packages.

## Appendix

- **Implementation Language:** TOL.
- **Usage:** Provides core TOL functions like `Include`, used internally by the interpreter and standard library, and potentially by users managing custom packages. 