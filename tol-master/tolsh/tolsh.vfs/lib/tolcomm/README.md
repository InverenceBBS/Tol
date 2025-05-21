# TOL Communication Packages (tolcomm)

This directory contains packages specifically designed for communication related to the TOL environment, likely involving remote connections, client-server interactions, or remote procedure calls (RPC) between TOL instances or between Tcl and TOL.

## Files

*   `rmtps_client.tcl` / `rmtps_client.tol`: Client implementation for a Remote TOL Protocol Server (RMTPS?), possibly using Tcl and TOL code.
*   `tolclient.tcl` / `tolclient.tol`: Generic client implementation for connecting to a TOL server, using Tcl and TOL.
*   `tolserver.tcl`: Implementation of a TOL server component, likely listening for client connections.
*   `tolshared.tcl`: Shared code or utilities used by both client and server components.
*   `tolslave.tcl`: Implementation related to managing slave TOL interpreters or processes for communication.
*   `pkgIndex.tcl`: Package index file for loading the various `tolcomm` components.

## Purpose

This collection of packages provides the core infrastructure for enabling distributed communication and remote interaction within or with the TOL system. It facilitates building client-server applications, remote execution, or data exchange involving TOL.

## Usage

Usage requires understanding the specific protocols and APIs defined within these files.

```tcl
# Conceptual usage
package require tolclient
# or package require tolserver
# or package require rmtps_client

# Client example
# set conn [tolclient::connect host port]
# set result [tolclient::eval $conn {TOL command}]

# Server example
# tolserver::start port ?options?
```

Refer to the individual `.tcl` and `.tol` files for detailed implementation and usage. 