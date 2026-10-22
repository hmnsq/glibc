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

#समावेश <argz.h>
#समावेश <stdlib.h>
#समावेश <string.h>

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  */
error_t
__argz_create (अक्षर *स्थिर argv[], अक्षर **argz, माप_प्रकार *len)
{
  पूर्णांक argc;
  माप_प्रकार tlen = 0;
  अक्षर *स्थिर *ap;
  अक्षर *p;

  क्रम (argc = 0; argv[argc] != शून्य; ++argc)
    tlen += म_माप (argv[argc]) + 1;

  अगर (tlen == 0)
    *argz = शून्य;
  अन्यथा
    {
      *argz = दो_स्मृति (tlen);
      अगर (*argz == शून्य)
	वापस ENOMEM;

      क्रम (p = *argz, ap = argv; *ap; ++ap, ++p)
	p = __stpcpy (p, *ap);
    }
  *len = tlen;

  वापस 0;
}
weak_alias (__argz_create, argz_create)
