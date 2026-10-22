/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#অন্তর্ভাৱ <argz.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  */
error_t
__argz_create (ৱর্ণ *ধ্রুৱ argv[], ৱর্ণ **argz, size_t *len)
{
  পূর্ণাঙ্ক argc;
  size_t tlen = 0;
  ৱর্ণ *ধ্রুৱ *ap;
  ৱর্ণ *p;

  বাবে (argc = 0; argv[argc] != রিক্ত; ++argc)
    tlen += strlen (argv[argc]) + 1;

  যদি (tlen == 0)
    *argz = রিক্ত;
  অন্যথা
    {
      *argz = malloc (tlen);
      যদি (*argz == রিক্ত)
	ঘূৰাই ENOMEM;

      বাবে (p = *argz, ap = argv; *ap; ++ap, ++p)
	p = __stpcpy (p, *ap);
    }
  *len = tlen;

  ঘূৰাই 0;
}
weak_alias (__argz_create, argz_create)
