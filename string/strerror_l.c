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

#ضمن <libintl.h>
#ضمن <locale.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <tls-internal.h>
#ضمن <libc-internal.h>

ساكن ثابت حرف *
translate (ثابت حرف *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ثابت حرف *res = _(str);
  __uselocale (oldloc);
  أرجع res;
}

ساكن حرف *
unknown_error (locale_t loc)
{
  أرجع (حرف *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
حرف *
__strerror_l (صحيح errnum, locale_t loc)
{
  صحيح saved_errno = errno;
  حرف *err = (حرف *) __get_errlist (errnum);
  إذا (__glibc_unlikely (err == عدم))
    {
      إذا (__libc_initial)
	{
	  بنية tls_internal_t *tls_internal = __glibc_tls_internal ();
	  حرر (tls_internal->strerror_l_buf);
	  إذا (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  وإلا
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = عدم;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      وإلا
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  وإلا
    err = (حرف *) translate (err, loc);

  __set_errno (saved_errno);
  أرجع err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
