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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
translate (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *res = _(str);
  __uselocale (oldloc);
  ಹಿಂತಿರುಗಿ res;
}

ಸ್ಥಿರ ಅಕ್ಷರ *
unknown_error (locale_t loc)
{
  ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
ಅಕ್ಷರ *
__strerror_l (ಪೂರ್ಣಾಂಕ errnum, locale_t loc)
{
  ಪೂರ್ಣಾಂಕ saved_errno = errno;
  ಅಕ್ಷರ *err = (ಅಕ್ಷರ *) __get_errlist (errnum);
  ಆದರೆ (__glibc_unlikely (err == ಖಾಲಿ))
    {
      ಆದರೆ (__libc_initial)
	{
	  ರಚನೆ tls_ಆಂತರಿಕ_t *tls_ಆಂತರಿಕ = __glibc_tls_internal ();
	  ಬಿಡುಗಡೆ (tls_ಆಂತರಿಕ->strerror_l_buf);
	  ಆದರೆ (__asprintf (&tls_ಆಂತರಿಕ->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_ಆಂತರಿಕ->strerror_l_buf;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* The memory was freed above.  */
	      tls_ಆಂತರಿಕ->strerror_l_buf = ಖಾಲಿ;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    err = (ಅಕ್ಷರ *) translate (err, loc);

  __set_errno (saved_errno);
  ಹಿಂತಿರುಗಿ err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
