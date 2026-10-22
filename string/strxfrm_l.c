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

#شامل <assert.h>
#شامل <langinfo.h>
#شامل <locale.h>
#شامل <stddef.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE نویسه
# define USTRING_TYPE unsigned نویسه
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

#شامل "../locale/localeinfo.h"
#شامل WEIGHT_H

/* Group locale data for shorter parameter lists.  */
تعریفنوع ساختار
{
  uint32_t nrules;
  unsigned نویسه *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
ایستا صحیح
utf8_encode (نویسه *buf, صحیح val)
{
  صحیح retval;

  اگر (val < 0x80)
    {
      *buf++ = (نویسه) val;
      retval = 1;
    }
  وگرنه
    {
      صحیح step;

      برای (step = 2; step < 6; ++step)
	اگر ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  بشکن;
      retval = step;

      *buf = (unsigned نویسه) (~0xff >> step);
      --step;
      انجامبده
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      وقتی (--step > 0);
      *buf |= val;
    }

  بازگشت retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
ایستا __always_inline size_t
find_idx (ثابت USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned نویسه *rule_idx, ثابت locale_data_t *l_data, ثابت صحیح pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  برای (صحیح i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  بازگشت len;
}

ایستا صحیح
find_position (ثابت USTRING_TYPE *us, ثابت locale_data_t *l_data,
	       ثابت صحیح pass)
{
  int32_t weight_idx;
  unsigned نویسه rule_idx;
  ثابت USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  بازگشت l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
ایستا size_t
do_xfrm (ثابت USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ثابت locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned نویسه rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  برای (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ثابت USTRING_TYPE *cur = usrc;
      ثابت USTRING_TYPE *backw_start = پوچ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      صحیح position = find_position (cur, l_data, pass);

      اگر (position == 0)
	{
	  وقتی (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      صحیح rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      اگر ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  اگر (backw_start != پوچ)
		    {
		      برای (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned نویسه rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  اگر (needed + i < n)
			    برای (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = پوچ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  اگر (needed + len < n)
		    وقتی (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  وگرنه
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      وگرنه
		{
		  /* Remember start of the backward sequence & track length.  */
		  اگر (backw_start == پوچ)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  اگر (backw_start != پوچ)
	    {
	      برای (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  اگر (needed + i < n)
		    برای (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      وگرنه
	{
	  صحیح val = 1;
#ifndef WIDE_CHAR_VERSION
	  نویسه buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  وقتی (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      صحیح rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      اگر ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  اگر (backw_start != پوچ)
		    {
		      برای (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned نویسه rule_idx;
			  ثابت USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  برای (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  اگر (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      اگر (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  برای (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#وگرنه
			      buflen = utf8_encode (buf, val);
			      اگر (needed + buflen + len < n)
				{
				  برای (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  برای (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  وگرنه
			    ++val;
			}

		      backw_start = پوچ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  اگر (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برای (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#وگرنه
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برای (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برای (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  وگرنه
		    ++val;
		}
	      وگرنه
		{
		  /* Remember start of the backward sequence & track length.  */
		  اگر (backw_start == پوچ)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  اگر (backw_start != پوچ)
	    {
	      برای (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned نویسه rule_idx;
		  ثابت USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  برای (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  اگر (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برای (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#وگرنه
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برای (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برای (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  وگرنه
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      اگر (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  اگر (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      اگر (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  بازگشت needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ایستا size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ثابت locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, ثابت unsigned نویسه *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned نویسه *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  برای (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      صحیح rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      صحیح position = rule & sort_position;

      last_needed = needed;
      اگر (position == 0)
	{
	  برای (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      اگر ((rule & sort_forward) != 0)
		{
		  size_t len;

		  اگر (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      برای (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  اگر (needed + len < n)
			    وقتی (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  وگرنه
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
		  اگر (needed + len < n)
		    وقتی (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  وگرنه
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      وگرنه
		{
		  /* Remember where the backwards series started.  */
		  اگر (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  اگر (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      وقتی (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  اگر (needed + len < n)
		    وقتی (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  وگرنه
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      وگرنه
	{
	  صحیح val = 1;
#ifndef WIDE_CHAR_VERSION
	  نویسه buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  برای (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      اگر ((rule & sort_forward) != 0)
		{
		  size_t len;

		  اگر (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      برای (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  اگر (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      اگر (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  برای (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#وگرنه
			      buflen = utf8_encode (buf, val);
			      اگر (needed + buflen + len < n)
				{
				  برای (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  برای (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  وگرنه
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  اگر (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      اگر (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  برای (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#وگرنه
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برای (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برای (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  وگرنه
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      وگرنه
		{
		  /* Remember where the backwards series started.  */
		  اگر (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  اگر (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      وقتی (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  اگر (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برای (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#وگرنه
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برای (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برای (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  وگرنه
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      اگر (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  اگر (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      اگر (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  بازگشت needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ثابت STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  ساختار __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->مقادیر[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  اگر (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      اگر (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      بازگشت srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  اگر (*src == L('\0'))
    {
      اگر (n != 0)
	*dest = L('\0');
      بازگشت 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned نویسه *)
    current->مقادیر[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  أكد (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  أكد (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  أكد (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  أكد (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ثابت USTRING_TYPE *usrc = (ثابت USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ثابت USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * اندازه (int32_t));
  unsigned نویسه *rulearr = alloca (SMALL_STR_SIZE + 1);

  انجامبده
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  وقتی (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  اگر (*cur == L('\0'))
    بازگشت do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  وگرنه
    بازگشت do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
