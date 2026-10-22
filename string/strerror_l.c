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

#अन्तर्भाव <libintl.h>
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <tls-internal.h>
#अन्तर्भाव <libc-internal.h>

स्थिर ध्रुव वर्ण *
translate (ध्रुव वर्ण *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  ध्रुव वर्ण *res = _(str);
  __uselocale (oldloc);
  पटिनिवत्त res;
}

स्थिर वर्ण *
unknown_error (locale_t loc)
{
  पटिनिवत्त (वर्ण *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
वर्ण *
__strerror_l (पूर्णाङ्क errnum, locale_t loc)
{
  पूर्णाङ्क saved_errno = errno;
  वर्ण *err = (वर्ण *) __get_errlist (errnum);
  सचे (__glibc_unlikely (err == रिक्त))
    {
      सचे (__libc_initial)
	{
	  संरचना tls_internal_t *tls_internal = __glibc_tls_internal ();
	  मुक्त (tls_internal->strerror_l_buf);
	  सचे (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  अञ्ञथा
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = रिक्त;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      अञ्ञथा
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  अञ्ञथा
    err = (वर्ण *) translate (err, loc);

  __set_errno (saved_errno);
  पटिनिवत्त err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
