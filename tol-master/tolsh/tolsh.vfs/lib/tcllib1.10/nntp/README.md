# README - nntp Module (tcllib 1.10)

## Overview

This directory contains the `nntp` module from Tcllib 1.10, within the `tolsh` VFS. This module provides client-side functionality for interacting with NNTP (Network News Transfer Protocol) servers, used for accessing Usenet newsgroups.

## Contents

### Files

- `nntp.tcl`: The core Tcl implementation for the NNTP client protocol.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to enable Tcl applications to act as NNTP clients. It allows scripts to connect to news servers, list available newsgroups (LIST), select a group (GROUP), retrieve article headers (HEAD, HDR, XHDR) or full articles (ARTICLE, BODY), and post new articles (POST).

## Appendix

N/A 