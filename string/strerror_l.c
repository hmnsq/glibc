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

#অন্তর্ভাব <libintl.h>
#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <tls-internal.h>
#অন্তর্ভাব <libc-internal.h>

স্থির ধ্রুবক অক্ষর *
translate (ধ্রুবক অক্ষর *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ধ্রুবক অক্ষর *res = _(str);
  __uselocale (oldloc);
  ফেরত res;
}

স্থির অক্ষর *
unknown_error (locale_t loc)
{
  ফেরত (অক্ষর *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
অক্ষর *
__strerror_l (পূর্ণসংখ্যা errnum, locale_t loc)
{
  পূর্ণসংখ্যা saved_errno = errno;
  অক্ষর *err = (অক্ষর *) __get_errlist (errnum);
  যদি (__glibc_unlikely (err == ফাঁকা))
    {
      যদি (__libc_initial)
	{
	  কাঠামো tls_internal_t *tls_internal = __glibc_tls_internal ();
	  মুক্ত (tls_internal->strerror_l_buf);
	  যদি (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  অন্যথা
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = ফাঁকা;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      অন্যথা
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  অন্যথা
    err = (অক্ষর *) translate (err, loc);

  __set_errno (saved_errno);
  ফেরত err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
