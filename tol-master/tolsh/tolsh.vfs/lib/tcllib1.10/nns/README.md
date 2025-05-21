# NNS Package (Name Name Service?)

This directory contains the Tcllib `nns` package, likely providing functionality related to a name service or directory service.

## Files

*   `nns.tcl`: Core NNS client or library implementation.
*   `nns_auto.tcl`: Possibly related to automatic discovery or configuration of the name service.
*   `server.tcl`: Implementation of an NNS server component.
*   `common.tcl`: Shared utility procedures used by client and/or server components.
*   `pkgIndex.tcl`: Package index file for loading `nns` and related components.

## Purpose

Based on the files, this package likely implements a custom name service protocol allowing Tcl applications to register, lookup, and possibly manage named resources or services within a network or system. It appears to provide both client (`nns.tcl`) and server (`server.tcl`) parts.

## Usage

```tcl
# Conceptual usage - requires specific knowledge of the NNS protocol
package require nns

# Client operations (example)
# nns::connect serverAddress
# set serviceInfo [nns::lookup serviceName]
# nns::register myService $myInfo

# Server operations (example)
# nns::server::start portNumber
```

Refer to the `.tcl` files for detailed implementation and commands. 