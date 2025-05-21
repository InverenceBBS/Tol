# RIPEMD Packages

This directory contains Tcllib implementations of the RIPEMD (RACE Integrity Primitives Evaluation Message Digest) hash functions.

## Files

*   `ripemd128.tcl`: Implementation of the RIPEMD-128 hash algorithm.
*   `ripemd160.tcl`: Implementation of the RIPEMD-160 hash algorithm.
*   `pkgIndex.tcl`: The package index file, making the `ripemd128` and `ripemd160` packages loadable via `package require`.

## Usage

These packages provide commands to compute RIPEMD message digests.

```tcl
package require ripemd160
# or package require ripemd128

# Example Usage (Conceptual - Refer to .tcl files or Tcllib documentation)

# Calculate hash of a string
# set hash [ripemd::ripemd160 "message digest"]

# Calculate hash of data from a channel
# set hash [ripemd::ripemd160 -channel $chan]

# Using HMAC with RIPEMD
# set hmac_key "key"
# set hmac [ripemd::hmac -key $hmac_key "message digest"]
```

These algorithms are used for data integrity checks and other cryptographic applications. RIPEMD-160 is generally considered more secure than RIPEMD-128. 