## Makefile.am -- Process this file with automake to produce Makefile.in
## Copyright (C) 2003 Bayes Decisi�n, SL
## Author: Daniel Rus <daniel@uponeits.com>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

EXTRA_DIST		= Jamfile

noinst_LTLIBRARIES	= libbgrammar.la

pkginclude_HEADERS	= tol_bgrammar.h tol_bmethod.h tol_boper.h \
			tol_bspfun.h tol_bstruct.h tol_bsyntax.h \
			tol_bsymboltable.h tol_bgencon.h tol_bgenobj.h \
			tol_bgentmp.h tol_bext.h tol_bgrastk.h \
			tol_bnameblock.h

libbgrammar_la_SOURCES	= gra.cpp graacc.cpp graimp.cpp met.cpp \
			opr.cpp oprimp.cpp spfun.cpp spfuninst.cpp \
			str.cpp syn.cpp symboltable.cpp ext_loader.cpp \
			ext.cpp grastk.cpp nameblock.cpp

