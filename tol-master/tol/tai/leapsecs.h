/* leapsecs.h: TAI Library

   Copyright (C) 2005 - Free Software Foundation
   Author: D. J. Bernstein <djb@cr.yp.to>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.
 */

#ifndef LEAPSECS_H
#define LEAPSECS_H

#ifdef WIN32
#  define LEAPSECS_DATFILE_DIR .
#endif

#include <tai/tai_common.h>

BEGIN_DECLS

TAI_API extern int leapsecs_init();
TAI_API extern int leapsecs_read();

TAI_API extern void leapsecs_add();
TAI_API extern int leapsecs_sub();

END_DECLS

#endif
