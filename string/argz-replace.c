/* String replacement in an argz vector
   Copyright (C) 1997-2026 Free Software Foundation, Inc.
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

#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
अटल व्योम
str_append (अक्षर **to, माप_प्रकार *to_len, स्थिर अक्षर *buf, स्थिर माप_प्रकार buf_len)
{
  माप_प्रकार new_len = *to_len + buf_len;
  अक्षर *new_to = पुनः_स्मृति (*to, new_len + 1);

  अगर (new_to)
    {
      *((अक्षर *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  अन्यथा
    {
      मुक्त (*to);
      *to = शून्य;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (अक्षर **argz, माप_प्रकार *argz_len, स्थिर अक्षर *str, स्थिर अक्षर *with,
		अचिन्हित *replace_गिनती)
{
  error_t err = 0;

  अगर (str && *str)
    {
      अक्षर *arg = शून्य;
      अक्षर *src = *argz;
      माप_प्रकार src_len = *argz_len;
      अक्षर *dst = शून्य;
      माप_प्रकार dst_len = 0;
      पूर्णांक delayed_copy = 1;	/* True while we've avoided copying anything.  */
      माप_प्रकार str_len = म_माप (str), with_len = म_माप (with);

      जबतक (!err && (arg = argz_अग्र (src, src_len, arg)))
	{
	  अक्षर *match = म_माला (arg, str);
	  अगर (match)
	    {
	      अक्षर *from = match + str_len;
	      माप_प्रकार to_len = match - arg;
	      अक्षर *to = __strndup (arg, to_len);

	      जबतक (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  अगर (to)
		    {
		      match = म_माला (from, str);
		      अगर (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      अन्यथा
			{
			  str_append (&to, &to_len, from, म_माप (from));
			  from = शून्य;
			}
		    }
		}

	      अगर (to)
		{
		  अगर (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      अगर (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  अगर (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  मुक्त (to);
		}
	      अन्यथा
		err = ENOMEM;

	      अगर (replace_गिनती)
		(*replace_गिनती)++;
	    }
	  अन्यथा अगर (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      अगर (! err)
	{
	  अगर (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      मुक्त (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      अन्यथा अगर (dst_len > 0)
	मुक्त (dst);
    }

  वापस err;
}
weak_alias (__argz_replace, argz_replace)
