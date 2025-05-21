# FTP Client Package

This directory contains the Tcllib `ftp` package, providing client-side functionality for interacting with FTP (File Transfer Protocol) servers.

## Files

*   `ftp.tcl`: The core implementation of the FTP client protocol.
*   `ftp_geturl.tcl`: A utility potentially focused on retrieving files via FTP URLs.
*   `pkgIndex.tcl`: The package index file for loading the `ftp` package and its components.

## Usage

This package enables Tcl applications to connect to FTP servers, navigate directories, list files, and transfer files (upload/download).

```tcl
package require ftp

# Example Usage (Conceptual - Refer to ftp.tcl or Tcllib documentation)

# Connect to an FTP server
# set conn [ftp::Open host user password ?options...?]

# Change directory
# ftp::Cd $conn remoteDirectory

# List files
# set fileList [ftp::Nlst $conn ?path...?]

# Download a file
# ftp::Get $conn remoteFile ?localFile?]

# Upload a file
# ftp::Put $conn localFile ?remoteFile?]

# Close the connection
# ftp::Close $conn
```

Consult the `ftp.tcl` file or the official Tcllib documentation for detailed command usage and options. 