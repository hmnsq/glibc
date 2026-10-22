/* Copyright (C) 2007-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <libintl.h>
#అన్తర్భావ <locale.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <tls-internal.h>
#అన్తర్భావ <libc-internal.h>

స్థిర స్థిరరాశి అక్షరం *
translate (స్థిరరాశి అక్షరం *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  స్థిరరాశి అక్షరం *res = _(str);
  __uselocale (oldloc);
  తిరిగి res;
}

స్థిర అక్షరం *
unknown_error (locale_t loc)
{
  తిరిగి (అక్షరం *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
అక్షరం *
__strerror_l (పూర్ణాంకం errnum, locale_t loc)
{
  పూర్ణాంకం saved_errno = errno;
  అక్షరం *err = (అక్షరం *) __get_errlist (errnum);
  ఒకవేళ (__glibc_unlikely (err == ఖాళీ))
    {
      ఒకవేళ (__libc_initial)
	{
	  నిర్మాణం tls_అంతర్గత_t *tls_అంతర్గత = __glibc_tls_internal ();
	  విడుదల (tls_అంతర్గత->strerror_l_buf);
	  ఒకవేళ (__asprintf (&tls_అంతర్గత->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_అంతర్గత->strerror_l_buf;
	  లేకపోతే
	    {
	      /* The memory was freed above.  */
	      tls_అంతర్గత->strerror_l_buf = ఖాళీ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      లేకపోతే
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  లేకపోతే
    err = (అక్షరం *) translate (err, loc);

  __set_errno (saved_errno);
  తిరిగి err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
