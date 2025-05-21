# AES Package

This directory contains the Tcllib `aes` package, providing procedures for AES (Advanced Encryption Standard) encryption and decryption.

## Files

*   `aes.tcl`: The core implementation of the AES algorithm.
*   `pkgIndex.tcl`: The package index file, making the `aes` package loadable via Tcl's `package require aes` command.

## Usage

To use this package, load it into your Tcl script:

```tcl
package require aes

# Example Usage (Conceptual - Refer to aes.tcl or Tcllib documentation for exact commands)

# Initialize the cipher with a key and mode
# set key [aes::Init mode key iv?]

# Encrypt data
# set encrypted_data [aes::Encrypt key data]

# Decrypt data
# set decrypted_data [aes::Decrypt key data]

# Clean up
# aes::Final key
```

This package allows Tcl applications to perform symmetric encryption and decryption using the widely adopted AES standard. 