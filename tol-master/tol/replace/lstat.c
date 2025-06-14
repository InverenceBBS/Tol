/* Work around the bug in some systems whereby lstat succeeds when
   given the zero-length file name argument.  The lstat from SunOS4.1.4
   has this bug.
   Copyright (C) 1997 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* written by Jim Meyering */

#include <config.h>

/* Disable the definition of lstat to rpl_lstat (from config.h) in this
   file.  Otherwise, we'd get conflicting prototypes for rpl_lstat on
   most systems.  */
#undef lstat

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#ifndef errno
extern int errno;
#endif

/* FIXME: describe.  */

int
rpl_lstat (file, sbuf)
     const char *file;
     struct stat *sbuf;
{
  if (file && *file == 0)
    {
      errno = EINVAL;
      return -1;
    }

  return lstat (file, sbuf);
}
