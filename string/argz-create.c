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

#అన్తర్భావ <argz.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  */
error_t
__argz_create (అక్షరం *స్థిరరాశి argv[], అక్షరం **argz, size_t *len)
{
  పూర్ణాంకం argc;
  size_t tlen = 0;
  అక్షరం *స్థిరరాశి *ap;
  అక్షరం *p;

  కొరకు (argc = 0; argv[argc] != ఖాళీ; ++argc)
    tlen += అక్షరశ్రేణి_పొడవు (argv[argc]) + 1;

  ఒకవేళ (tlen == 0)
    *argz = ఖాళీ;
  లేకపోతే
    {
      *argz = జ్ఞాపకం_ఇవ్వు (tlen);
      ఒకవేళ (*argz == ఖాళీ)
	తిరిగి ENOMEM;

      కొరకు (p = *argz, ap = argv; *ap; ++ap, ++p)
	p = __stpcpy (p, *ap);
    }
  *len = tlen;

  తిరిగి 0;
}
weak_alias (__argz_create, argz_create)
