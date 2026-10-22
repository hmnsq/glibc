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
__argz_create_sep (स्थिर अक्षर *string, पूर्णांक delim, अक्षर **argz, माप_प्रकार *len)
{
  माप_प्रकार nlen = म_माप (string) + 1;

  अगर (nlen > 1)
    {
      स्थिर अक्षर *rp;
      अक्षर *wp;

      *argz = (अक्षर *) दो_स्मृति (nlen);
      अगर (*argz == शून्य)
	वापस ENOMEM;

      rp = string;
      wp = *argz;
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

      अगर (nlen == 0)
	{
	  मुक्त (*argz);
	  *argz = शून्य;
	  *len = 0;
	}

      *len = nlen;
    }
  अन्यथा
    {
      *argz = शून्य;
      *len = 0;
    }

  वापस 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
