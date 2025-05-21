# Tcl Configuration Helpers (`tol-master/tolbaseBLT/tclconfig/`)

## Overview

This folder mirrors the standard `tclconfig` directory distributed with many
Tcl extensions. It contains Autoconf macros and template scripts used to detect
Tcl/Tk installations and compiler settings during the build.

## Contents

- `tcl.m4`, `toltk.m4` – Autoconf macros for locating Tcl/Tk headers and
  libraries.
- `install-sh`, `missing` – Portable install scripts from the GNU build system.
- `README.txt` – Upstream documentation explaining how these files should be
  used.

## Purpose

Including these files allows the tolbaseBLT project to use the same configure
logic as other Tcl extensions when built with Autoconf.

## Appendix

- **Technology:** GNU Autoconf, shell scripts.
- **Usage:** Refer to `README.txt` for guidance when regenerating `configure` or
  integrating with an Autoconf-based build.
