# TolTcl Release Configuration Support (`tol-master/toltcl/release/`)

## Overview

This directory contains resources related to configuring the environment for standard (release) usage of the **TolTcl** binding layer (`tol-master/toltcl/`).

## Contents

- **`default_config.sh`:** A shell script designed to configure the environment for running release builds of TolTcl. It likely performs actions such as:
    - Setting standard environment variables required by TolTcl (e.g., `TOL_PATH`, library paths).
    - Specifying paths to release builds of libraries.
    - Configuring other settings suitable for normal execution (as opposed to debugging).
    This script might be sourced (`. ./default_config.sh`) by users or wrapper scripts (`toltcl/bin/tolsh.sh`) before running applications that use TolTcl.

## Purpose

This directory provides a convenient script (`default_config.sh`) to help set up the correct runtime environment for using standard release builds of the TolTcl binding layer, complementing the similar script found in the `debug/` directory for debugging purposes.

## Appendix

- **Technology:** Shell scripting (sh/bash).
- **Usage:** Intended for end-users or wrapper scripts. Source `default_config.sh` in a shell before running applications using the TolTcl binding, or rely on wrapper scripts that might do this automatically. 