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

#यदि_अपरिभाषितम् STRING_TYPE
# define STRING_TYPE वर्ण
# define USTRING_TYPE अचिह्नित वर्ण
# define STRXFRM __strxfrm_l
# define STRLEN वाक्यदैर्घ्यम्
# define STPNCPY __stpncpy
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#यदि_अन्तः

#परिभाषय CONCAT(a,b) CONCAT1(a,b)
#परिभाषय CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#परिभाषय SMALL_STR_आकार 4095

#अन्तर्भाव "../locale/localeinfo.h"
#अन्तर्भाव WEIGHT_H

/* Group locale data for shorter parameter lists.  */
प्रकारनिर्देश संरचना
{
  uint32_t nrules;
  अचिह्नित वर्ण *rulesets;
  USTRING_TYPE *weights;
  int32_t *सारणी;
  USTRING_TYPE *extra;
  int32_t *परोक्षम्;
} locale_दत्त_t;

#यदि_अपरिभाषितम् WIDE_CHAR_संस्करणम्

/* We need UTF-8 encoding of numbers.  */
स्थिर पूर्णाङ्क
utf8_encode (वर्ण *buf, पूर्णाङ्क val)
{
  पूर्णाङ्क retval;

  यदि (val < 0x80)
    {
      *buf++ = (वर्ण) val;
      retval = 1;
    }
  अन्यथा
    {
      पूर्णाङ्क चरणः;

      प्रति (चरणः = 2; चरणः < 6; ++चरणः)
	यदि ((val & (~(uint32_t)0 << (5 * चरणः + 1))) == 0)
	  भङ्ग;
      retval = चरणः;

      *buf = (अचिह्नित वर्ण) (~0xff >> चरणः);
      --चरणः;
      कुरु
	{
	  buf[चरणः] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      यावत् (--चरणः > 0);
      *buf |= val;
    }

  प्रत्यागम retval;
}
#यदि_अन्तः

/* Find next weight and rule index.  Inlined since called for every char.  */
स्थिर __always_inline size_t
find_idx (ध्रुव USTRING_TYPE **us, int32_t *weight_idx,
	  अचिह्नित वर्ण *नियमः_idx, ध्रुव locale_दत्त_t *l_दत्त, ध्रुव पूर्णाङ्क pass)
{
  int32_t tmp = findidx (l_दत्त->सारणी, l_दत्त->परोक्षम्, l_दत्त->extra, us,
			 -1);
  *नियमः_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_दत्त->weights[idx++];

  /* Skip over indices of previous levels.  */
  प्रति (पूर्णाङ्क i = 0; i < pass; i++)
    {
      idx += len;
      len = l_दत्त->weights[idx++];
    }

  *weight_idx = idx;
  प्रत्यागम len;
}

स्थिर पूर्णाङ्क
find_position (ध्रुव USTRING_TYPE *us, ध्रुव locale_दत्त_t *l_दत्त,
	       ध्रुव पूर्णाङ्क pass)
{
  int32_t weight_idx;
  अचिह्नित वर्ण नियमः_idx;
  ध्रुव USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &नियमः_idx, l_दत्त, pass);
  प्रत्यागम l_दत्त->rulesets[नियमः_idx * l_दत्त->nrules + pass] & क्रमय_position;
}

