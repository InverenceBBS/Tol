# Tar Package

This directory contains the Tcllib `tar` package, providing procedures for creating, reading, and manipulating TAR archives.

## Files

*   `tar.tcl`: The core implementation of the TAR archive handling functionality. Provides procedures for creating, listing, extracting, and checking TAR files.
*   `pkgIndex.tcl`: The package index file, making the `tar` package loadable via Tcl's `package require tar` command.

## Usage

To use this package, load it into your Tcl script:

```tcl
package require tar

# Example Usage (Conceptual - Refer to tar.tcl or Tcllib documentation for exact commands)

# Create a new tar archive
# tar::create archiveName fileList ?options...?

# List the contents of an existing tar archive
# set contents [tar::contents archiveData ?options...?]

# Extract files from a tar archive
# tar::extract archiveData targetDirectory ?options...? ?filePatterns...?

# Check the integrity of a tar archive
# tar::check archiveData ?options...?
```

This package allows Tcl applications to work directly with TAR archive files without needing external command-line tools. 