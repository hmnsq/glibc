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

#അന്തര്ഭാവ <argz.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  */
error_t
__argz_create (അക്ഷരം *സ്ഥിരം argv[], അക്ഷരം **argz, size_t *len)
{
  പൂർണ്ണസംഖ്യ argc;
  size_t tlen = 0;
  അക്ഷരം *സ്ഥിരം *ap;
  അക്ഷരം *p;

  വേണ്ടി (argc = 0; argv[argc] != ശൂന്യ; ++argc)
    tlen += strlen (argv[argc]) + 1;

  എങ്കിൽ (tlen == 0)
    *argz = ശൂന്യ;
  അല്ലെങ്കിൽ
    {
      *argz = malloc (tlen);
      എങ്കിൽ (*argz == ശൂന്യ)
	തിരികെ ENOMEM;

      വേണ്ടി (p = *argz, ap = argv; *ap; ++ap, ++p)
	p = __stpcpy (p, *ap);
    }
  *len = tlen;

  തിരികെ 0;
}
weak_alias (__argz_create, argz_create)
