# README - pop3 Module (tcllib 1.10)

## Overview

This directory contains the `pop3` module from Tcllib 1.10, part of the `tolsh` VFS. This module provides client-side functionality for interacting with POP3 (Post Office Protocol version 3) mail servers.

## Contents

### Files

- `pop3.tcl`: The core Tcl implementation for the POP3 client protocol.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to enable Tcl applications to act as POP3 clients. It allows scripts to connect to POP3 servers, authenticate (USER/PASS), check mail status (STAT), list messages (LIST, UIDL), retrieve messages (RETR), delete messages (DELE), and disconnect (QUIT).

## Appendix

N/A 