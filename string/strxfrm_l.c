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

#ଅନ୍ତର୍ଭାଵ <assert.h>
#ଅନ୍ତର୍ଭାଵ <langinfo.h>
#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE ଅକ୍ଷର
# define USTRING_TYPE unsigned ଅକ୍ଷର
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

#ଅନ୍ତର୍ଭାଵ "../locale/localeinfo.h"
#ଅନ୍ତର୍ଭାଵ WEIGHT_H

/* Group locale data for shorter parameter lists.  */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
  uint32_t nrules;
  unsigned ଅକ୍ଷର *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
utf8_encode (ଅକ୍ଷର *buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା val)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା retval;

  ଯଦି (val < 0x80)
    {
      *buf++ = (ଅକ୍ଷର) val;
      retval = 1;
    }
  ଅନ୍ୟଥା
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା step;

      ପାଇଁ (step = 2; step < 6; ++step)
	ଯଦି ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  ଭାଙ୍ଗ;
      retval = step;

      *buf = (unsigned ଅକ୍ଷର) (~0xff >> step);
      --step;
      କର
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      ଯେତେବେଳେ (--step > 0);
      *buf |= val;
    }

  ଫେରନ୍ତୁ retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
ସ୍ଥିର __always_inline size_t
find_idx (ଅଚଳ USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned ଅକ୍ଷର *rule_idx, ଅଚଳ locale_data_t *l_data, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  ଫେରନ୍ତୁ len;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
find_position (ଅଚଳ USTRING_TYPE *us, ଅଚଳ locale_data_t *l_data,
	       ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pass)
{
  int32_t weight_idx;
  unsigned ଅକ୍ଷର rule_idx;
  ଅଚଳ USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  ଫେରନ୍ତୁ l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
ସ୍ଥିର size_t
do_xfrm (ଅଚଳ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ଅଚଳ locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned ଅକ୍ଷର rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  ପାଇଁ (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ଅଚଳ USTRING_TYPE *cur = usrc;
      ଅଚଳ USTRING_TYPE *backw_start = ଖାଲି;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା position = find_position (cur, l_data, pass);

      ଯଦି (position == 0)
	{
	  ଯେତେବେଳେ (*cur != L('\0'))
	    {
	      ଅଚଳ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      ଯଦି ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ଯଦି (backw_start != ଖାଲି)
		    {
		      ପାଇଁ (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned ଅକ୍ଷର rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  ଯଦି (needed + i < n)
			    ପାଇଁ (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = ଖାଲି;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ଯଦି (needed + len < n)
		    ଯେତେବେଳେ (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  ଅନ୍ୟଥା
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      ଅନ୍ୟଥା
		{
		  /* Remember start of the backward sequence & track length.  */
		  ଯଦି (backw_start == ଖାଲି)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  ଯଦି (backw_start != ଖାଲି)
	    {
	      ପାଇଁ (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  ଯଦି (needed + i < n)
		    ପାଇଁ (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      ଅନ୍ୟଥା
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା val = 1;
#ifndef WIDE_CHAR_VERSION
	  ଅକ୍ଷର buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  ଯେତେବେଳେ (*cur != L('\0'))
	    {
	      ଅଚଳ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      ଯଦି ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ଯଦି (backw_start != ଖାଲି)
		    {
		      ପାଇଁ (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned ଅକ୍ଷର rule_idx;
			  ଅଚଳ USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  ପାଇଁ (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  ଯଦି (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      ଯଦି (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ପାଇଁ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#ଅନ୍ୟଥା
			      buflen = utf8_encode (buf, val);
			      ଯଦି (needed + buflen + len < n)
				{
				  ପାଇଁ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ପାଇଁ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  ଅନ୍ୟଥା
			    ++val;
			}

		      backw_start = ଖାଲି;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ଯଦି (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ଯଦି (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#ଅନ୍ୟଥା
		      buflen = utf8_encode (buf, val);
		      ଯଦି (needed + buflen + len < n)
			{
			  ପାଇଁ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  ଅନ୍ୟଥା
		    ++val;
		}
	      ଅନ୍ୟଥା
		{
		  /* Remember start of the backward sequence & track length.  */
		  ଯଦି (backw_start == ଖାଲି)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  ଯଦି (backw_start != ଖାଲି)
	    {
	      ପାଇଁ (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned ଅକ୍ଷର rule_idx;
		  ଅଚଳ USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  ପାଇଁ (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  ଯଦି (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ଯଦି (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#ଅନ୍ୟଥା
		      buflen = utf8_encode (buf, val);
		      ଯଦି (needed + buflen + len < n)
			{
			  ପାଇଁ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  ଅନ୍ୟଥା
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ଯଦି (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ଯଦି (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      ଯଦି (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ଫେରନ୍ତୁ needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ସ୍ଥିର size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ଅଚଳ locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, ଅଚଳ unsigned ଅକ୍ଷର *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned ଅକ୍ଷର *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  ପାଇଁ (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା position = rule & sort_position;

      last_needed = needed;
      ଯଦି (position == 0)
	{
	  ପାଇଁ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ଯଦି ((rule & sort_forward) != 0)
		{
		  size_t len;

		  ଯଦି (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      ପାଇଁ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  ଯଦି (needed + len < n)
			    ଯେତେବେଳେ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  ଅନ୍ୟଥା
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
		  ଯଦି (needed + len < n)
		    ଯେତେବେଳେ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  ଅନ୍ୟଥା
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      ଅନ୍ୟଥା
		{
		  /* Remember where the backwards series started.  */
		  ଯଦି (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  ଯଦି (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      ଯେତେବେଳେ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  ଯଦି (needed + len < n)
		    ଯେତେବେଳେ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  ଅନ୍ୟଥା
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      ଅନ୍ୟଥା
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା val = 1;
#ifndef WIDE_CHAR_VERSION
	  ଅକ୍ଷର buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  ପାଇଁ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ଯଦି ((rule & sort_forward) != 0)
		{
		  size_t len;

		  ଯଦି (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      ପାଇଁ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  ଯଦି (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      ଯଦି (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ପାଇଁ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#ଅନ୍ୟଥା
			      buflen = utf8_encode (buf, val);
			      ଯଦି (needed + buflen + len < n)
				{
				  ପାଇଁ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ପାଇଁ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  ଅନ୍ୟଥା
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ଯଦି (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ଯଦି (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#ଅନ୍ୟଥା
		      buflen = utf8_encode (buf, val);
		      ଯଦି (needed + buflen + len < n)
			{
			  ପାଇଁ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  ଅନ୍ୟଥା
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      ଅନ୍ୟଥା
		{
		  /* Remember where the backwards series started.  */
		  ଯଦି (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  ଯଦି (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      ଯେତେବେଳେ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  ଯଦି (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      ଯଦି (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#ଅନ୍ୟଥା
		      buflen = utf8_encode (buf, val);
		      ଯଦି (needed + buflen + len < n)
			{
			  ପାଇଁ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ପାଇଁ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  ଅନ୍ୟଥା
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ଯଦି (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ଯଦି (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      ଯଦି (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ଫେରନ୍ତୁ needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ଅଚଳ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  ସଂରଚନା __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  ଯଦି (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      ଯଦି (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ଫେରନ୍ତୁ srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  ଯଦି (*src == L('\0'))
    {
      ଯଦି (n != 0)
	*dest = L('\0');
      ଫେରନ୍ତୁ 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned ଅକ୍ଷର *)
    current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->ମୂଲ୍ୟଗୁଡ଼ିକ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  ପ୍ରତିଜ୍ଞା (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  ପ୍ରତିଜ୍ଞା (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  ପ୍ରତିଜ୍ଞା (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  ପ୍ରତିଜ୍ଞା (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ଅଚଳ USTRING_TYPE *usrc = (ଅଚଳ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ଅଚଳ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * ଆକାର (int32_t));
  unsigned ଅକ୍ଷର *rulearr = alloca (SMALL_STR_SIZE + 1);

  କର
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  ଯେତେବେଳେ (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  ଯଦି (*cur == L('\0'))
    ଫେରନ୍ତୁ do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
