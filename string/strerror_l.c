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

ایستا ثابت نویسه *
translate (ثابت نویسه *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ثابت نویسه *res = _(str);
  __uselocale (oldloc);
  بازگشت res;
}

ایستا نویسه *
unknown_error (locale_t loc)
{
  بازگشت (نویسه *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
نویسه *
__strerror_l (صحیح errnum, locale_t loc)
{
  صحیح saved_errno = errno;
  نویسه *err = (نویسه *) __get_errlist (errnum);
  اگر (__glibc_unlikely (err == پوچ))
    {
      اگر (__libc_initial)
	{
	  ساختار tls_internal_t *tls_internal = __glibc_tls_internal ();
	  آزاد (tls_internal->strerror_l_buf);
	  اگر (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  وگرنه
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = پوچ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      وگرنه
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  وگرنه
    err = (نویسه *) translate (err, loc);

  __set_errno (saved_errno);
  بازگشت err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
