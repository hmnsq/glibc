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

#அந்தர்பாவ <libintl.h>
#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <tls-internal.h>
#அந்தர்பாவ <libc-internal.h>

நிலையான மாறிலி எழுத்து *
translate (மாறிலி எழுத்து *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  மாறிலி எழுத்து *res = _(str);
  __uselocale (oldloc);
  திரும்பு res;
}

நிலையான எழுத்து *
unknown_error (locale_t loc)
{
  திரும்பு (எழுத்து *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
எழுத்து *
__strerror_l (முழு errnum, locale_t loc)
{
  முழு saved_errno = errno;
  எழுத்து *err = (எழுத்து *) __get_errlist (errnum);
  எனில் (__glibc_unlikely (err == வெற்று))
    {
      எனில் (__libc_initial)
	{
	  கட்டமைப்பு tls_internal_t *tls_internal = __glibc_tls_internal ();
	  விடுவி (tls_internal->strerror_l_buf);
	  எனில் (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  இல்லையெனில்
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = வெற்று;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      இல்லையெனில்
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  இல்லையெனில்
    err = (எழுத்து *) translate (err, loc);

  __set_errno (saved_errno);
  திரும்பு err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
