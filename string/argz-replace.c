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

#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
સ્થિર શૂન્ય
str_append (અક્ષર **to, size_t *to_len, અચલ અક્ષર *buf, અચલ size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  અક્ષર *new_to = realloc (*to, new_len + 1);

  જો (new_to)
    {
      *((અક્ષર *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  નહીંતર
    {
      મુક્ત (*to);
      *to = ખાલી;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (અક્ષર **argz, size_t *argz_len, અચલ અક્ષર *str, અચલ અક્ષર *with,
		unsigned *replace_ગણતરી)
{
  error_t err = 0;

  જો (str && *str)
    {
      અક્ષર *arg = ખાલી;
      અક્ષર *src = *argz;
      size_t src_len = *argz_len;
      અક્ષર *dst = ખાલી;
      size_t dst_len = 0;
      પૂર્ણાંક delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      જ્યારે (!err && (arg = argz_next (src, src_len, arg)))
	{
	  અક્ષર *match = strstr (arg, str);
	  જો (match)
	    {
	      અક્ષર *from = match + str_len;
	      size_t to_len = match - arg;
	      અક્ષર *to = __strndup (arg, to_len);

	      જ્યારે (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  જો (to)
		    {
		      match = strstr (from, str);
		      જો (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      નહીંતર
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = ખાલી;
			}
		    }
		}

	      જો (to)
		{
		  જો (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      જો (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  જો (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  મુક્ત (to);
		}
	      નહીંતર
		err = ENOMEM;

	      જો (replace_ગણતરી)
		(*replace_ગણતરી)++;
	    }
	  નહીંતર જો (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      જો (! err)
	{
	  જો (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      મુક્ત (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      નહીંતર જો (dst_len > 0)
	મુક્ત (dst);
    }

  પાછા err;
}
weak_alias (__argz_replace, argz_replace)
