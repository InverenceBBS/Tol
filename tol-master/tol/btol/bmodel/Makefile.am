## Makefile.am -- Process this file with automake to produce Makefile.in
## Copyright (C) 2003-2008, Bayes Inference, SA
## Written by Daniel Rus Morales <daniel@uponeits.com>
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

noinst_LTLIBRARIES	= libbmodel.la
pkginclude_HEADERS	= tol_baia.h tol_bmaia.h tol_bestim.h \
			tol_bmodel.h
libbmodel_la_SOURCES	= aia.cpp maia.cpp estim.cpp foread.cpp modcalc.cpp \
			 moddiag.cpp model.cpp modprev.cpp sparselinreg.cpp

if HAVE_cholmod_CPPFLAGS
  libbmodel_la_CPPFLAGS = $(cholmod_CPPFLAGS)
endif
