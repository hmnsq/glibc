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

#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ತರ್ಭಾವ <langinfo.h>
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE ವರ್ಣ
# define USTRING_TYPE unsigned ವರ್ಣ
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

#ಅನ್ತರ್ಭಾವ "../locale/localeinfo.h"
#ಅನ್ತರ್ಭಾವ WEIGHT_H

/* Group locale data for shorter parameter lists.  */
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
  uint32_t nrules;
  unsigned ವರ್ಣ *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
utf8_encode (ವರ್ಣ *buf, ಪೂರ್ಣಾಙ್ಕ val)
{
  ಪೂರ್ಣಾಙ್ಕ retval;

  ಯದಿ (val < 0x80)
    {
      *buf++ = (ವರ್ಣ) val;
      retval = 1;
    }
  ಅನ್ಯಥಾ
    {
      ಪೂರ್ಣಾಙ್ಕ step;

      ಪ್ರತಿ (step = 2; step < 6; ++step)
	ಯದಿ ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  ಭಙ್ಗ;
      retval = step;

      *buf = (unsigned ವರ್ಣ) (~0xff >> step);
      --step;
      ಕುರು
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      ಯಾವತ್ (--step > 0);
      *buf |= val;
    }

  ಪ್ರತ್ಯಾಗಮ retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
ಸ್ಥಿರ __always_inline size_t
find_idx (ಧ್ರುವ USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned ವರ್ಣ *rule_idx, ಧ್ರುವ locale_data_t *l_data, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  ಪ್ರತ್ಯಾಗಮ len;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
find_position (ಧ್ರುವ USTRING_TYPE *us, ಧ್ರುವ locale_data_t *l_data,
	       ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ pass)
{
  int32_t weight_idx;
  unsigned ವರ್ಣ rule_idx;
  ಧ್ರುವ USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  ಪ್ರತ್ಯಾಗಮ l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
ಸ್ಥಿರ size_t
do_xfrm (ಧ್ರುವ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ಧ್ರುವ locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned ವರ್ಣ rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  ಪ್ರತಿ (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ಧ್ರುವ USTRING_TYPE *cur = usrc;
      ಧ್ರುವ USTRING_TYPE *backw_start = ರಿಕ್ತ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      ಪೂರ್ಣಾಙ್ಕ position = find_position (cur, l_data, pass);

      ಯದಿ (position == 0)
	{
	  ಯಾವತ್ (*cur != L('\0'))
	    {
	      ಧ್ರುವ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      ಪೂರ್ಣಾಙ್ಕ rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      ಯದಿ ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ಯದಿ (backw_start != ರಿಕ್ತ)
		    {
		      ಪ್ರತಿ (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned ವರ್ಣ rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  ಯದಿ (needed + i < n)
			    ಪ್ರತಿ (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = ರಿಕ್ತ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ಯದಿ (needed + len < n)
		    ಯಾವತ್ (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  ಅನ್ಯಥಾ
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      ಅನ್ಯಥಾ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ಯದಿ (backw_start == ರಿಕ್ತ)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  ಯದಿ (backw_start != ರಿಕ್ತ)
	    {
	      ಪ್ರತಿ (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  ಯದಿ (needed + i < n)
		    ಪ್ರತಿ (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      ಅನ್ಯಥಾ
	{
	  ಪೂರ್ಣಾಙ್ಕ val = 1;
#ifndef WIDE_CHAR_VERSION
	  ವರ್ಣ buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  ಯಾವತ್ (*cur != L('\0'))
	    {
	      ಧ್ರುವ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      ಪೂರ್ಣಾಙ್ಕ rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      ಯದಿ ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ಯದಿ (backw_start != ರಿಕ್ತ)
		    {
		      ಪ್ರತಿ (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned ವರ್ಣ rule_idx;
			  ಧ್ರುವ USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  ಪ್ರತಿ (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  ಯದಿ (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      ಯದಿ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ಪ್ರತಿ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#ಅನ್ಯಥಾ
			      buflen = utf8_encode (buf, val);
			      ಯದಿ (needed + buflen + len < n)
				{
				  ಪ್ರತಿ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ಪ್ರತಿ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  ಅನ್ಯಥಾ
			    ++val;
			}

		      backw_start = ರಿಕ್ತ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ಯದಿ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ಯದಿ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#ಅನ್ಯಥಾ
		      buflen = utf8_encode (buf, val);
		      ಯದಿ (needed + buflen + len < n)
			{
			  ಪ್ರತಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  ಅನ್ಯಥಾ
		    ++val;
		}
	      ಅನ್ಯಥಾ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ಯದಿ (backw_start == ರಿಕ್ತ)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  ಯದಿ (backw_start != ರಿಕ್ತ)
	    {
	      ಪ್ರತಿ (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned ವರ್ಣ rule_idx;
		  ಧ್ರುವ USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  ಪ್ರತಿ (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  ಯದಿ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ಯದಿ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#ಅನ್ಯಥಾ
		      buflen = utf8_encode (buf, val);
		      ಯದಿ (needed + buflen + len < n)
			{
			  ಪ್ರತಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  ಅನ್ಯಥಾ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ಯದಿ (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ಯದಿ (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      ಯದಿ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ಪ್ರತ್ಯಾಗಮ needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ಸ್ಥಿರ size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ಧ್ರುವ locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, ಧ್ರುವ unsigned ವರ್ಣ *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned ವರ್ಣ *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  ಪ್ರತಿ (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      ಪೂರ್ಣಾಙ್ಕ rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      ಪೂರ್ಣಾಙ್ಕ position = rule & sort_position;

      last_needed = needed;
      ಯದಿ (position == 0)
	{
	  ಪ್ರತಿ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ಯದಿ ((rule & sort_forward) != 0)
		{
		  size_t len;

		  ಯದಿ (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      ಪ್ರತಿ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  ಯದಿ (needed + len < n)
			    ಯಾವತ್ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  ಅನ್ಯಥಾ
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
		  ಯದಿ (needed + len < n)
		    ಯಾವತ್ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  ಅನ್ಯಥಾ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      ಅನ್ಯಥಾ
		{
		  /* Remember where the backwards series started.  */
		  ಯದಿ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  ಯದಿ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      ಯಾವತ್ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  ಯದಿ (needed + len < n)
		    ಯಾವತ್ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  ಅನ್ಯಥಾ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      ಅನ್ಯಥಾ
	{
	  ಪೂರ್ಣಾಙ್ಕ val = 1;
#ifndef WIDE_CHAR_VERSION
	  ವರ್ಣ buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  ಪ್ರತಿ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ಯದಿ ((rule & sort_forward) != 0)
		{
		  size_t len;

		  ಯದಿ (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      ಪ್ರತಿ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  ಯದಿ (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      ಯದಿ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ಪ್ರತಿ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#ಅನ್ಯಥಾ
			      buflen = utf8_encode (buf, val);
			      ಯದಿ (needed + buflen + len < n)
				{
				  ಪ್ರತಿ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ಪ್ರತಿ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  ಅನ್ಯಥಾ
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ಯದಿ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ಯದಿ (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#ಅನ್ಯಥಾ
		      buflen = utf8_encode (buf, val);
		      ಯದಿ (needed + buflen + len < n)
			{
			  ಪ್ರತಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  ಅನ್ಯಥಾ
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      ಅನ್ಯಥಾ
		{
		  /* Remember where the backwards series started.  */
		  ಯದಿ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  ಯದಿ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      ಯಾವತ್ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  ಯದಿ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ಯದಿ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#ಅನ್ಯಥಾ
		      buflen = utf8_encode (buf, val);
		      ಯದಿ (needed + buflen + len < n)
			{
			  ಪ್ರತಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಪ್ರತಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  ಅನ್ಯಥಾ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ಯದಿ (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ಯದಿ (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      ಯದಿ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ಪ್ರತ್ಯಾಗಮ needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ಧ್ರುವ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  ಸಂರಚನಾ __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  ಯದಿ (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      ಯದಿ (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ಪ್ರತ್ಯಾಗಮ srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  ಯದಿ (*src == L('\0'))
    {
      ಯದಿ (n != 0)
	*dest = L('\0');
      ಪ್ರತ್ಯಾಗಮ 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned ವರ್ಣ *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ಧ್ರುವ USTRING_TYPE *usrc = (ಧ್ರುವ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ಧ್ರುವ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * ಪರಿಮಾಣ (int32_t));
  unsigned ವರ್ಣ *rulearr = alloca (SMALL_STR_SIZE + 1);

  ಕುರು
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  ಯಾವತ್ (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  ಯದಿ (*cur == L('\0'))
    ಪ್ರತ್ಯಾಗಮ do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
