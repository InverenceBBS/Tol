# README - mime / smtp Modules (tcllib 1.10)

## Overview

This directory contains the `mime` and `smtp` modules from Tcllib 1.10, within the `tolsh` VFS. These modules provide tools for creating and handling MIME (Multipurpose Internet Mail Extensions) messages and for sending email via SMTP (Simple Mail Transfer Protocol).

## Contents

### Files

- `mime.tcl`: The core implementation for creating, parsing, and manipulating MIME-formatted messages. This includes handling headers, different content types (text, attachments), encodings (like base64, quoted-printable), and multipart structures.
- `smtp.tcl`: Implementation of an SMTP client. It allows Tcl scripts to connect to an SMTP server, authenticate (if necessary), and send email messages (likely constructed using the `mime` module).
- `pkgIndex.tcl`: Standard Tcl package index file for the `mime` and `smtp` modules.

### Subdirectories

None.

## Purpose

The purpose of these modules is to provide comprehensive email handling capabilities for Tcl applications. The `mime` module allows for the construction of complex email messages conforming to MIME standards, while the `smtp` module handles the actual transmission of these messages to a mail server.

## Appendix

N/A 