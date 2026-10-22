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

#समावेश <assert.h>
#समावेश <langinfo.h>
#समावेश <locale.h>
#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <sys/param.h>

#अगर_अघोषित STRING_TYPE
# define STRING_TYPE अक्षर
# define USTRING_TYPE अचिन्हित अक्षर
# define STRXFRM __strxfrm_l
# define STRLEN म_माप
# define STPNCPY __stpncpy
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#पूर्ण_अगर

#घोषणा CONCAT(a,b) CONCAT1(a,b)
#घोषणा CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#घोषणा SMALL_STR_आकार 4095

#समावेश "../locale/localeinfo.h"
#समावेश WEIGHT_H

/* Group locale data for shorter parameter lists.  */
प्रकार काष्ठा
{
  uint32_t nrules;
  अचिन्हित अक्षर *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_तथ्य_t;

#अगर_अघोषित WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
अटल पूर्णांक
utf8_encode (अक्षर *buf, पूर्णांक val)
{
  पूर्णांक retval;

  अगर (val < 0x80)
    {
      *buf++ = (अक्षर) val;
      retval = 1;
    }
  अन्यथा
    {
      पूर्णांक step;

      क्रम (step = 2; step < 6; ++step)
	अगर ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  अवरोध;
      retval = step;

      *buf = (अचिन्हित अक्षर) (~0xff >> step);
      --step;
      करो
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      जबतक (--step > 0);
      *buf |= val;
    }

  वापस retval;
}
#पूर्ण_अगर

/* Find next weight and rule index.  Inlined since called for every char.  */
अटल __always_inline माप_प्रकार
find_idx (स्थिर USTRING_TYPE **us, int32_t *weight_idx,
	  अचिन्हित अक्षर *rule_idx, स्थिर locale_तथ्य_t *l_तथ्य, स्थिर पूर्णांक pass)
{
  int32_t tmp = findidx (l_तथ्य->table, l_तथ्य->indirect, l_तथ्य->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  माप_प्रकार len = l_तथ्य->weights[idx++];

  /* Skip over indices of previous levels.  */
  क्रम (पूर्णांक i = 0; i < pass; i++)
    {
      idx += len;
      len = l_तथ्य->weights[idx++];
    }

  *weight_idx = idx;
  वापस len;
}

अटल पूर्णांक
find_position (स्थिर USTRING_TYPE *us, स्थिर locale_तथ्य_t *l_तथ्य,
	       स्थिर पूर्णांक pass)
{
  int32_t weight_idx;
  अचिन्हित अक्षर rule_idx;
  स्थिर USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_तथ्य, pass);
  वापस l_तथ्य->rulesets[rule_idx * l_तथ्य->nrules + pass] & sort_position;
}

/* Do the transformation.  */
अटल माप_प्रकार
do_xfrm (स्थिर USTRING_TYPE *usrc, STRING_TYPE *dest, माप_प्रकार n,
	 स्थिर locale_तथ्य_t *l_तथ्य)
{
  int32_t weight_idx;
  अचिन्हित अक्षर rule_idx;
  uint32_t pass;
  माप_प्रकार needed = 0;
  माप_प्रकार last_needed;

  /* Now the passes over the weights.  */
  क्रम (pass = 0; pass < l_तथ्य->nrules; ++pass)
    {
      माप_प्रकार backw_len = 0;
      last_needed = needed;
      स्थिर USTRING_TYPE *cur = usrc;
      स्थिर USTRING_TYPE *backw_start = शून्य;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      पूर्णांक position = find_position (cur, l_तथ्य, pass);

      अगर (position == 0)
	{
	  जबतक (*cur != L('\0'))
	    {
	      स्थिर USTRING_TYPE *pos = cur;
	      माप_प्रकार len = find_idx (&cur, &weight_idx, &rule_idx, l_तथ्य,
				     pass);
	      पूर्णांक rule = l_तथ्य->rulesets[rule_idx * l_तथ्य->nrules + pass];

	      अगर ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  अगर (backw_start != शून्य)
		    {
		      क्रम (माप_प्रकार i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  अचिन्हित अक्षर rule_idx;
			  माप_प्रकार len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_तथ्य, pass);
			  अगर (needed + i < n)
			    क्रम (माप_प्रकार j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_तथ्य->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = शून्य;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  अगर (needed + len < n)
		    जबतक (len-- > 0)
		      dest[needed++] = l_तथ्य->weights[weight_idx++];
		  अन्यथा
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  अगर (backw_start == शून्य)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  अगर (backw_start != शून्य)
	    {
	      क्रम (माप_प्रकार i = backw_len; i > 0; )
		{
		  माप_प्रकार len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_तथ्य, pass);
		  अगर (needed + i < n)
		    क्रम (माप_प्रकार j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_तथ्य->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      अन्यथा
	{
	  पूर्णांक val = 1;
#अगर_अघोषित WIDE_CHAR_VERSION
	  अक्षर buf[7];
	  माप_प्रकार buflen;
#पूर्ण_अगर
	  माप_प्रकार i;

	  जबतक (*cur != L('\0'))
	    {
	      स्थिर USTRING_TYPE *pos = cur;
	      माप_प्रकार len = find_idx (&cur, &weight_idx, &rule_idx, l_तथ्य,
				     pass);
	      पूर्णांक rule = l_तथ्य->rulesets[rule_idx * l_तथ्य->nrules + pass];

	      अगर ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  अगर (backw_start != शून्य)
		    {
		      क्रम (माप_प्रकार p = backw_len; p > 0; p--)
			{
			  माप_प्रकार len;
			  int32_t weight_idx;
			  अचिन्हित अक्षर rule_idx;
			  स्थिर USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_तथ्य, pass);

			  क्रम (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_तथ्य, pass);

			  अगर (len != 0)
			    {
#अगर_घोषित WIDE_CHAR_VERSION
			      अगर (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  क्रम (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_तथ्य->weights[weight_idx + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      अगर (needed + buflen + len < n)
				{
				  क्रम (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  क्रम (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_तथ्य->weights[weight_idx + i];
				}
			      needed += buflen + len;
#पूर्ण_अगर
			      val = 1;
			    }
			  अन्यथा
			    ++val;
			}

		      backw_start = शून्य;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  अगर (len != 0)
		    {
#अगर_घोषित WIDE_CHAR_VERSION
		      अगर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_तथ्य->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      अगर (needed + buflen + len < n)
			{
			  क्रम (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_तथ्य->weights[weight_idx + i];
			}
		      needed += buflen + len;
#पूर्ण_अगर
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	      अन्यथा
		{
		  /* Remember start of the backward sequence & track length.  */
		  अगर (backw_start == शून्य)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  अगर (backw_start != शून्य)
	    {
	      क्रम (माप_प्रकार p = backw_len; p > 0; p--)
		{
		  माप_प्रकार len;
		  int32_t weight_idx;
		  अचिन्हित अक्षर rule_idx;
		  स्थिर USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_तथ्य, pass);

		  क्रम (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_तथ्य, pass);

		  अगर (len != 0)
		    {
#अगर_घोषित WIDE_CHAR_VERSION
		      अगर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_तथ्य->weights[weight_idx + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      अगर (needed + buflen + len < n)
			{
			  क्रम (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_तथ्य->weights[weight_idx + i];
			}
		      needed += buflen + len;
#पूर्ण_अगर
		      val = 1;
		    }
		  अन्यथा
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      अगर (needed < n)
	dest[needed] = pass + 1 < l_तथ्य->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  अगर (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      अगर (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  वापस needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
अटल माप_प्रकार
do_xfrm_cached (STRING_TYPE *dest, माप_प्रकार n, स्थिर locale_तथ्य_t *l_तथ्य,
		माप_प्रकार idxmax, int32_t *idxarr, स्थिर अचिन्हित अक्षर *rulearr)
{
  uint32_t nrules = l_तथ्य->nrules;
  अचिन्हित अक्षर *rulesets = l_तथ्य->rulesets;
  USTRING_TYPE *weights = l_तथ्य->weights;
  uint32_t pass;
  माप_प्रकार needed = 0;
  माप_प्रकार last_needed;
  माप_प्रकार idxcnt;

  /* Now the passes over the weights.  */
  क्रम (pass = 0; pass < nrules; ++pass)
    {
      माप_प्रकार backw_stop = ~0ul;
      पूर्णांक rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      पूर्णांक position = rule & sort_position;

      last_needed = needed;
      अगर (position == 0)
	{
	  क्रम (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      अगर ((rule & sort_forward) != 0)
		{
		  माप_प्रकार len;

		  अगर (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      माप_प्रकार backw;

		      क्रम (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  अगर (needed + len < n)
			    जबतक (len-- > 0)
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
		  अगर (needed + len < n)
		    जबतक (len-- > 0)
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
		  अगर (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  अगर (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      माप_प्रकार backw;

	      backw = idxcnt;
	      जबतक (backw > backw_stop)
		{
		  माप_प्रकार len = weights[idxarr[--backw]++];

		  अगर (needed + len < n)
		    जबतक (len-- > 0)
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
#अगर_अघोषित WIDE_CHAR_VERSION
	  अक्षर buf[7];
	  माप_प्रकार buflen;
#पूर्ण_अगर
	  माप_प्रकार i;

	  क्रम (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      अगर ((rule & sort_forward) != 0)
		{
		  माप_प्रकार len;

		  अगर (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      माप_प्रकार backw;

		      क्रम (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  अगर (len != 0)
			    {
#अगर_घोषित WIDE_CHAR_VERSION
			      अगर (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  क्रम (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#अन्यथा
			      buflen = utf8_encode (buf, val);
			      अगर (needed + buflen + len < n)
				{
				  क्रम (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  क्रम (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#पूर्ण_अगर
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
		  अगर (len != 0)
		    {
#अगर_घोषित WIDE_CHAR_VERSION
		      अगर (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      अगर (needed + buflen + len < n)
			{
			  क्रम (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#पूर्ण_अगर
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
		  अगर (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  अगर (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      माप_प्रकार backw;

	      backw = idxmax - 1;
	      जबतक (backw > backw_stop)
		{
		  माप_प्रकार len = weights[idxarr[--backw]++];
		  अगर (len != 0)
		    {
#अगर_घोषित WIDE_CHAR_VERSION
		      अगर (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#अन्यथा
		      buflen = utf8_encode (buf, val);
		      अगर (needed + buflen + len < n)
			{
			  क्रम (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  क्रम (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#पूर्ण_अगर
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
      अगर (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  अगर (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      अगर (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  वापस needed - 1;
}

माप_प्रकार
STRXFRM (STRING_TYPE *dest, स्थिर STRING_TYPE *src, माप_प्रकार n, locale_t l)
{
  locale_तथ्य_t l_तथ्य;
  काष्ठा __locale_data *current = l->__locales[LC_COLLATE];
  l_तथ्य.nrules = current->मूल्यावली[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  अगर (l_तथ्य.nrules == 0)
    {
      माप_प्रकार srclen = STRLEN (src);

      अगर (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      वापस srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  अगर (*src == L('\0'))
    {
      अगर (n != 0)
	*dest = L('\0');
      वापस 0;
    }

  /* Get the locale data.  */
  l_तथ्य.rulesets = (अचिन्हित अक्षर *)
    current->मूल्यावली[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_तथ्य.table = (int32_t *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_तथ्य.weights = (USTRING_TYPE *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_तथ्य.extra = (USTRING_TYPE *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_तथ्य.indirect = (int32_t *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  निश्चित (((uintptr_t) l_तथ्य.table) % __alignof__ (l_तथ्य.table[0]) == 0);
  निश्चित (((uintptr_t) l_तथ्य.weights) % __alignof__ (l_तथ्य.weights[0]) == 0);
  निश्चित (((uintptr_t) l_तथ्य.extra) % __alignof__ (l_तथ्य.extra[0]) == 0);
  निश्चित (((uintptr_t) l_तथ्य.indirect) % __alignof__ (l_तथ्य.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  स्थिर USTRING_TYPE *usrc = (स्थिर USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  माप_प्रकार idxmax = 0;
  स्थिर USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_आकार * माप (int32_t));
  अचिन्हित अक्षर *rulearr = alloca (SMALL_STR_आकार + 1);

  करो
    {
      int32_t tmp = findidx (l_तथ्य.table, l_तथ्य.indirect, l_तथ्य.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  जबतक (*cur != L('\0') && idxmax < SMALL_STR_आकार);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  अगर (*cur == L('\0'))
    वापस do_xfrm_cached (dest, n, &l_तथ्य, idxmax, idxarr, rulearr);
  अन्यथा
    वापस do_xfrm (usrc, dest, n, &l_तथ्य);
}
libc_hidden_def (STRXFRM)

#अगर_अघोषित WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#पूर्ण_अगर
