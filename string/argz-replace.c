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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
ସ୍ଥିର ଶୂନ୍ୟ
str_append (ଅକ୍ଷର **to, size_t *to_len, ଅଚଳ ଅକ୍ଷର *buf, ଅଚଳ size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  ଅକ୍ଷର *new_to = realloc (*to, new_len + 1);

  ଯଦି (new_to)
    {
      *((ଅକ୍ଷର *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  ଅନ୍ୟଥା
    {
      ମୁକ୍ତ (*to);
      *to = ଖାଲି;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (ଅକ୍ଷର **argz, size_t *argz_len, ଅଚଳ ଅକ୍ଷର *str, ଅଚଳ ଅକ୍ଷର *with,
		unsigned *replace_ଗଣନା)
{
  error_t err = 0;

  ଯଦି (str && *str)
    {
      ଅକ୍ଷର *arg = ଖାଲି;
      ଅକ୍ଷର *src = *argz;
      size_t src_len = *argz_len;
      ଅକ୍ଷର *dst = ଖାଲି;
      size_t dst_len = 0;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      ଯେତେବେଳେ (!err && (arg = argz_next (src, src_len, arg)))
	{
	  ଅକ୍ଷର *match = strstr (arg, str);
	  ଯଦି (match)
	    {
	      ଅକ୍ଷର *from = match + str_len;
	      size_t to_len = match - arg;
	      ଅକ୍ଷର *to = __strndup (arg, to_len);

	      ଯେତେବେଳେ (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  ଯଦି (to)
		    {
		      match = strstr (from, str);
		      ଯଦି (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      ଅନ୍ୟଥା
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = ଖାଲି;
			}
		    }
		}

	      ଯଦି (to)
		{
		  ଯଦି (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ଯଦି (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ଯଦି (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  ମୁକ୍ତ (to);
		}
	      ଅନ୍ୟଥା
		err = ENOMEM;

	      ଯଦି (replace_ଗଣନା)
		(*replace_ଗଣନା)++;
	    }
	  ଅନ୍ୟଥା ଯଦି (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ଯଦି (! err)
	{
	  ଯଦି (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      ମୁକ୍ତ (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (dst_len > 0)
	ମୁକ୍ତ (dst);
    }

  ଫେରନ୍ତୁ err;
}
weak_alias (__argz_replace, argz_replace)
