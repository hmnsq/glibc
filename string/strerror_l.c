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

#അന്തര്ഭാവ <libintl.h>
#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <tls-internal.h>
#അന്തര്ഭാവ <libc-internal.h>

സ്ഥിതം സ്ഥിരം അക്ഷരം *
translate (സ്ഥിരം അക്ഷരം *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  സ്ഥിരം അക്ഷരം *res = _(str);
  __uselocale (oldloc);
  തിരികെ res;
}

സ്ഥിതം അക്ഷരം *
unknown_error (locale_t loc)
{
  തിരികെ (അക്ഷരം *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
അക്ഷരം *
__strerror_l (പൂർണ്ണസംഖ്യ errnum, locale_t loc)
{
  പൂർണ്ണസംഖ്യ saved_errno = errno;
  അക്ഷരം *err = (അക്ഷരം *) __get_errlist (errnum);
  എങ്കിൽ (__glibc_unlikely (err == ശൂന്യ))
    {
      എങ്കിൽ (__libc_initial)
	{
	  ഘടന tls_internal_t *tls_internal = __glibc_tls_internal ();
	  സ്വതന്ത്രം (tls_internal->strerror_l_buf);
	  എങ്കിൽ (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  അല്ലെങ്കിൽ
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = ശൂന്യ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      അല്ലെങ്കിൽ
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  അല്ലെങ്കിൽ
    err = (അക്ഷരം *) translate (err, loc);

  __set_errno (saved_errno);
  തിരികെ err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
