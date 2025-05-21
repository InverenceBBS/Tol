# TolTcl Debugging Support (`tol-master/toltcl/debug/`)

## Overview

This directory contains resources to aid developers in debugging the **TolTcl** binding layer (`tol-master/toltcl/`).

## Contents

- **`default_config.sh`:** A shell script designed to configure the environment for a debugging session. It might perform actions such as:
    - Setting environment variables to enable debug symbols or logging within TolTcl or its dependencies (Tcl, TOL core).
    - Specifying paths to debug builds of libraries.
    - Configuring other settings useful for attaching a debugger or analyzing runtime behavior.
    This script would typically be sourced (`. ./default_config.sh`) by a developer before starting a debugging session.

## Purpose

This directory provides convenient tools for developers needing to debug the TolTcl C binding code. The `default_config.sh` script helps establish a consistent debugging environment.

## Appendix

- **Technology:** Shell scripting (sh/bash).
- **Usage:** Intended for developers working on the TolTcl component. Source `default_config.sh` in a shell before running TolTcl under a debugger. 