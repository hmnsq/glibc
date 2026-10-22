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

#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <langinfo.h>
#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/param.h>

#ifndef STRING_TYPE
# define STRING_TYPE അക്ഷരം
# define USTRING_TYPE unsigned അക്ഷരം
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

#അന്തര്ഭാവ "../locale/localeinfo.h"
#അന്തര്ഭാവ WEIGHT_H

/* Group locale data for shorter parameter lists.  */
തരനിർവചനം ഘടന
{
  uint32_t nrules;
  unsigned അക്ഷരം *rulesets;
  USTRING_TYPE *weights;
  int32_t *table;
  USTRING_TYPE *extra;
  int32_t *indirect;
} locale_data_t;

#ifndef WIDE_CHAR_VERSION

/* We need UTF-8 encoding of numbers.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ
utf8_encode (അക്ഷരം *buf, പൂർണ്ണസംഖ്യ val)
{
  പൂർണ്ണസംഖ്യ retval;

  എങ്കിൽ (val < 0x80)
    {
      *buf++ = (അക്ഷരം) val;
      retval = 1;
    }
  അല്ലെങ്കിൽ
    {
      പൂർണ്ണസംഖ്യ step;

      വേണ്ടി (step = 2; step < 6; ++step)
	എങ്കിൽ ((val & (~(uint32_t)0 << (5 * step + 1))) == 0)
	  നിർത്തുക;
      retval = step;

      *buf = (unsigned അക്ഷരം) (~0xff >> step);
      --step;
      ചെയ്യുക
	{
	  buf[step] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      ആകുമ്പോൾ (--step > 0);
      *buf |= val;
    }

  തിരികെ retval;
}
#endif

/* Find next weight and rule index.  Inlined since called for every char.  */
സ്ഥിതം __always_inline size_t
find_idx (സ്ഥിരം USTRING_TYPE **us, int32_t *weight_idx,
	  unsigned അക്ഷരം *rule_idx, സ്ഥിരം locale_data_t *l_data, സ്ഥിരം പൂർണ്ണസംഖ്യ pass)
{
  int32_t tmp = findidx (l_data->table, l_data->indirect, l_data->extra, us,
			 -1);
  *rule_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_data->weights[idx++];

  /* Skip over indices of previous levels.  */
  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < pass; i++)
    {
      idx += len;
      len = l_data->weights[idx++];
    }

  *weight_idx = idx;
  തിരികെ len;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
find_position (സ്ഥിരം USTRING_TYPE *us, സ്ഥിരം locale_data_t *l_data,
	       സ്ഥിരം പൂർണ്ണസംഖ്യ pass)
{
  int32_t weight_idx;
  unsigned അക്ഷരം rule_idx;
  സ്ഥിരം USTRING_TYPE *usrc = us;

  find_idx (&usrc, &weight_idx, &rule_idx, l_data, pass);
  തിരികെ l_data->rulesets[rule_idx * l_data->nrules + pass] & sort_position;
}

