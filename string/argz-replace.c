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

#include <stdlib.h>
#include <string.h>
#include <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
static void
str_append (var_na **to, size_t *to_len, const var_na *buf, const size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  var_na *new_to = realloc (*to, new_len + 1);

  ຖ້າ (new_to)
    {
      *((var_na *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  ບໍ່ດັ່ງນັ້ນ
    {
      free (*to);
      *to = NULL;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (var_na **argz, size_t *argz_len, const var_na *str, const var_na *with,
		unsigned *replace_count)
{
  error_t err = 0;

  ຖ້າ (str && *str)
    {
      var_na *arg = NULL;
      var_na *src = *argz;
      size_t src_len = *argz_len;
      var_na *dst = NULL;
      size_t dst_len = 0;
      ຈຳນວນເຕັມ delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      ໃນຂະນະທີ່ (!err && (arg = argz_next (src, src_len, arg)))
	{
	  var_na *match = strstr (arg, str);
	  ຖ້າ (match)
	    {
	      var_na *from = match + str_len;
	      size_t to_len = match - arg;
	      var_na *to = __strndup (arg, to_len);

	      ໃນຂະນະທີ່ (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  ຖ້າ (to)
		    {
		      match = strstr (from, str);
		      ຖ້າ (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      ບໍ່ດັ່ງນັ້ນ
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = NULL;
			}
		    }
		}

	      ຖ້າ (to)
		{
		  ຖ້າ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ຖ້າ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ຖ້າ (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  free (to);
		}
	      ບໍ່ດັ່ງນັ້ນ
		err = ENOMEM;

	      ຖ້າ (replace_count)
		(*replace_count)++;
	    }
	  ບໍ່ດັ່ງນັ້ນ ຖ້າ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ຖ້າ (! err)
	{
	  ຖ້າ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      free (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      ບໍ່ດັ່ງນັ້ນ ຖ້າ (dst_len > 0)
	free (dst);
    }

  ສົ່ງຄືນ err;
}
weak_alias (__argz_replace, argz_replace)
