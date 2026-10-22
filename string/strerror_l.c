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

#અન્તર્ભાવ <libintl.h>
#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <tls-internal.h>
#અન્તર્ભાવ <libc-internal.h>

સ્થિર અચલ અક્ષર *
translate (અચલ અક્ષર *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  અચલ અક્ષર *res = _(str);
  __uselocale (oldloc);
  પાછા res;
}

સ્થિર અક્ષર *
unknown_error (locale_t loc)
{
  પાછા (અક્ષર *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
અક્ષર *
__strerror_l (પૂર્ણાંક errnum, locale_t loc)
{
  પૂર્ણાંક saved_errno = errno;
  અક્ષર *err = (અક્ષર *) __get_errlist (errnum);
  જો (__glibc_unlikely (err == ખાલી))
    {
      જો (__libc_initial)
	{
	  સંરચના tls_internal_t *tls_internal = __glibc_tls_internal ();
	  મુક્ત (tls_internal->strerror_l_buf);
	  જો (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  નહીંતર
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = ખાલી;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      નહીંતર
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  નહીંતર
    err = (અક્ષર *) translate (err, loc);

  __set_errno (saved_errno);
  પાછા err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
