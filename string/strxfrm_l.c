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

#অন্তর্ভাব <assert.h>
#অন্তর্ভাব <langinfo.h>
#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE অক্ষর
# define USTRING_TYPE unsigned অক্ষর
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
#define SMALL_STR_আকার 4095

#অন্তর্ভাব "../locale/localeinfo.h"
#অন্তর্ভাব WEIGHT_H

/* Group locale data for shorter parameter lists.  */
প্রকারলেখ কাঠামো
{
  uint32_t nrules;
  unsigned অক্ষর *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_তথ্য_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
স্থির পূর্ণসংখ্যা
utf8_encode (অক্ষর *buf, পূর্ণসংখ্যা val)
{
  পূর্ণসংখ্যা retval;

  যদি (val < 0x80)
    {
      *buf++ = (অক্ষর) val;
      retval = 1;
    }
  অন্যথা
    {
      পূর্ণসংখ্যা step;

      জন্য (step = 2; step < 6; ++step)
	যদি ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  বিরতি;
      retval = step;

      *buf = (unsigned অক্ষর) (~0xff >> step);
      --step;
      করো
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      যখন (--step > 0);
      *buf |= val;
    }

  ফেরত retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
স্থির __always_inline size_t
find_idx (ধ্রুবক USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned অক্ষর *rule_idx, ধ্রুবক locale_তথ্য_t *l_তথ্য, ধ্রুবক পূর্ণসংখ্যা pass)
{
  int32_t tmp = findidx (l_তথ্য->table, l_তথ্য->indirect, l_তথ্য->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_তথ্য->weights[idx++];

  /* Skip over indices of previous levels.  */
  জন্য (পূর্ণসংখ্যা i = 0; i < pass; i++)
    {
      idx += len;
      len = l_তথ্য->weights[idx++];
    }

  *weight_idx = idx;
  ফেরত len;
}

স্থির পূর্ণসংখ্যা
find_position (ধ্রুবক USTRING_TYPE *us, ধ্রুবক locale_তথ্য_t *l_তথ্য,
	       ধ্রুবক পূর্ণসংখ্যা pass)
{
  int32_t weight_idx;
  unsigned অক্ষর rule_idx;
  ধ্রুবক USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_তথ্য, pass);
  ফেরত l_তথ্য->rulesets[rule_idx * l_তথ্য->nrules + pass] & sort_position;
}

/* Do the transformation.  */
স্থির size_t
do_xfrm (ধ্রুবক USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ধ্রুবক locale_তথ্য_t *l_তথ্য)
{
  int32_t weight_idx;
  unsigned অক্ষর rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  জন্য (pass = 0; pass < l_তথ্য->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      ধ্রুবক USTRING_TYPE *cur = usrc;
      ধ্রুবক USTRING_TYPE *backw_start = ফাঁকা;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      পূর্ণসংখ্যা position = find_position (cur, l_তথ্য, pass);

      যদি (position == 0)
	{
	  যখন (*cur != L('\0'))
	    {
	      ধ্রুবক USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_তথ্য,
				     pass);
	      পূর্ণসংখ্যা rule = l_তথ্য->rulesets[rule_idx * l_তথ্য->nrules + pass];

	      যদি ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  যদি (backw_start != ফাঁকা)
		    {
		      জন্য (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned অক্ষর rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_তথ্য, pass);
			  যদি (needed + i < n)
			    জন্য (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_তথ্য->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = ফাঁকা;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  যদি (needed + len < n)
		    যখন (len-- > 0)
		      dest[needed++] = l_তথ্য->weights[weight_idx++];
		  অন্যথা
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      অন্যথা
		{
		  /* Remember start of the backward sequence & track length.  */
		  যদি (backw_start == ফাঁকা)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  যদি (backw_start != ফাঁকা)
	    {
	      জন্য (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_তথ্য, pass);
		  যদি (needed + i < n)
		    জন্য (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_তথ্য->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      অন্যথা
	{
	  পূর্ণসংখ্যা val = 1;
#ifndef WIDE_CHAR_VERSION
	  অক্ষর buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  যখন (*cur != L('\0'))
	    {
	      ধ্রুবক USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_তথ্য,
				     pass);
	      পূর্ণসংখ্যা rule = l_তথ্য->rulesets[rule_idx * l_তথ্য->nrules + pass];

	      যদি ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  যদি (backw_start != ফাঁকা)
		    {
		      জন্য (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned অক্ষর rule_idx;
			  ধ্রুবক USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_তথ্য, pass);

			  জন্য (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_তথ্য, pass);

			  যদি (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      যদি (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  জন্য (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_তথ্য->weights[weight_idx + i];
				}
			      needed += 1 + len;
#অন্যথা
			      buflen = utf8_encode (buf, val);
			      যদি (needed + buflen + len < n)
				{
				  জন্য (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  জন্য (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_তথ্য->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  অন্যথা
			    ++val;
			}

		      backw_start = ফাঁকা;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_তথ্য->weights[weight_idx + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  জন্য (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_তথ্য->weights[weight_idx + i];
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
		  যদি (backw_start == ফাঁকা)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  যদি (backw_start != ফাঁকা)
	    {
	      জন্য (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned অক্ষর rule_idx;
		  ধ্রুবক USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_তথ্য, pass);

		  জন্য (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_তথ্য, pass);

		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_তথ্য->weights[weight_idx + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  জন্য (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_তথ্য->weights[weight_idx + i];
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
	dest[needed] = pass + 1 < l_তথ্য->nrules ? L('\1') : L('\0');
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
  ফেরত needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
স্থির size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ধ্রুবক locale_তথ্য_t *l_তথ্য,
		size_t idxmax, int32_t *idxarr, ধ্রুবক unsigned অক্ষর *rulearr)
{
  uint32_t nrules = l_তথ্য->nrules;
  unsigned অক্ষর *rulesets = l_তথ্য->rulesets;
  USTRING_TYPE *weights = l_তথ্য->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  জন্য (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      পূর্ণসংখ্যা rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      পূর্ণসংখ্যা position = rule & sort_position;

      last_needed = needed;
      যদি (position == 0)
	{
	  জন্য (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      যদি ((rule & sort_forward) != 0)
		{
		  size_t len;

		  যদি (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      জন্য (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  যদি (needed + len < n)
			    যখন (len-- > 0)
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
		    যখন (len-- > 0)
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
	      যখন (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  যদি (needed + len < n)
		    যখন (len-- > 0)
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
	  পূর্ণসংখ্যা val = 1;
#ifndef WIDE_CHAR_VERSION
	  অক্ষর buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  জন্য (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      যদি ((rule & sort_forward) != 0)
		{
		  size_t len;

		  যদি (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      জন্য (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  যদি (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      যদি (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  জন্য (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#অন্যথা
			      buflen = utf8_encode (buf, val);
			      যদি (needed + buflen + len < n)
				{
				  জন্য (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  জন্য (i = 0; i < len; ++i)
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
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  জন্য (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  জন্য (i = 0; i < len; ++i)
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
	      যখন (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  যদি (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      যদি (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  জন্য (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#অন্যথা
		      buflen = utf8_encode (buf, val);
		      যদি (needed + buflen + len < n)
			{
			  জন্য (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  জন্য (i = 0; i < len; ++i)
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
  ফেরত needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ধ্রুবক STRING_TYPE *src, size_t n, locale_t l)
{
  locale_তথ্য_t l_তথ্য;
  কাঠামো __locale_data *current = l->__locales[LC_COLLATE];
  l_তথ্য.nrules = current->মানসমূহ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  যদি (l_তথ্য.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      যদি (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ফেরত srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  যদি (*src == L('\0'))
    {
      যদি (n != 0)
	*dest = L('\0');
      ফেরত 0;
    }

  /* Get the locale data.  */
  l_তথ্য.rulesets = (unsigned অক্ষর *)
    current->মানসমূহ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_তথ্য.table = (int32_t *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_তথ্য.weights = (USTRING_TYPE *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_তথ্য.extra = (USTRING_TYPE *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_তথ্য.indirect = (int32_t *)
    current->মানসমূহ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  প্রতিজ্ঞা (((uintptr_t) l_তথ্য.table) % __alignof__ (l_তথ্য.table[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_তথ্য.weights) % __alignof__ (l_তথ্য.weights[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_তথ্য.extra) % __alignof__ (l_তথ্য.extra[0]) == 0);
  প্রতিজ্ঞা (((uintptr_t) l_তথ্য.indirect) % __alignof__ (l_তথ্য.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ধ্রুবক USTRING_TYPE *usrc = (ধ্রুবক USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ধ্রুবক USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_আকার * আকার (int32_t));
  unsigned অক্ষর *rulearr = alloca (SMALL_STR_আকার + 1);

  করো
    {
      int32_t tmp = findidx (l_তথ্য.table, l_তথ্য.indirect, l_তথ্য.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  যখন (*cur != L('\0') && idxmax < SMALL_STR_আকার);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  যদি (*cur == L('\0'))
    ফেরত do_xfrm_cached (dest, n, &l_তথ্য, idxmax, idxarr, rulearr);
  অন্যথা
    ফেরত do_xfrm (usrc, dest, n, &l_তথ্য);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
