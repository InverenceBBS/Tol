# Base64 / Uuencode / Yencode Packages

This directory contains Tcllib packages for various binary-to-text encoding schemes.

## Files

*   `base64.tcl`: Core implementation for Base64 encoding/decoding (RFC 4648).
*   `base64c.tcl`: Wrapper for a potential C-accelerated version of Base64.
*   `uuencode.tcl`: Implementation for Uuencode and Uudecode.
*   `yencode.tcl`: Implementation for Yencode and Ydecode.
*   `pkgIndex.tcl`: Package index file loading `base64`, `uuencode`, and `yencode` packages.

## Purpose

These packages provide standard methods for encoding binary data into ASCII text formats, suitable for transmission via email (MIME), inclusion in XML/HTML, or other text-based protocols.

## Usage

```tcl
package require base64
# or package require uuencode
# or package require yencode

# Base64 Example
# set encoded [::base64::encode $binaryData]
# set decoded [::base64::decode $encodedString]

# Uuencode Example
# set encoded [::uuencode::encode $binaryData ?fileName? ?fileMode?]
# set decoded [::uuencode::decode $encodedString]

# Yencode Example
# set encoded [::yencode::encode $binaryData]
# set decoded [::yencode::decode $encodedString]
```

Refer to the specific `.tcl` files or Tcllib documentation for details. 