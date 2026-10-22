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

#अन्तर्भाव <argz.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  */
error_t
__argz_create (वर्ण *ध्रुव argv[], वर्ण **argz, size_t *len)
{
  पूर्णाङ्क argc;
  size_t tlen = 0;
  वर्ण *ध्रुव *ap;
  वर्ण *p;

  प्रति (argc = 0; argv[argc] != रिक्त; ++argc)
    tlen += strlen (argv[argc]) + 1;

  यदि (tlen == 0)
    *argz = रिक्त;
  अन्यथा
    {
      *argz = malloc (tlen);
      यदि (*argz == रिक्त)
	प्रत्यागम ENOMEM;

      प्रति (p = *argz, ap = argv; *ap; ++ap, ++p)
	p = __stpcpy (p, *ap);
    }
  *len = tlen;

  प्रत्यागम 0;
}
weak_alias (__argz_create, argz_create)
