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

#ଅନ୍ତର୍ଭାଵ <libintl.h>
#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <tls-internal.h>
#ଅନ୍ତର୍ଭାଵ <libc-internal.h>

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *
translate (ଅଚଳ ଅକ୍ଷର *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ଅଚଳ ଅକ୍ଷର *res = _(str);
  __uselocale (oldloc);
  ଫେରନ୍ତୁ res;
}

ସ୍ଥିର ଅକ୍ଷର *
unknown_error (locale_t loc)
{
  ଫେରନ୍ତୁ (ଅକ୍ଷର *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
ଅକ୍ଷର *
__strerror_l (ପୂର୍ଣ୍ଣସଂଖ୍ୟା errnum, locale_t loc)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା saved_errno = errno;
  ଅକ୍ଷର *err = (ଅକ୍ଷର *) __get_errlist (errnum);
  ଯଦି (__glibc_unlikely (err == ଖାଲି))
    {
      ଯଦି (__libc_initial)
	{
	  ସଂରଚନା tls_internal_t *tls_internal = __glibc_tls_internal ();
	  ମୁକ୍ତ (tls_internal->strerror_l_buf);
	  ଯଦି (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  ଅନ୍ୟଥା
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = ଖାଲି;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      ଅନ୍ୟଥା
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  ଅନ୍ୟଥା
    err = (ଅକ୍ଷର *) translate (err, loc);

  __set_errno (saved_errno);
  ଫେରନ୍ତୁ err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
