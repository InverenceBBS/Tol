# README - log / logger Modules (tcllib 1.10)

## Overview

This directory contains the `log` and `logger` modules from Tcllib 1.10, within the `tolsh` VFS. These modules provide logging facilities for Tcl applications, offering more features than simple `puts` statements.

## Contents

### Files

- `log.tcl`: A basic logging facility, likely offering different log levels (e.g., info, warning, error).
- `logger.tcl`: A more advanced logging framework, potentially inspired by systems like log4j. It likely supports multiple logging levels, hierarchical loggers, and pluggable output destinations (appenders).
- `loggerAppender.tcl`: Defines standard appender types for the `logger` framework (e.g., writing to console, file, rotating files).
- `loggerUtils.tcl`: Utility procedures supporting the `logger` framework.
- `pkgIndex.tcl`: Standard Tcl package index file for the `log` and `logger` modules.

### Subdirectories

- `msgs/`: Contains message catalog files for localizing log messages generated by the modules.

## Purpose

The purpose of these modules is to provide robust and configurable logging for Tcl applications. The `log` package offers a simple interface, while the `logger` package provides a more flexible and powerful system with features like log levels, named loggers, different output formats, and various destinations (appenders) for log messages. This helps in debugging, monitoring, and auditing applications.

## Appendix

N/A 