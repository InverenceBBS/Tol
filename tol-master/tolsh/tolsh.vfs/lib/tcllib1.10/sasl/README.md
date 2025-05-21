# README - sasl Module (tcllib 1.10)

## Overview

This directory contains the `sasl` (Simple Authentication and Security Layer) module from Tcllib 1.10, within the `tolsh` VFS. SASL is a framework for adding authentication support to connection-based protocols (like SMTP, LDAP, IMAP, XMPP).

## Contents

### Files

- `sasl.tcl`: The core implementation of the SASL framework, likely handling negotiation and common mechanisms.
- `ntlm.tcl`: Implementation of the NTLM (NT LAN Manager) SASL authentication mechanism, commonly used in Microsoft environments.
- `gtoken.tcl`: Possibly related to generic token-based authentication or a specific mechanism like GSSAPI or Kerberos tokens within SASL.
- `pkgIndex.tcl`: Standard Tcl package index file for the `sasl` package and potentially its specific mechanism sub-packages.

### Subdirectories

None.

## Purpose

The purpose of this module is to provide Tcl applications with a framework for implementing SASL authentication. It allows clients and servers using various protocols to negotiate and perform authentication using different mechanisms (like PLAIN, LOGIN, CRAM-MD5, DIGEST-MD5, NTLM, etc.) in a standardized way.

## Appendix

N/A 