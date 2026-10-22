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

#شامل <libintl.h>
#شامل <locale.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <tls-internal.h>
#شامل <libc-internal.h>

ساکن ثابت حرف *
translate (ثابت حرف *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ثابت حرف *res = _(str);
  __uselocale (oldloc);
  واپس res;
}

ساکن حرف *
unknown_error (locale_t loc)
{
  واپس (حرف *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
حرف *
__strerror_l (صحیح errnum, locale_t loc)
{
  صحیح saved_errno = errno;
  حرف *err = (حرف *) __get_errlist (errnum);
  اگر (__glibc_unlikely (err == تہی))
    {
      اگر (__libc_initial)
	{
	  ساخت tls_اندرونی_t *tls_اندرونی = __glibc_tls_internal ();
	  آزاد (tls_اندرونی->strerror_l_buf);
	  اگر (__asprintf (&tls_اندرونی->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_اندرونی->strerror_l_buf;
	  ورنہ
	    {
	      /* The memory was freed above.  */
	      tls_اندرونی->strerror_l_buf = تہی;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      ورنہ
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  ورنہ
    err = (حرف *) translate (err, loc);

  __set_errno (saved_errno);
  واپس err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
