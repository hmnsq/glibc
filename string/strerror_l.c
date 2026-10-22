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

#ਅਨ੍ਤਰ੍ਭਾਵ <libintl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <tls-internal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-internal.h>

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *
translate (ਅਚਲ ਅੱਖਰ *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ਅਚਲ ਅੱਖਰ *res = _(str);
  __uselocale (oldloc);
  ਵਾਪਸ res;
}

ਸਥਿਰ ਅੱਖਰ *
unknown_error (locale_t loc)
{
  ਵਾਪਸ (ਅੱਖਰ *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
ਅੱਖਰ *
__strerror_l (ਪੂਰਨ errnum, locale_t loc)
{
  ਪੂਰਨ saved_errno = errno;
  ਅੱਖਰ *err = (ਅੱਖਰ *) __get_errlist (errnum);
  ਜੇ (__glibc_unlikely (err == ਨਿਰਾ))
    {
      ਜੇ (__libc_initial)
	{
	  ਬਣਤਰ tls_ਅੰਦਰੂਨੀ_t *tls_ਅੰਦਰੂਨੀ = __glibc_tls_internal ();
	  ਮੁਕਤ (tls_ਅੰਦਰੂਨੀ->strerror_l_buf);
	  ਜੇ (__asprintf (&tls_ਅੰਦਰੂਨੀ->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_ਅੰਦਰੂਨੀ->strerror_l_buf;
	  ਨਹੀਂਤਾਂ
	    {
	      /* The memory was freed above.  */
	      tls_ਅੰਦਰੂਨੀ->strerror_l_buf = ਨਿਰਾ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      ਨਹੀਂਤਾਂ
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  ਨਹੀਂਤਾਂ
    err = (ਅੱਖਰ *) translate (err, loc);

  __set_errno (saved_errno);
  ਵਾਪਸ err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
