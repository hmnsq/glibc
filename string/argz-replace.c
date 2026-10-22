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

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
స్థిర శూన్య
str_append (అక్షరం **గమ్యం, size_t *గమ్యం_len, స్థిరరాశి అక్షరం *buf, స్థిరరాశి size_t buf_len)
{
  size_t new_len = *గమ్యం_len + buf_len;
  అక్షరం *new_గమ్యం = realloc (*గమ్యం, new_len + 1);

  ఒకవేళ (new_గమ్యం)
    {
      *((అక్షరం *) __mempcpy (new_గమ్యం + *గమ్యం_len, buf, buf_len)) = '\0';
      *గమ్యం = new_గమ్యం;
      *గమ్యం_len = new_len;
    }
  లేకపోతే
    {
      విడుదల (*గమ్యం);
      *గమ్యం = ఖాళీ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (అక్షరం **argz, size_t *argz_len, స్థిరరాశి అక్షరం *str, స్థిరరాశి అక్షరం *with,
		గుర్తులేని *replace_లెక్క)
{
  error_t err = 0;

  ఒకవేళ (str && *str)
    {
      అక్షరం *arg = ఖాళీ;
      అక్షరం *src = *argz;
      size_t src_len = *argz_len;
      అక్షరం *dst = ఖాళీ;
      size_t dst_len = 0;
      పూర్ణాంకం delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = అక్షరశ్రేణి_పొడవు (str), with_len = అక్షరశ్రేణి_పొడవు (with);

      అయితే (!err && (arg = argz_తదుపరి (src, src_len, arg)))
	{
	  అక్షరం *సరిపోలిక = అక్షరశ్రేణి_శోధన (arg, str);
	  ఒకవేళ (సరిపోలిక)
	    {
	      అక్షరం *from = సరిపోలిక + str_len;
	      size_t గమ్యం_len = సరిపోలిక - arg;
	      అక్షరం *గమ్యం = __strndup (arg, గమ్యం_len);

	      అయితే (గమ్యం && from)
		{
		  str_append (&గమ్యం, &గమ్యం_len, with, with_len);
		  ఒకవేళ (గమ్యం)
		    {
		      సరిపోలిక = అక్షరశ్రేణి_శోధన (from, str);
		      ఒకవేళ (సరిపోలిక)
			{
			  str_append (&గమ్యం, &గమ్యం_len, from, సరిపోలిక - from);
			  from = సరిపోలిక + str_len;
			}
		      లేకపోతే
			{
			  str_append (&గమ్యం, &గమ్యం_len, from, అక్షరశ్రేణి_పొడవు (from));
			  from = ఖాళీ;
			}
		    }
		}

	      ఒకవేళ (గమ్యం)
		{
		  ఒకవేళ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ఒకవేళ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ఒకవేళ (! err)
		    err = __argz_add (&dst, &dst_len, గమ్యం);
		  విడుదల (గమ్యం);
		}
	      లేకపోతే
		err = ENOMEM;

	      ఒకవేళ (replace_లెక్క)
		(*replace_లెక్క)++;
	    }
	  లేకపోతే ఒకవేళ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ఒకవేళ (! err)
	{
	  ఒకవేళ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      విడుదల (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      లేకపోతే ఒకవేళ (dst_len > 0)
	విడుదల (dst);
    }

  తిరిగి err;
}
weak_alias (__argz_replace, argz_replace)
