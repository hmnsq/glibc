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

#অন্তর্ভাৱ <assert.h>
#অন্তর্ভাৱ <langinfo.h>
#অন্তর্ভাৱ <locale.h>
#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE ৱর্ণ
# define USTRING_TYPE unsigned ৱর্ণ
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

#অন্তর্ভাৱ "../locale/localeinfo.h"
#অন্তর্ভাৱ WEIGHT_H

/* Group locale data for shorter parameter lists.  */
প্রকারনির্দেশ সংরচনা
{
  uint32_t nrules;
  unsigned ৱর্ণ *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
স্থির পূর্ণাঙ্ক
utf8_encode (ৱর্ণ *buf, পূর্ণাঙ্ক val)
{
  পূর্ণাঙ্ক retval;

  যদি (val < 0x80)
    {
      *buf++ = (ৱর্ণ) val;
      retval = 1;
    }
  অন্যথা
    {
      পূর্ণাঙ্ক step;

      বাবে (step = 2; step < 6; ++step)
	যদি ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  ভঙ্গ;
      retval = step;

      *buf = (unsigned ৱর্ণ) (~0xff >> step);
      --step;
      কৰা
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      যেতিয়ালৈ (--step > 0);
      *buf |= val;
    }

  ঘূৰাই retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
স্থির __always_inline size_t
find_idx (ধ্রুৱ USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned ৱর্ণ *rule_idx, ধ্রুৱ locale_data_t *l_data, ধ্রুৱ পূর্ণাঙ্ক pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  বাবে (পূর্ণাঙ্ক i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  ঘূৰাই len;
}

স্থির পূর্ণাঙ্ক
find_position (ধ্রুৱ USTRING_TYPE *us, ধ্রুৱ locale_data_t *l_data,
	       ধ্রুৱ পূর্ণাঙ্ক pass)
{
  int32_t weight_idx;
  unsigned ৱর্ণ rule_idx;
  ধ্রুৱ USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  ঘূৰাই l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
স্থির size_t
do_xfrm (ধ্রুৱ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ধ্রুৱ locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned ৱর্ণ rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  বাবে (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ধ্রুৱ USTRING_TYPE *cur = usrc;
      ধ্রুৱ USTRING_TYPE *backw_start = রিক্ত;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      পূর্ণাঙ্ক position = find_position (cur, l_data, pass);

      যদি (position == 0)
	{
	  যেতিয়ালৈ (*cur != L('\0'))
	    {
	      ধ্রুৱ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      পূর্ণাঙ্ক rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      যদি ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  যদি (backw_start != রিক্ত)
		    {
		      বাবে (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned ৱর্ণ rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  যদি (needed + i < n)
			    বাবে (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = রিক্ত;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  যদি (needed + len < n)
		    যেতিয়ালৈ (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  অন্যথা
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      অন্যথা
		{
		  /* Remember start of the backward sequence & track length.  */
		  যদি (backw_start == রিক্ত)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  যদি (backw_start != রিক্ত)
	    {
	      বাবে (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  যদি (needed + i < n)
		    বাবে (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      অন্যথা
	{
	  পূর্ণাঙ্ক val = 1;
#ifndef WIDE_CHAR_VERSION
	  ৱর্ণ buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  যেতিয়ালৈ (*cur != L('\0'))
	    {
	      ধ্রুৱ USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      পূর্ণাঙ্ক rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      যদি ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  যদি (backw_start != রিক্ত)
		    {
		      বাবে (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned ৱর্ণ rule_idx;
			  ধ্রুৱ USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  বাবে (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  যদি (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      যদি (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  বাবে (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#অন্যথা
			      buflen = utf8_encode (buf, val);
			      যদি (needed + buflen + len < n)
				{
				  বাবে (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  বাবে (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  অন্যথা
			    ++val;
			}

		      backw_start = রিক্ত;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  বাবে (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  অন্যথা
		    ++val;
		}
	      অন্যথা
		{
		  /* Remember start of the backward sequence & track length.  */
		  যদি (backw_start == রিক্ত)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  যদি (backw_start != রিক্ত)
	    {
	      বাবে (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned ৱর্ণ rule_idx;
		  ধ্রুৱ USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  বাবে (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  বাবে (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  অন্যথা
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      যদি (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  যদি (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      যদি (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ঘূৰাই needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
স্থির size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ধ্রুৱ locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, ধ্রুৱ unsigned ৱর্ণ *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned ৱর্ণ *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  বাবে (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      পূর্ণাঙ্ক rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      পূর্ণাঙ্ক position = rule & sort_position;

      last_needed = needed;
      যদি (position == 0)
	{
	  বাবে (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      যদি ((rule & sort_forward) != 0)
		{
		  size_t len;

		  যদি (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      বাবে (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  যদি (needed + len < n)
			    যেতিয়ালৈ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  অন্যথা
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
		  যদি (needed + len < n)
		    যেতিয়ালৈ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  অন্যথা
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      অন্যথা
		{
		  /* Remember where the backwards series started.  */
		  যদি (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  যদি (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      যেতিয়ালৈ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  যদি (needed + len < n)
		    যেতিয়ালৈ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  অন্যথা
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      অন্যথা
	{
	  পূর্ণাঙ্ক val = 1;
#ifndef WIDE_CHAR_VERSION
	  ৱর্ণ buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  বাবে (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      যদি ((rule & sort_forward) != 0)
		{
		  size_t len;

		  যদি (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      বাবে (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  যদি (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      যদি (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  বাবে (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#অন্যথা
			      buflen = utf8_encode (buf, val);
			      যদি (needed + buflen + len < n)
				{
				  বাবে (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  বাবে (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  অন্যথা
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  বাবে (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  অন্যথা
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      অন্যথা
		{
		  /* Remember where the backwards series started.  */
		  যদি (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  যদি (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      যেতিয়ালৈ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  বাবে (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  বাবে (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  অন্যথা
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      যদি (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  যদি (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      যদি (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ঘূৰাই needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ধ্রুৱ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  সংরচনা __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->মানসমূহ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  যদি (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      যদি (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ঘূৰাই srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  যদি (*src == L('\0'))
    {
      যদি (n != 0)
	*dest = L('\0');
      ঘূৰাই 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned ৱর্ণ *)
    current->মানসমূহ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  প্রতিজ্ঞা (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ধ্রুৱ USTRING_TYPE *usrc = (ধ্রুৱ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ধ্রুৱ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * পরিমাণ (int32_t));
  unsigned ৱর্ণ *rulearr = alloca (SMALL_STR_SIZE + 1);

  কৰা
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  যেতিয়ালৈ (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  যদি (*cur == L('\0'))
    ঘূৰাই do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  অন্যথা
    ঘূৰাই do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
