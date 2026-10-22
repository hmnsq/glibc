/* Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#अन्तर्भाव <assert.h>
#अन्तर्भाव <langinfo.h>
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE अक्षर
# define USTRING_TYPE अचिन्हित अक्षर
# define STRXFRM __strxfrm_l
# define STRLEN म_माप
# define STPNCPY __stpncpy
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#endif

#define CONCAT(a,b) CONCAT1(a,b)
#define CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#define SMALL_STR_SIZE 4095

#अन्तर्भाव "../locale/localeinfo.h"
#अन्तर्भाव WEIGHT_H

/* Group locale data for shorter parameter lists.  */
प्रकारव्याख्या संरचना
{
  uint32_t nrules;
  अचिन्हित अक्षर *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
स्थिर पूर्णांक
utf8_encode (अक्षर *buf, पूर्णांक val)
{
  पूर्णांक retval;

  जर (val < 0x80)
    {
      *buf++ = (अक्षर) val;
      retval = 1;
    }
  अन्यथा
    {
      पूर्णांक step;

      साठी (step = 2; step < 6; ++step)
	जर ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  थांबा;
      retval = step;

      *buf = (अचिन्हित अक्षर) (~0xff >> step);
      --step;
      करा
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      पर्यंत (--step > 0);
      *buf |= val;
    }

  परत retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
स्थिर __always_inline माप_प्रकार
find_idx (स्थिरांक USTRING_TYPE **us, int32_t *weight_idx,
	  अचिन्हित अक्षर *rule_idx, स्थिरांक locale_data_t *l_data, स्थिरांक पूर्णांक pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  माप_प्रकार len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  साठी (पूर्णांक i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  परत len;
}

स्थिर पूर्णांक
find_position (स्थिरांक USTRING_TYPE *us, स्थिरांक locale_data_t *l_data,
	       स्थिरांक पूर्णांक pass)
{
  int32_t weight_idx;
  अचिन्हित अक्षर rule_idx;
  स्थिरांक USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  परत l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
स्थिर माप_प्रकार
do_xfrm (स्थिरांक USTRING_TYPE *usrc, STRING_TYPE *dest, माप_प्रकार n,
	 स्थिरांक locale_data_t *l_data)
{
  int32_t weight_idx;
  अचिन्हित अक्षर rule_idx;
  uint32_t pass;
  माप_प्रकार needed = 0;
  माप_प्रकार last_needed;

  /* Now the passes over the weights.  */
  साठी (pass = 0; pass < l_data->nrules; ++pass)
    {
      माप_प्रकार backw_len = 0;
      last_needed = needed;
      स्थिरांक USTRING_TYPE *cur = usrc;
      स्थिरांक USTRING_TYPE *backw_start = रिक्त;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      पूर्णांक position = find_position (cur, l_data, pass);

      जर (position == 0)
	{
	  पर्यंत (*cur != L('\0'))
	    {
	      स्थिरांक USTRING_TYPE *pos = cur;
	      माप_प्रकार len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      पूर्णांक rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      जर ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  जर (backw_start != रिक्त)
		    {
		      साठी (माप_प्रकार i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  अचिन्हित अक्षर rule_idx;
			  माप_प्रकार len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  जर (needed + i < n)
			    साठी (माप_प्रकार j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  जर (needed + len < n)
		    पर्यंत (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  अन्यथा
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  जर (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  जर (backw_start != रिक्त)
	    {
	      साठी (माप_प्रकार i = backw_len; i > 0; )
		{
		  माप_प्रकार len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  जर (needed + i < n)
		    साठी (माप_प्रकार j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      अन्यथा
	{
	  पूर्णांक val = 1;
#ifndef WIDE_CHAR_VERSION
	  अक्षर buf[7];
	  माप_प्रकार buflen;
#endif
	  माप_प्रकार i;

	  पर्यंत (*cur != L('\0'))
	    {
	      स्थिरांक USTRING_TYPE *pos = cur;
	      माप_प्रकार len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      पूर्णांक rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      जर ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  जर (backw_start != रिक्त)
		    {
		      साठी (माप_प्रकार p = backw_len; p > 0; p--)
			{
			  माप_प्रकार len;
			  int32_t weight_idx;
			  अचिन्हित अक्षर rule_idx;
			  स्थिरांक USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  साठी (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  जर (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      जर (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  साठी (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      जर (needed + buflen + len < n)
				{
				  साठी (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  साठी (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  अन्यथा
			    ++val;
			}

		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  जर (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      जर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  साठी (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      जर (needed + buflen + len < n)
			{
			  साठी (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  साठी (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  जर (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  जर (backw_start != रिक्त)
	    {
	      साठी (माप_प्रकार p = backw_len; p > 0; p--)
		{
		  माप_प्रकार len;
		  int32_t weight_idx;
		  अचिन्हित अक्षर rule_idx;
		  स्थिरांक USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  साठी (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  जर (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      जर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  साठी (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      जर (needed + buflen + len < n)
			{
			  साठी (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  साठी (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      जर (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  जर (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      जर (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  परत needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
स्थिर माप_प्रकार
do_xfrm_cached (STRING_TYPE *dest, माप_प्रकार n, स्थिरांक locale_data_t *l_data,
		माप_प्रकार idxmax, int32_t *idxarr, स्थिरांक अचिन्हित अक्षर *rulearr)
{
  uint32_t nrules = l_data->nrules;
  अचिन्हित अक्षर *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  माप_प्रकार needed = 0;
  माप_प्रकार last_needed;
  माप_प्रकार idxcnt;

  /* Now the passes over the weights.  */
  साठी (pass = 0; pass < nrules; ++pass)
    {
      माप_प्रकार backw_stop = ~0ul;
      पूर्णांक rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      पूर्णांक position = rule & sort_position;

      last_needed = needed;
      जर (position == 0)
	{
	  साठी (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      जर ((rule & sort_forward) != 0)
		{
		  माप_प्रकार len;

		  जर (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      माप_प्रकार backw;

		      साठी (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  जर (needed + len < n)
			    पर्यंत (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  अन्यथा
			    {
				/* No more characters fit into the buffer.  */
			      needed += len;
			      idxarr[backw] += len;
			    }
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  जर (needed + len < n)
		    पर्यंत (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  अन्यथा
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      अन्यथा
		{
		  /* Remember where the backwards series started.  */
		  जर (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  जर (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      माप_प्रकार backw;

	      backw = idxcnt;
	      पर्यंत (backw > backw_stop)
		{
		  माप_प्रकार len = weights[idxarr[--backw]++];

		  जर (needed + len < n)
		    पर्यंत (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  अन्यथा
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      अन्यथा
	{
	  पूर्णांक val = 1;
#ifndef WIDE_CHAR_VERSION
	  अक्षर buf[7];
	  माप_प्रकार buflen;
#endif
	  माप_प्रकार i;

	  साठी (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      जर ((rule & sort_forward) != 0)
		{
		  माप_प्रकार len;

		  जर (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      माप_प्रकार backw;

		      साठी (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  जर (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      जर (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  साठी (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      जर (needed + buflen + len < n)
				{
				  साठी (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  साठी (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  अन्यथा
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  जर (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      जर (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  साठी (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      जर (needed + buflen + len < n)
			{
			  साठी (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  साठी (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  अन्यथा
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      अन्यथा
		{
		  /* Remember where the backwards series started.  */
		  जर (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  जर (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      माप_प्रकार backw;

	      backw = idxmax - 1;
	      पर्यंत (backw > backw_stop)
		{
		  माप_प्रकार len = weights[idxarr[--backw]++];
		  जर (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      जर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  साठी (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      जर (needed + buflen + len < n)
			{
			  साठी (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  साठी (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      जर (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  जर (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      जर (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  परत needed - 1;
}

माप_प्रकार
STRXFRM (STRING_TYPE *dest, स्थिरांक STRING_TYPE *src, माप_प्रकार n, locale_t l)
{
  locale_data_t l_data;
  संरचना __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->मूल्ये[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  जर (l_data.nrules == 0)
    {
      माप_प्रकार srclen = STRLEN (src);

      जर (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      परत srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  जर (*src == L('\0'))
    {
      जर (n != 0)
	*dest = L('\0');
      परत 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (अचिन्हित अक्षर *)
    current->मूल्ये[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->मूल्ये[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->मूल्ये[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->मूल्ये[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->मूल्ये[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  प्रतिज्ञा (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  स्थिरांक USTRING_TYPE *usrc = (स्थिरांक USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  माप_प्रकार idxmax = 0;
  स्थिरांक USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * आकार (int32_t));
  अचिन्हित अक्षर *rulearr = alloca (SMALL_STR_SIZE + 1);

  करा
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  पर्यंत (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  जर (*cur == L('\0'))
    परत do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  अन्यथा
    परत do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
