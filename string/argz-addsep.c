/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#समावेश <argz.h>
#समावेश <errno.h>
#समावेश <stdlib.h>
#समावेश <string.h>


error_t
__argz_add_sep (अक्षर **argz, माप_प्रकार *argz_len, स्थिर अक्षर *string, पूर्णांक delim)
{
  माप_प्रकार nlen = म_माप (string) + 1;

  अगर (nlen > 1)
    {
      स्थिर अक्षर *rp;
      अक्षर *wp;

      *argz = (अक्षर *) पुनः_स्मृति (*argz, *argz_len + nlen);
      अगर (*argz == शून्य)
	वापस ENOMEM;

      wp = *argz + *argz_len;
      rp = string;
      करो
	अगर (*rp == delim)
	  {
	    अगर (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    अन्यथा
	      --nlen;
	  }
	अन्यथा
	  *wp++ = *rp;
      जबतक (*rp++ != '\0');

      *argz_len += nlen;
    }

  वापस 0;
}
weak_alias (__argz_add_sep, argz_add_sep)
