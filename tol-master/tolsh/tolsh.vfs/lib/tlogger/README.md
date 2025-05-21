# tlogger Package

This directory contains the `tlogger` package.

## Files

*   `tlogger.tcl`: The core implementation. Given the name, it likely provides a logging facility, possibly tailored for TOL or a specific application within the TOL environment. It might be simpler than Tcllib's `log` or `logger` packages.
*   `pkgIndex.tcl`: The package index file for loading `tlogger`.

## Purpose

Provides a mechanism for logging messages within Tcl scripts, potentially with specific features or formatting suitable for the TOL system.

## Usage

```tcl
package require tlogger

# Conceptual usage - requires inspecting tlogger.tcl
# tlogger::log level message
# tlogger::info "An informational message"
# tlogger::error "An error occurred"
```

Refer to `tlogger.tcl` for specific commands and functionality. 