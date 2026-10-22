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

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
സ്ഥിതം ശൂന്യം
str_append (അക്ഷരം **to, size_t *to_len, സ്ഥിരം അക്ഷരം *buf, സ്ഥിരം size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  അക്ഷരം *new_to = realloc (*to, new_len + 1);

  എങ്കിൽ (new_to)
    {
      *((അക്ഷരം *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  അല്ലെങ്കിൽ
    {
      സ്വതന്ത്രം (*to);
      *to = ശൂന്യ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (അക്ഷരം **argz, size_t *argz_len, സ്ഥിരം അക്ഷരം *str, സ്ഥിരം അക്ഷരം *with,
		unsigned *replace_എണ്ണം)
{
  error_t err = 0;

  എങ്കിൽ (str && *str)
    {
      അക്ഷരം *arg = ശൂന്യ;
      അക്ഷരം *src = *argz;
      size_t src_len = *argz_len;
      അക്ഷരം *dst = ശൂന്യ;
      size_t dst_len = 0;
      പൂർണ്ണസംഖ്യ delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      ആകുമ്പോൾ (!err && (arg = argz_next (src, src_len, arg)))
	{
	  അക്ഷരം *match = strstr (arg, str);
	  എങ്കിൽ (match)
	    {
	      അക്ഷരം *from = match + str_len;
	      size_t to_len = match - arg;
	      അക്ഷരം *to = __strndup (arg, to_len);

	      ആകുമ്പോൾ (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  എങ്കിൽ (to)
		    {
		      match = strstr (from, str);
		      എങ്കിൽ (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      അല്ലെങ്കിൽ
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = ശൂന്യ;
			}
		    }
		}

	      എങ്കിൽ (to)
		{
		  എങ്കിൽ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      എങ്കിൽ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  എങ്കിൽ (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  സ്വതന്ത്രം (to);
		}
	      അല്ലെങ്കിൽ
		err = ENOMEM;

	      എങ്കിൽ (replace_എണ്ണം)
		(*replace_എണ്ണം)++;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      എങ്കിൽ (! err)
	{
	  എങ്കിൽ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      സ്വതന്ത്രം (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      അല്ലെങ്കിൽ എങ്കിൽ (dst_len > 0)
	സ്വതന്ത്രം (dst);
    }

  തിരികെ err;
}
weak_alias (__argz_replace, argz_replace)
