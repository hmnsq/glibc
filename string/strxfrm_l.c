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
# define STRING_TYPE वर्ण
# define USTRING_TYPE unsigned वर्ण
# define STRXFRM __strxfrm_l
# define STRLEN strlen
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
प्रकारनिर्देश संरचना
{
  uint32_t nrules;
  unsigned वर्ण *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
स्थिर पूर्णाङ्क
utf8_encode (वर्ण *buf, पूर्णाङ्क val)
{
  पूर्णाङ्क retval;

  सचे (val < 0x80)
    {
      *buf++ = (वर्ण) val;
      retval = 1;
    }
  अञ्ञथा
    {
      पूर्णाङ्क step;

      अत्थाय (step = 2; step < 6; ++step)
	सचे ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  भङ्ग;
      retval = step;

      *buf = (unsigned वर्ण) (~0xff >> step);
      --step;
      करोहि
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      याव (--step > 0);
      *buf |= val;
    }

  पटिनिवत्त retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
स्थिर __always_inline size_t
find_idx (ध्रुव USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned वर्ण *rule_idx, ध्रुव locale_data_t *l_data, ध्रुव पूर्णाङ्क pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  अत्थाय (पूर्णाङ्क i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  पटिनिवत्त len;
}

स्थिर पूर्णाङ्क
find_position (ध्रुव USTRING_TYPE *us, ध्रुव locale_data_t *l_data,
	       ध्रुव पूर्णाङ्क pass)
{
  int32_t weight_idx;
  unsigned वर्ण rule_idx;
  ध्रुव USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  पटिनिवत्त l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
स्थिर size_t
do_xfrm (ध्रुव USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ध्रुव locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned वर्ण rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  अत्थाय (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ध्रुव USTRING_TYPE *cur = usrc;
      ध्रुव USTRING_TYPE *backw_start = रिक्त;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      पूर्णाङ्क position = find_position (cur, l_data, pass);

      सचे (position == 0)
	{
	  याव (*cur != L('\0'))
	    {
	      ध्रुव USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      पूर्णाङ्क rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      सचे ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  सचे (backw_start != रिक्त)
		    {
		      अत्थाय (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned वर्ण rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  सचे (needed + i < n)
			    अत्थाय (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  सचे (needed + len < n)
		    याव (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  अञ्ञथा
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      अञ्ञथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  सचे (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  सचे (backw_start != रिक्त)
	    {
	      अत्थाय (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  सचे (needed + i < n)
		    अत्थाय (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      अञ्ञथा
	{
	  पूर्णाङ्क val = 1;
#ifndef WIDE_CHAR_VERSION
	  वर्ण buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  याव (*cur != L('\0'))
	    {
	      ध्रुव USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      पूर्णाङ्क rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      सचे ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  सचे (backw_start != रिक्त)
		    {
		      अत्थाय (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned वर्ण rule_idx;
			  ध्रुव USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  अत्थाय (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  सचे (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      सचे (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  अत्थाय (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#अञ्ञथा
			      buflen = utf8_encode (buf, val);
			      सचे (needed + buflen + len < n)
				{
				  अत्थाय (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  अत्थाय (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  अञ्ञथा
			    ++val;
			}

		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  सचे (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      सचे (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अञ्ञथा
		      buflen = utf8_encode (buf, val);
		      सचे (needed + buflen + len < n)
			{
			  अत्थाय (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  अञ्ञथा
		    ++val;
		}
	      अञ्ञथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  सचे (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  सचे (backw_start != रिक्त)
	    {
	      अत्थाय (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned वर्ण rule_idx;
		  ध्रुव USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  अत्थाय (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  सचे (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      सचे (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अञ्ञथा
		      buflen = utf8_encode (buf, val);
		      सचे (needed + buflen + len < n)
			{
			  अत्थाय (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  अञ्ञथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      सचे (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  सचे (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      सचे (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  पटिनिवत्त needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
स्थिर size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ध्रुव locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, ध्रुव unsigned वर्ण *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned वर्ण *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  अत्थाय (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      पूर्णाङ्क rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      पूर्णाङ्क position = rule & sort_position;

      last_needed = needed;
      सचे (position == 0)
	{
	  अत्थाय (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      सचे ((rule & sort_forward) != 0)
		{
		  size_t len;

		  सचे (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      अत्थाय (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  सचे (needed + len < n)
			    याव (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  अञ्ञथा
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
		  सचे (needed + len < n)
		    याव (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  अञ्ञथा
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      अञ्ञथा
		{
		  /* Remember where the backwards series started.  */
		  सचे (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  सचे (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      याव (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  सचे (needed + len < n)
		    याव (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  अञ्ञथा
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      अञ्ञथा
	{
	  पूर्णाङ्क val = 1;
#ifndef WIDE_CHAR_VERSION
	  वर्ण buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  अत्थाय (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      सचे ((rule & sort_forward) != 0)
		{
		  size_t len;

		  सचे (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      अत्थाय (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  सचे (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      सचे (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  अत्थाय (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#अञ्ञथा
			      buflen = utf8_encode (buf, val);
			      सचे (needed + buflen + len < n)
				{
				  अत्थाय (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  अत्थाय (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  अञ्ञथा
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  सचे (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      सचे (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#अञ्ञथा
		      buflen = utf8_encode (buf, val);
		      सचे (needed + buflen + len < n)
			{
			  अत्थाय (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  अञ्ञथा
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      अञ्ञथा
		{
		  /* Remember where the backwards series started.  */
		  सचे (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  सचे (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      याव (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  सचे (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      सचे (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#अञ्ञथा
		      buflen = utf8_encode (buf, val);
		      सचे (needed + buflen + len < n)
			{
			  अत्थाय (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  अत्थाय (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  अञ्ञथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      सचे (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  सचे (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      सचे (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  पटिनिवत्त needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ध्रुव STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  संरचना __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  सचे (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      सचे (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      पटिनिवत्त srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  सचे (*src == L('\0'))
    {
      सचे (n != 0)
	*dest = L('\0');
      पटिनिवत्त 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned वर्ण *)
    current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  प्रतिज्ञा (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ध्रुव USTRING_TYPE *usrc = (ध्रुव USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ध्रुव USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * परिमाण (int32_t));
  unsigned वर्ण *rulearr = alloca (SMALL_STR_SIZE + 1);

  करोहि
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  याव (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  सचे (*cur == L('\0'))
    पटिनिवत्त do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  अञ्ञथा
    पटिनिवत्त do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