/* Do the transformation.  */
स्थिर size_t
do_xfrm (ध्रुव USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ध्रुव locale_दत्त_t *l_दत्त)
{
  int32_t weight_idx;
  अचिह्नित वर्ण नियमः_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t चरमः_needed;

  /* Now the passes over the weights.  */
  प्रति (pass = 0; pass < l_दत्त->nrules; ++pass)
    {
      size_t backw_len = 0;
      चरमः_needed = needed;
      ध्रुव USTRING_TYPE *cur = usrc;
      ध्रुव USTRING_TYPE *backw_start = रिक्त;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      पूर्णाङ्क position = find_position (cur, l_दत्त, pass);

      यदि (position == 0)
	{
	  यावत् (*cur != L('\0'))
	    {
	      ध्रुव USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &नियमः_idx, l_दत्त,
				     pass);
	      पूर्णाङ्क नियमः = l_दत्त->rulesets[नियमः_idx * l_दत्त->nrules + pass];

	      यदि ((नियमः & क्रमय_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  यदि (backw_start != रिक्त)
		    {
		      प्रति (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  अचिह्नित वर्ण नियमः_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &नियमः_idx, l_दत्त, pass);
			  यदि (needed + i < n)
			    प्रति (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_दत्त->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  यदि (needed + len < n)
		    यावत् (len-- > 0)
		      dest[needed++] = l_दत्त->weights[weight_idx++];
		  अन्यथा
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  यदि (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  यदि (backw_start != रिक्त)
	    {
	      प्रति (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &नियमः_idx,
					 l_दत्त, pass);
		  यदि (needed + i < n)
		    प्रति (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_दत्त->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      अन्यथा
	{
	  पूर्णाङ्क val = 1;
#यदि_अपरिभाषितम् WIDE_CHAR_संस्करणम्
	  वर्ण buf[7];
	  size_t buflen;
#यदि_अन्तः
	  size_t i;

	  यावत् (*cur != L('\0'))
	    {
	      ध्रुव USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &नियमः_idx, l_दत्त,
				     pass);
	      पूर्णाङ्क नियमः = l_दत्त->rulesets[नियमः_idx * l_दत्त->nrules + pass];

	      यदि ((नियमः & क्रमय_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  यदि (backw_start != रिक्त)
		    {
		      प्रति (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  अचिह्नित वर्ण नियमः_idx;
			  ध्रुव USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &नियमः_idx, l_दत्त, pass);

			  प्रति (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &नियमः_idx, l_दत्त, pass);

			  यदि (len != 0)
			    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
			      यदि (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  प्रति (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_दत्त->weights[weight_idx + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      यदि (needed + buflen + len < n)
				{
				  प्रति (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  प्रति (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_दत्त->weights[weight_idx + i];
				}
			      needed += buflen + len;
#यदि_अन्तः
			      val = 1;
			    }
			  अन्यथा
			    ++val;
			}

		      backw_start = रिक्त;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  यदि (len != 0)
		    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
		      यदि (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_दत्त->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      यदि (needed + buflen + len < n)
			{
			  प्रति (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_दत्त->weights[weight_idx + i];
			}
		      needed += buflen + len;
#यदि_अन्तः
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  यदि (backw_start == रिक्त)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  यदि (backw_start != रिक्त)
	    {
	      प्रति (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  अचिह्नित वर्ण नियमः_idx;
		  ध्रुव USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &नियमः_idx, l_दत्त, pass);

		  प्रति (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &नियमः_idx, l_दत्त, pass);

		  यदि (len != 0)
		    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
		      यदि (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_दत्त->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      यदि (needed + buflen + len < n)
			{
			  प्रति (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_दत्त->weights[weight_idx + i];
			}
		      needed += buflen + len;
#यदि_अन्तः
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      यदि (needed < n)
	dest[needed] = pass + 1 < l_दत्त->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  यदि (needed > 2 && needed == चरमः_needed + 1)
    {
      /* Remove the \1 byte.  */
      यदि (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  प्रत्यागम needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
स्थिर size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ध्रुव locale_दत्त_t *l_दत्त,
		size_t idxmax, int32_t *idxarr, ध्रुव अचिह्नित वर्ण *rulearr)
{
  uint32_t nrules = l_दत्त->nrules;
  अचिह्नित वर्ण *rulesets = l_दत्त->rulesets;
  USTRING_TYPE *weights = l_दत्त->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t चरमः_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  प्रति (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      पूर्णाङ्क नियमः = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      पूर्णाङ्क position = नियमः & क्रमय_position;

      चरमः_needed = needed;
      यदि (position == 0)
	{
	  प्रति (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      यदि ((नियमः & क्रमय_forward) != 0)
		{
		  size_t len;

		  यदि (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      प्रति (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  यदि (needed + len < n)
			    यावत् (len-- > 0)
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
		  यदि (needed + len < n)
		    यावत् (len-- > 0)
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
		  यदि (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      नियमः = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  यदि (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      यावत् (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  यदि (needed + len < n)
		    यावत् (len-- > 0)
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
	  पूर्णाङ्क val = 1;
#यदि_अपरिभाषितम् WIDE_CHAR_संस्करणम्
	  वर्ण buf[7];
	  size_t buflen;
#यदि_अन्तः
	  size_t i;

	  प्रति (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      यदि ((नियमः & क्रमय_forward) != 0)
		{
		  size_t len;

		  यदि (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      प्रति (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  यदि (len != 0)
			    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
			      यदि (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  प्रति (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      यदि (needed + buflen + len < n)
				{
				  प्रति (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  प्रति (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#यदि_अन्तः
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
		  यदि (len != 0)
		    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
		      यदि (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      यदि (needed + buflen + len < n)
			{
			  प्रति (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#यदि_अन्तः
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
		  यदि (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      नियमः = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  यदि (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      यावत् (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  यदि (len != 0)
		    {
#यदि_परिभाषितम् WIDE_CHAR_संस्करणम्
		      यदि (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      यदि (needed + buflen + len < n)
			{
			  प्रति (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  प्रति (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#यदि_अन्तः
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
      यदि (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  यदि (needed > 2 && needed == चरमः_needed + 1)
    {
      /* Remove the \1 byte.  */
      यदि (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  प्रत्यागम needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ध्रुव STRING_TYPE *src, size_t n, locale_t l)
{
  locale_दत्त_t l_दत्त;
  संरचना __locale_data *current = l->__locales[LC_COLLATE];
  l_दत्त.nrules = current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  यदि (l_दत्त.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      यदि (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      प्रत्यागम srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  यदि (*src == L('\0'))
    {
      यदि (n != 0)
	*dest = L('\0');
      प्रत्यागम 0;
    }

  /* Get the locale data.  */
  l_दत्त.rulesets = (अचिह्नित वर्ण *)
    current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_दत्त.सारणी = (int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_सारणी,SUFFIX))].string;
  l_दत्त.weights = (USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_दत्त.extra = (USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_दत्त.परोक्षम् = (int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_परोक्षम्,SUFFIX))].string;

  प्रतिज्ञा (((uintptr_t) l_दत्त.सारणी) % __alignof__ (l_दत्त.सारणी[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_दत्त.weights) % __alignof__ (l_दत्त.weights[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_दत्त.extra) % __alignof__ (l_दत्त.extra[0]) == 0);
  प्रतिज्ञा (((uintptr_t) l_दत्त.परोक्षम्) % __alignof__ (l_दत्त.परोक्षम्[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ध्रुव USTRING_TYPE *usrc = (ध्रुव USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ध्रुव USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_आकार * परिमाण (int32_t));
  अचिह्नित वर्ण *rulearr = alloca (SMALL_STR_आकार + 1);

  कुरु
    {
      int32_t tmp = findidx (l_दत्त.सारणी, l_दत्त.परोक्षम्, l_दत्त.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  यावत् (*cur != L('\0') && idxmax < SMALL_STR_आकार);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  यदि (*cur == L('\0'))
    प्रत्यागम do_xfrm_cached (dest, n, &l_दत्त, idxmax, idxarr, rulearr);
  अन्यथा
    प्रत्यागम do_xfrm (usrc, dest, n, &l_दत्त);
}
libc_hidden_def (STRXFRM)

#यदि_अपरिभाषितम् WIDE_CHAR_संस्करणम्
weak_alias (__strxfrm_l, strxfrm_l)
#यदि_अन्तः
