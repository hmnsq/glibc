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

#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <langinfo.h>
#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE અક્ષર
# define USTRING_TYPE unsigned અક્ષર
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

#અન્તર્ભાવ "../locale/localeinfo.h"
#અન્તર્ભાવ WEIGHT_H

/* Group locale data for shorter parameter lists.  */
પ્રકારવ્યાખ્યા સંરચના
{
  uint32_t nrules;
  unsigned અક્ષર *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
સ્થિર પૂર્ણાંક
utf8_encode (અક્ષર *buf, પૂર્ણાંક val)
{
  પૂર્ણાંક retval;

  જો (val < 0x80)
    {
      *buf++ = (અક્ષર) val;
      retval = 1;
    }
  નહીંતર
    {
      પૂર્ણાંક step;

      માટે (step = 2; step < 6; ++step)
	જો ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  તોડો;
      retval = step;

      *buf = (unsigned અક્ષર) (~0xff >> step);
      --step;
      કરો
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      જ્યારે (--step > 0);
      *buf |= val;
    }

  પાછા retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
સ્થિર __always_inline size_t
find_idx (અચલ USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned અક્ષર *rule_idx, અચલ locale_data_t *l_data, અચલ પૂર્ણાંક pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  માટે (પૂર્ણાંક i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  પાછા len;
}

સ્થિર પૂર્ણાંક
find_position (અચલ USTRING_TYPE *us, અચલ locale_data_t *l_data,
	       અચલ પૂર્ણાંક pass)
{
  int32_t weight_idx;
  unsigned અક્ષર rule_idx;
  અચલ USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  પાછા l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
સ્થિર size_t
do_xfrm (અચલ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 અચલ locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned અક્ષર rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  માટે (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      અચલ USTRING_TYPE *cur = usrc;
      અચલ USTRING_TYPE *backw_start = ખાલી;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      પૂર્ણાંક position = find_position (cur, l_data, pass);

      જો (position == 0)
	{
	  જ્યારે (*cur != L('\0'))
	    {
	      અચલ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      પૂર્ણાંક rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      જો ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  જો (backw_start != ખાલી)
		    {
		      માટે (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned અક્ષર rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  જો (needed + i < n)
			    માટે (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = ખાલી;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  જો (needed + len < n)
		    જ્યારે (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  નહીંતર
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      નહીંતર
		{
		  /* Remember start of the backward sequence & track length.  */
		  જો (backw_start == ખાલી)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  જો (backw_start != ખાલી)
	    {
	      માટે (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  જો (needed + i < n)
		    માટે (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      નહીંતર
	{
	  પૂર્ણાંક val = 1;
#ifndef WIDE_CHAR_VERSION
	  અક્ષર buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  જ્યારે (*cur != L('\0'))
	    {
	      અચલ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      પૂર્ણાંક rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      જો ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  જો (backw_start != ખાલી)
		    {
		      માટે (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned અક્ષર rule_idx;
			  અચલ USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  માટે (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  જો (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      જો (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  માટે (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#નહીંતર
			      buflen = utf8_encode (buf, val);
			      જો (needed + buflen + len < n)
				{
				  માટે (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  માટે (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  નહીંતર
			    ++val;
			}

		      backw_start = ખાલી;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  જો (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      જો (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  માટે (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#નહીંતર
		      buflen = utf8_encode (buf, val);
		      જો (needed + buflen + len < n)
			{
			  માટે (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  માટે (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  નહીંતર
		    ++val;
		}
	      નહીંતર
		{
		  /* Remember start of the backward sequence & track length.  */
		  જો (backw_start == ખાલી)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  જો (backw_start != ખાલી)
	    {
	      માટે (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned અક્ષર rule_idx;
		  અચલ USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  માટે (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  જો (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      જો (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  માટે (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#નહીંતર
		      buflen = utf8_encode (buf, val);
		      જો (needed + buflen + len < n)
			{
			  માટે (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  માટે (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  નહીંતર
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      જો (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  જો (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      જો (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  પાછા needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
સ્થિર size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, અચલ locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, અચલ unsigned અક્ષર *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned અક્ષર *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  માટે (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      પૂર્ણાંક rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      પૂર્ણાંક position = rule & sort_position;

      last_needed = needed;
      જો (position == 0)
	{
	  માટે (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      જો ((rule & sort_forward) != 0)
		{
		  size_t len;

		  જો (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      માટે (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  જો (needed + len < n)
			    જ્યારે (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  નહીંતર
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
		  જો (needed + len < n)
		    જ્યારે (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  નહીંતર
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      નહીંતર
		{
		  /* Remember where the backwards series started.  */
		  જો (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  જો (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      જ્યારે (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  જો (needed + len < n)
		    જ્યારે (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  નહીંતર
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      નહીંતર
	{
	  પૂર્ણાંક val = 1;
#ifndef WIDE_CHAR_VERSION
	  અક્ષર buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  માટે (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      જો ((rule & sort_forward) != 0)
		{
		  size_t len;

		  જો (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      માટે (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  જો (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      જો (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  માટે (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#નહીંતર
			      buflen = utf8_encode (buf, val);
			      જો (needed + buflen + len < n)
				{
				  માટે (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  માટે (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  નહીંતર
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  જો (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      જો (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  માટે (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#નહીંતર
		      buflen = utf8_encode (buf, val);
		      જો (needed + buflen + len < n)
			{
			  માટે (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  માટે (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  નહીંતર
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      નહીંતર
		{
		  /* Remember where the backwards series started.  */
		  જો (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  જો (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      જ્યારે (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  જો (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      જો (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  માટે (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#નહીંતર
		      buflen = utf8_encode (buf, val);
		      જો (needed + buflen + len < n)
			{
			  માટે (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  માટે (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  નહીંતર
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      જો (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  જો (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      જો (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  પાછા needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, અચલ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  સંરચના __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->કિંમતો[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  જો (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      જો (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      પાછા srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  જો (*src == L('\0'))
    {
      જો (n != 0)
	*dest = L('\0');
      પાછા 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned અક્ષર *)
    current->કિંમતો[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->કિંમતો[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->કિંમતો[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->કિંમતો[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->કિંમતો[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  પ્રતિજ્ઞા (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  પ્રતિજ્ઞા (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  પ્રતિજ્ઞા (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  પ્રતિજ્ઞા (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  અચલ USTRING_TYPE *usrc = (અચલ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  અચલ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * કદ (int32_t));
  unsigned અક્ષર *rulearr = alloca (SMALL_STR_SIZE + 1);

  કરો
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  જ્યારે (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  જો (*cur == L('\0'))
    પાછા do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  નહીંતર
    પાછા do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