/* Do the transformation.  */
സ്ഥിതം size_t
do_xfrm (സ്ഥിരം USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 സ്ഥിരം locale_data_t *l_data)
{
  int32_t weight_idx;
  unsigned അക്ഷരം rule_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;

  /* Now the passes over the weights.  */
  വേണ്ടി (pass = 0; pass < l_data->nrules; ++pass)
    {
      size_t backw_len = 0;
      last_needed = needed;
      സ്ഥിരം USTRING_TYPE *cur = usrc;
      സ്ഥിരം USTRING_TYPE *backw_start = ശൂന്യ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      പൂർണ്ണസംഖ്യ position = find_position (cur, l_data, pass);

      എങ്കിൽ (position == 0)
	{
	  ആകുമ്പോൾ (*cur != L('\0'))
	    {
	      സ്ഥിരം USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      പൂർണ്ണസംഖ്യ rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      എങ്കിൽ ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  എങ്കിൽ (backw_start != ശൂന്യ)
		    {
		      വേണ്ടി (size_t i = backw_len; i > 0; )
			{
			  int32_t weight_idx;
			  unsigned അക്ഷരം rule_idx;
			  size_t len = find_idx (&backw_start, &weight_idx,
						 &rule_idx, l_data, pass);
			  എങ്കിൽ (needed + i < n)
			    വേണ്ടി (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_data->weights[weight_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_start = ശൂന്യ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  എങ്കിൽ (needed + len < n)
		    ആകുമ്പോൾ (len-- > 0)
		      dest[needed++] = l_data->weights[weight_idx++];
		  അല്ലെങ്കിൽ
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      അല്ലെങ്കിൽ
		{
		  /* Remember start of the backward sequence & track length.  */
		  എങ്കിൽ (backw_start == ശൂന്യ)
		    backw_start = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  എങ്കിൽ (backw_start != ശൂന്യ)
	    {
	      വേണ്ടി (size_t i = backw_len; i > 0; )
		{
		  size_t len = find_idx (&backw_start, &weight_idx, &rule_idx,
					 l_data, pass);
		  എങ്കിൽ (needed + i < n)
		    വേണ്ടി (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_data->weights[weight_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      അല്ലെങ്കിൽ
	{
	  പൂർണ്ണസംഖ്യ val = 1;
#ifndef WIDE_CHAR_VERSION
	  അക്ഷരം buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  ആകുമ്പോൾ (*cur != L('\0'))
	    {
	      സ്ഥിരം USTRING_TYPE *pos = cur;
	      size_t len = find_idx (&cur, &weight_idx, &rule_idx, l_data,
				     pass);
	      പൂർണ്ണസംഖ്യ rule = l_data->rulesets[rule_idx * l_data->nrules + pass];

	      എങ്കിൽ ((rule & sort_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  എങ്കിൽ (backw_start != ശൂന്യ)
		    {
		      വേണ്ടി (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t weight_idx;
			  unsigned അക്ഷരം rule_idx;
			  സ്ഥിരം USTRING_TYPE *backw_cur = backw_start;

			  /* To prevent a warning init the used vars.  */
			  len = find_idx (&backw_cur, &weight_idx,
					  &rule_idx, l_data, pass);

			  വേണ്ടി (i = 1; i < p; i++)
			    len = find_idx (&backw_cur, &weight_idx,
					    &rule_idx, l_data, pass);

			  എങ്കിൽ (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      എങ്കിൽ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  വേണ്ടി (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += 1 + len;
#അല്ലെങ്കിൽ
			      buflen = utf8_encode (buf, val);
			      എങ്കിൽ (needed + buflen + len < n)
				{
				  വേണ്ടി (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  വേണ്ടി (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_data->weights[weight_idx + i];
				}
			      needed += buflen + len;
#endif
			      val = 1;
			    }
			  അല്ലെങ്കിൽ
			    ++val;
			}

		      backw_start = ശൂന്യ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  എങ്കിൽ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      എങ്കിൽ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#അല്ലെങ്കിൽ
		      buflen = utf8_encode (buf, val);
		      എങ്കിൽ (needed + buflen + len < n)
			{
			  വേണ്ടി (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  അല്ലെങ്കിൽ
		    ++val;
		}
	      അല്ലെങ്കിൽ
		{
		  /* Remember start of the backward sequence & track length.  */
		  എങ്കിൽ (backw_start == ശൂന്യ)
		    backw_start = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  എങ്കിൽ (backw_start != ശൂന്യ)
	    {
	      വേണ്ടി (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t weight_idx;
		  unsigned അക്ഷരം rule_idx;
		  സ്ഥിരം USTRING_TYPE *backw_cur = backw_start;

		  /* To prevent a warning init the used vars.  */
		  len = find_idx (&backw_cur, &weight_idx,
				  &rule_idx, l_data, pass);

		  വേണ്ടി (i = 1; i < p; i++)
		    len = find_idx (&backw_cur, &weight_idx,
				    &rule_idx, l_data, pass);

		  എങ്കിൽ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      എങ്കിൽ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += 1 + len;
#അല്ലെങ്കിൽ
		      buflen = utf8_encode (buf, val);
		      എങ്കിൽ (needed + buflen + len < n)
			{
			  വേണ്ടി (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_data->weights[weight_idx + i];
			}
		      needed += buflen + len;
#endif
		      val = 1;
		    }
		  അല്ലെങ്കിൽ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      എങ്കിൽ (needed < n)
	dest[needed] = pass + 1 < l_data->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  എങ്കിൽ (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      എങ്കിൽ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  തിരികെ needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
സ്ഥിതം size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, സ്ഥിരം locale_data_t *l_data,
		size_t idxmax, int32_t *idxarr, സ്ഥിരം unsigned അക്ഷരം *rulearr)
{
  uint32_t nrules = l_data->nrules;
  unsigned അക്ഷരം *rulesets = l_data->rulesets;
  USTRING_TYPE *weights = l_data->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t last_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  വേണ്ടി (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      പൂർണ്ണസംഖ്യ rule = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      പൂർണ്ണസംഖ്യ position = rule & sort_position;

      last_needed = needed;
      എങ്കിൽ (position == 0)
	{
	  വേണ്ടി (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      എങ്കിൽ ((rule & sort_forward) != 0)
		{
		  size_t len;

		  എങ്കിൽ (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      വേണ്ടി (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  എങ്കിൽ (needed + len < n)
			    ആകുമ്പോൾ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  അല്ലെങ്കിൽ
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
		  എങ്കിൽ (needed + len < n)
		    ആകുമ്പോൾ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  അല്ലെങ്കിൽ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      അല്ലെങ്കിൽ
		{
		  /* Remember where the backwards series started.  */
		  എങ്കിൽ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  എങ്കിൽ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      ആകുമ്പോൾ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  എങ്കിൽ (needed + len < n)
		    ആകുമ്പോൾ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  അല്ലെങ്കിൽ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      അല്ലെങ്കിൽ
	{
	  പൂർണ്ണസംഖ്യ val = 1;
#ifndef WIDE_CHAR_VERSION
	  അക്ഷരം buf[7];
	  size_t buflen;
#endif
	  size_t i;

	  വേണ്ടി (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      എങ്കിൽ ((rule & sort_forward) != 0)
		{
		  size_t len;

		  എങ്കിൽ (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      വേണ്ടി (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  എങ്കിൽ (len != 0)
			    {
#ifdef WIDE_CHAR_VERSION
			      എങ്കിൽ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  വേണ്ടി (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#അല്ലെങ്കിൽ
			      buflen = utf8_encode (buf, val);
			      എങ്കിൽ (needed + buflen + len < n)
				{
				  വേണ്ടി (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  വേണ്ടി (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#endif
			      idxarr[backw] += len;
			      val = 1;
			    }
			  അല്ലെങ്കിൽ
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  എങ്കിൽ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      എങ്കിൽ (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#അല്ലെങ്കിൽ
		      buflen = utf8_encode (buf, val);
		      എങ്കിൽ (needed + buflen + len < n)
			{
			  വേണ്ടി (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  അല്ലെങ്കിൽ
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      അല്ലെങ്കിൽ
		{
		  /* Remember where the backwards series started.  */
		  എങ്കിൽ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      rule = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  എങ്കിൽ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      ആകുമ്പോൾ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  എങ്കിൽ (len != 0)
		    {
#ifdef WIDE_CHAR_VERSION
		      എങ്കിൽ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#അല്ലെങ്കിൽ
		      buflen = utf8_encode (buf, val);
		      എങ്കിൽ (needed + buflen + len < n)
			{
			  വേണ്ടി (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  വേണ്ടി (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#endif
		      idxarr[backw] += len;
		      val = 1;
		    }
		  അല്ലെങ്കിൽ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      എങ്കിൽ (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  എങ്കിൽ (needed > 2 && needed == last_needed + 1)
    {
      /* Remove the \1 byte.  */
      എങ്കിൽ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  തിരികെ needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, സ്ഥിരം STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  ഘടന __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;

  /* Handle byte comparison case.  */
  എങ്കിൽ (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      എങ്കിൽ (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      തിരികെ srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  എങ്കിൽ (*src == L('\0'))
    {
      എങ്കിൽ (n != 0)
	*dest = L('\0');
      തിരികെ 0;
    }

  /* Get the locale data.  */
  l_data.rulesets = (unsigned അക്ഷരം *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  പ്രതിജ്ഞാ (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  സ്ഥിരം USTRING_TYPE *usrc = (സ്ഥിരം USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  സ്ഥിരം USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * വലുപ്പം (int32_t));
  unsigned അക്ഷരം *rulearr = alloca (SMALL_STR_SIZE + 1);

  ചെയ്യുക
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  ആകുമ്പോൾ (*cur != L('\0') && idxmax < SMALL_STR_SIZE);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  എങ്കിൽ (*cur == L('\0'))
    തിരികെ do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  അല്ലെങ്കിൽ
    തിരികെ do_xfrm (usrc, dest, n, &l_data);
}
libc_hidden_def (STRXFRM)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strxfrm_l, strxfrm_l)
#endif
