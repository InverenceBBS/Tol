# TolTcl Third-Party Tcl Extensions (`tol-master/toltcl/ThirdParty/`)

## Overview

This directory contains source code archives for third-party Tcl extensions that are dependencies or optional components for the **TolTcl** binding layer (`tol-master/toltcl/`). Bundling these sources allows them to be built as part of the TolTcl compilation process.

## Contents

- **Source Archives:** Compressed source code for:
    - `TclCurl-7.19.6.tar.gz`: **TclCurl** extension (v7.19.6) - Provides Tcl bindings for the libcurl library, enabling URL transfers (HTTP, HTTPS, FTP, etc.) from Tcl scripts.
    - `TclCurl-7.22.0.tar.gz`: **TclCurl** extension (v7.22.0) - A newer version of the same extension.
- **Build Integration (`CMakeLists.txt`):** A CMake script that likely handles:
    - Selecting the desired TclCurl version (presumably 7.22.0).
    - Unpacking the source archive.
    - Configuring and building the TclCurl extension (which itself likely uses Autotools or CMake and depends on libcurl development libraries).
    - Ensuring the compiled TclCurl extension is available for TolTcl to load or link against.

## Purpose

This directory vendors the source code for the TclCurl extension. By including it directly and integrating its build with CMake, the project can provide network transfer capabilities (like fetching data from web APIs) accessible via Tcl commands within the TolTcl environment, potentially simplifying the build and dependency management for end-users.

## Appendix

- **Technology:** Tcl C extensions, CMake, libcurl.
- **Dependencies:** Building TclCurl requires the libcurl development library and headers to be installed on the system.
- **Usage:** Used internally by the CMake build process for TolTcl. The source archive is unpacked and compiled automatically if the TclCurl feature is enabled. 