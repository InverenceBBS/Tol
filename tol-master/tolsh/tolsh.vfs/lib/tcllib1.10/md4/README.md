# MD4 Package

This directory contains the Tcllib `md4` package, providing an implementation of the MD4 message-digest algorithm.

**Note:** MD4 is considered cryptographically broken and unsuitable for security-related purposes. It should only be used where required for compatibility with legacy systems.

## Files

*   `md4.tcl`: The pure-Tcl implementation of the MD4 hash algorithm.
*   `md4c.tcl`: A C-accelerated version of the MD4 implementation (likely requires compilation/integration with Tcl's C API).
*   `pkgIndex.tcl`: The package index file for loading the `md4` package.

## Usage

This package computes an MD4 hash (digest) of input data.

```tcl
package require md4

# Example Usage (Conceptual - Refer to .tcl files or Tcllib documentation)

# Calculate MD4 hash of a string
# set hash [md4::md4 "message digest"]

# Calculate MD4 hash of data from a file/channel
# set chan [open data.bin rb]
# set hash [md4::md4 -channel $chan]
# close $chan

# Using HMAC-MD4 (if supported by the specific implementation)
# set hmac [md4::hmac -key secretKey "message digest"]
```

Consult the `.tcl` files or the official Tcllib documentation for specific command syntax and options. Remember the security implications of using MD4. 