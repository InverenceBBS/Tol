# DNS Package

This directory contains the Tcllib `dns` package, providing utilities for Domain Name System (DNS) lookups and related IP address manipulations.

## Files

*   `dns.tcl`: Core DNS query implementation.
*   `ip.tcl`: Basic IP address validation and manipulation utilities.
*   `ipMore.tcl`: More advanced IP address utilities (possibly CIDR, subnets, etc.).
*   `ipMoreC.tcl`: Likely a C-accelerated version of `ipMore.tcl`.
*   `msgs/`: Directory containing message catalog files for internationalization.
*   `pkgIndex.tcl`: Package index file for loading the `dns` and related packages.
*   `resolv.tcl`: Utilities for interacting with the system's resolver configuration (e.g., `/etc/resolv.conf`).
*   `spf.tcl`: Implementation related to Sender Policy Framework (SPF) record lookups.

## Usage

This package allows Tcl applications to perform various DNS queries (A, MX, TXT, SPF, etc.) and work with IP addresses.

```tcl
package require dns

# Example Usage (Conceptual - Refer to .tcl files or Tcllib documentation)

# Resolve a hostname to an IP address (A record)
# set ip [dns::resolve hostname]

# Get Mail Exchanger (MX) records
# set mx_records [dns::resolve hostname -type MX]

# Validate an IP address
# set is_valid [ip::valid $address]

# Check SPF record
# set spf_result [dns::spf::check $domain $ip $sender]
```

Consult the specific Tcl files or the official Tcllib documentation for details on available procedures and options. 