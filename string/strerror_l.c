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

#समावेश <libintl.h>
#समावेश <locale.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <tls-internal.h>
#समावेश <libc-internal.h>

अटल स्थिर अक्षर *
translate (स्थिर अक्षर *str, locale_t loc)
{
  locale_t oldloc = __uselocale (loc);
  स्थिर अक्षर *res = _(str);
  __uselocale (oldloc);
  वापस res;
}

अटल अक्षर *
unknown_error (locale_t loc)
{
  वापस (अक्षर *) translate ("Unknown error", loc);
}


/* Return a string describing the errno code in ERRNUM.  */
अक्षर *
__strerror_l (पूर्णांक errnum, locale_t loc)
{
  पूर्णांक saved_errno = त्रुटि_सं;
  अक्षर *err = (अक्षर *) __get_errlist (errnum);
  अगर (__glibc_unlikely (err == शून्य))
    {
      अगर (__libc_initial)
	{
	  काष्ठा tls_internal_t *tls_internal = __glibc_tls_internal ();
	  मुक्त (tls_internal->strerror_l_buf);
	  अगर (__asprintf (&tls_internal->strerror_l_buf, "%s%d",
			  translate ("Unknown error ", loc), errnum) > 0)
	    err = tls_internal->strerror_l_buf;
	  अन्यथा
	    {
	      /* The memory was freed above.  */
	      tls_internal->strerror_l_buf = शून्य;
	      /* Provide a fallback translation.  */
	      err = unknown_error (loc);
	    }
	}
      अन्यथा
	/* Secondary namespaces use a different malloc, so cannot
	   participate in the buffer management.  */
	err = unknown_error (loc);
    }
  अन्यथा
    err = (अक्षर *) translate (err, loc);

  __set_errno (saved_errno);
  वापस err;
}
weak_alias (__strerror_l, strerror_l)
libc_hidden_def (__strerror_l)
