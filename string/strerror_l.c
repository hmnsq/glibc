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

#ಅನ್ತರ್ಭಾವ <libintl.h>
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <tls-internal.h>
#ಅನ್ತರ್ಭಾವ <libc-internal.h>

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *
translate (ಧ್ರುವ ವರ್ಣ *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ಧ್ರುವ ವರ್ಣ *res = _(str);
  __uselocale (oldloc);
  ಪ್ರತ್ಯಾಗಮ res;
}

ಸ್ಥಿರ ವರ್ಣ *
unknown_error (locale_t loc)
{
  ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
ವರ್ಣ *
__strerror_l (ಪೂರ್ಣಾಙ್ಕ errnum, locale_t loc)
{
  ಪೂರ್ಣಾಙ್ಕ saved_errno = errno;
  ವರ್ಣ *err = (ವರ್ಣ *) __get_errlist (errnum);
  ಯದಿ (__glibc_unlikely (err == ರಿಕ್ತ))
    {
      ಯದಿ (__libc_initial)
	{
	  ಸಂರಚನಾ tls_internal_t *tls_internal = __glibc_tls_internal ();
	  ಮುಕ್ತ (tls_internal->strerror_l_buf);
	  ಯದಿ (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  ಅನ್ಯಥಾ
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = ರಿಕ್ತ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      ಅನ್ಯಥಾ
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  ಅನ್ಯಥಾ
    err = (ವರ್ಣ *) translate (err, loc);

  __set_errno (saved_errno);
  ಪ್ರತ್ಯಾಗಮ err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
