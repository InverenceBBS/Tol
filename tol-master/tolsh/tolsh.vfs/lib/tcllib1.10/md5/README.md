# MD5 Package

This directory contains the Tcllib `md5` package, providing an implementation of the MD5 message-digest algorithm.

**Note:** While widely used historically, MD5 is known to have significant cryptographic weaknesses (especially collision resistance) and is generally not recommended for new security-sensitive applications like digital signatures or password hashing. Use stronger algorithms like SHA-256 or SHA-3 where possible. MD5 might still be acceptable for non-cryptographic checksums.

## Files

*   `md5.tcl`: The pure-Tcl implementation of the MD5 hash algorithm.
*   `md5c.tcl`: A C-accelerated version of the MD5 implementation.
*   `md5x.tcl`: Possibly an extended or alternative MD5 implementation.
*   `pkgIndex.tcl`: The package index file for loading the `md5` package.

## Usage

This package computes an MD5 hash (digest) of input data.

```tcl
package require md5

# Example Usage (Conceptual - Refer to .tcl files or Tcllib documentation)

# Calculate MD5 hash of a string
# set hash [md5::md5 "message digest"]

# Calculate MD5 hash of data from a file/channel
# set chan [open data.bin rb]
# set hash [md5::md5 -channel $chan]
# close $chan

# Using HMAC-MD5
# set hmac [md5::hmac -key secretKey "message digest"]
```

Consult the `.tcl` files or the official Tcllib documentation for specific command syntax and options. Be mindful of the security limitations of MD5. 