# uuid Package

This directory contains the Tcllib `uuid` package, providing procedures for generating Universally Unique Identifiers (UUIDs), also known as Globally Unique Identifiers (GUIDs).

## Files

*   `uuid.tcl`: The core implementation for generating UUIDs. It likely supports different UUID versions (e.g., Version 1 based on time and MAC address, Version 4 based on random numbers).
*   `pkgIndex.tcl`: The package index file, making the `uuid` package loadable via Tcl's `package require uuid` command.

## Purpose

This package allows Tcl applications to generate standard UUIDs. UUIDs are designed to be unique across space and time and are commonly used as identifiers for database keys, objects, sessions, or any entity requiring a unique identifier without relying on a central authority.

## Usage

```tcl
package require uuid

# Example Usage (Conceptual - Refer to uuid.tcl or Tcllib documentation)

# Generate a default UUID (likely version 4)
# set myUuid [uuid::generate]

# Generate a specific version (if supported)
# set timeUuid [uuid::generate -version 1]

# Validate a UUID string
# if {[uuid::is $someString]} {
#    puts "Valid UUID"
# }
``` 