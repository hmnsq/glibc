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

#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <langinfo.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRING_TYPE
# define STRING_TYPE ਅੱਖਰ
# define USTRING_TYPE ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define STRXFRM __strxfrm_l
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STPNCPY __stpncpy
# define ਭਾਰ_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONCAT(a,b) CONCAT1(a,b)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SMALL_STR_ਮਾਪ 4095

#ਅਨ੍ਤਰ੍ਭਾਵ "../locale/localeinfo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ ਭਾਰ_H

/* Group locale data for shorter parameter lists.  */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  uint32_t nrules;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulesets;
  USTRING_TYPE *weights;
  int32_t *ਸਾਰਣੀ;
  USTRING_TYPE *extra;
  int32_t *ਅਸਿੱਧਾ;
} locale_ਅੰਕੜੇ_t;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ

/* We need UTF-8 encoding of numbers.  */
ਸਥਿਰ ਪੂਰਨ
utf8_encode (ਅੱਖਰ *buf, ਪੂਰਨ val)
{
  ਪੂਰਨ retval;

  ਜੇ (val < 0x80)
    {
      *buf++ = (ਅੱਖਰ) val;
      retval = 1;
    }
  ਨਹੀਂਤਾਂ
    {
      ਪੂਰਨ ਕਦਮ;

      ਲਈ (ਕਦਮ = 2; ਕਦਮ < 6; ++ਕਦਮ)
	ਜੇ ((val & (~(uint32_t)0 << (5 * ਕਦਮ + 1))) == 0)
	  ਰੋਕੋ;
      retval = ਕਦਮ;

      *buf = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) (~0xff >> ਕਦਮ);
      --ਕਦਮ;
      ਕਰੋ
	{
	  buf[ਕਦਮ] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      ਜਦੋਂ (--ਕਦਮ > 0);
      *buf |= val;
    }

  ਵਾਪਸ retval;
}
#ਜੇ_ਅੰਤ

/* Find next weight and rule index.  Inlined since called for every char.  */
ਸਥਿਰ __always_inline size_t
ਲੱਭੋ_idx (ਅਚਲ USTRING_TYPE **us, int32_t *ਭਾਰ_idx,
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਨਿਯਮ_idx, ਅਚਲ locale_ਅੰਕੜੇ_t *l_ਅੰਕੜੇ, ਅਚਲ ਪੂਰਨ pass)
{
  int32_t tmp = findidx (l_ਅੰਕੜੇ->ਸਾਰਣੀ, l_ਅੰਕੜੇ->ਅਸਿੱਧਾ, l_ਅੰਕੜੇ->extra, us,
			 -1);
  *ਨਿਯਮ_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_ਅੰਕੜੇ->weights[idx++];

  /* Skip over indices of previous levels.  */
  ਲਈ (ਪੂਰਨ i = 0; i < pass; i++)
    {
      idx += len;
      len = l_ਅੰਕੜੇ->weights[idx++];
    }

  *ਭਾਰ_idx = idx;
  ਵਾਪਸ len;
}

ਸਥਿਰ ਪੂਰਨ
ਲੱਭੋ_position (ਅਚਲ USTRING_TYPE *us, ਅਚਲ locale_ਅੰਕੜੇ_t *l_ਅੰਕੜੇ,
	       ਅਚਲ ਪੂਰਨ pass)
{
  int32_t ਭਾਰ_idx;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ_idx;
  ਅਚਲ USTRING_TYPE *usrc = us;

  ਲੱਭੋ_idx (&usrc, &ਭਾਰ_idx, &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);
  ਵਾਪਸ l_ਅੰਕੜੇ->rulesets[ਨਿਯਮ_idx * l_ਅੰਕੜੇ->nrules + pass] & ਛਾਂਟੋ_position;
}

/* Do the transformation.  */
ਸਥਿਰ size_t
do_xfrm (ਅਚਲ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ਅਚਲ locale_ਅੰਕੜੇ_t *l_ਅੰਕੜੇ)
{
  int32_t ਭਾਰ_idx;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t ਆਖਰੀ_needed;

  /* Now the passes over the weights.  */
  ਲਈ (pass = 0; pass < l_ਅੰਕੜੇ->nrules; ++pass)
    {
      size_t backw_len = 0;
      ਆਖਰੀ_needed = needed;
      ਅਚਲ USTRING_TYPE *cur = usrc;
      ਅਚਲ USTRING_TYPE *backw_ਸ਼ੁਰੂ = ਨਿਰਾ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      ਪੂਰਨ position = ਲੱਭੋ_position (cur, l_ਅੰਕੜੇ, pass);

      ਜੇ (position == 0)
	{
	  ਜਦੋਂ (*cur != L('\0'))
	    {
	      ਅਚਲ USTRING_TYPE *pos = cur;
	      size_t len = ਲੱਭੋ_idx (&cur, &ਭਾਰ_idx, &ਨਿਯਮ_idx, l_ਅੰਕੜੇ,
				     pass);
	      ਪੂਰਨ ਨਿਯਮ = l_ਅੰਕੜੇ->rulesets[ਨਿਯਮ_idx * l_ਅੰਕੜੇ->nrules + pass];

	      ਜੇ ((ਨਿਯਮ & ਛਾਂਟੋ_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ਜੇ (backw_ਸ਼ੁਰੂ != ਨਿਰਾ)
		    {
		      ਲਈ (size_t i = backw_len; i > 0; )
			{
			  int32_t ਭਾਰ_idx;
			  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ_idx;
			  size_t len = ਲੱਭੋ_idx (&backw_ਸ਼ੁਰੂ, &ਭਾਰ_idx,
						 &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);
			  ਜੇ (needed + i < n)
			    ਲਈ (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_ਅੰਕੜੇ->weights[ਭਾਰ_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_ਸ਼ੁਰੂ = ਨਿਰਾ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ਜੇ (needed + len < n)
		    ਜਦੋਂ (len-- > 0)
		      dest[needed++] = l_ਅੰਕੜੇ->weights[ਭਾਰ_idx++];
		  ਨਹੀਂਤਾਂ
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ਜੇ (backw_ਸ਼ੁਰੂ == ਨਿਰਾ)
		    backw_ਸ਼ੁਰੂ = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  ਜੇ (backw_ਸ਼ੁਰੂ != ਨਿਰਾ)
	    {
	      ਲਈ (size_t i = backw_len; i > 0; )
		{
		  size_t len = ਲੱਭੋ_idx (&backw_ਸ਼ੁਰੂ, &ਭਾਰ_idx, &ਨਿਯਮ_idx,
					 l_ਅੰਕੜੇ, pass);
		  ਜੇ (needed + i < n)
		    ਲਈ (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_ਅੰਕੜੇ->weights[ਭਾਰ_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  ਪੂਰਨ val = 1;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
	  ਅੱਖਰ buf[7];
	  size_t buflen;
#ਜੇ_ਅੰਤ
	  size_t i;

	  ਜਦੋਂ (*cur != L('\0'))
	    {
	      ਅਚਲ USTRING_TYPE *pos = cur;
	      size_t len = ਲੱਭੋ_idx (&cur, &ਭਾਰ_idx, &ਨਿਯਮ_idx, l_ਅੰਕੜੇ,
				     pass);
	      ਪੂਰਨ ਨਿਯਮ = l_ਅੰਕੜੇ->rulesets[ਨਿਯਮ_idx * l_ਅੰਕੜੇ->nrules + pass];

	      ਜੇ ((ਨਿਯਮ & ਛਾਂਟੋ_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ਜੇ (backw_ਸ਼ੁਰੂ != ਨਿਰਾ)
		    {
		      ਲਈ (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t ਭਾਰ_idx;
			  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ_idx;
			  ਅਚਲ USTRING_TYPE *backw_cur = backw_ਸ਼ੁਰੂ;

			  /* To prevent a warning init the used vars.  */
			  len = ਲੱਭੋ_idx (&backw_cur, &ਭਾਰ_idx,
					  &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);

			  ਲਈ (i = 1; i < p; i++)
			    len = ਲੱਭੋ_idx (&backw_cur, &ਭਾਰ_idx,
					    &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);

			  ਜੇ (len != 0)
			    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
			      ਜੇ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ਲਈ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
				}
			      needed += 1 + len;
#ਨਹੀਂਤਾਂ
			      buflen = utf8_encode (buf, val);
			      ਜੇ (needed + buflen + len < n)
				{
				  ਲਈ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ਲਈ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
				}
			      needed += buflen + len;
#ਜੇ_ਅੰਤ
			      val = 1;
			    }
			  ਨਹੀਂਤਾਂ
			    ++val;
			}

		      backw_ਸ਼ੁਰੂ = ਨਿਰਾ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ਜੇ (len != 0)
		    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
		      ਜੇ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
			}
		      needed += 1 + len;
#ਨਹੀਂਤਾਂ
		      buflen = utf8_encode (buf, val);
		      ਜੇ (needed + buflen + len < n)
			{
			  ਲਈ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
			}
		      needed += buflen + len;
#ਜੇ_ਅੰਤ
		      val = 1;
		    }
		  ਨਹੀਂਤਾਂ
		    ++val;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ਜੇ (backw_ਸ਼ੁਰੂ == ਨਿਰਾ)
		    backw_ਸ਼ੁਰੂ = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  ਜੇ (backw_ਸ਼ੁਰੂ != ਨਿਰਾ)
	    {
	      ਲਈ (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t ਭਾਰ_idx;
		  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ_idx;
		  ਅਚਲ USTRING_TYPE *backw_cur = backw_ਸ਼ੁਰੂ;

		  /* To prevent a warning init the used vars.  */
		  len = ਲੱਭੋ_idx (&backw_cur, &ਭਾਰ_idx,
				  &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);

		  ਲਈ (i = 1; i < p; i++)
		    len = ਲੱਭੋ_idx (&backw_cur, &ਭਾਰ_idx,
				    &ਨਿਯਮ_idx, l_ਅੰਕੜੇ, pass);

		  ਜੇ (len != 0)
		    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
		      ਜੇ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
			}
		      needed += 1 + len;
#ਨਹੀਂਤਾਂ
		      buflen = utf8_encode (buf, val);
		      ਜੇ (needed + buflen + len < n)
			{
			  ਲਈ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ਅੰਕੜੇ->weights[ਭਾਰ_idx + i];
			}
		      needed += buflen + len;
#ਜੇ_ਅੰਤ
		      val = 1;
		    }
		  ਨਹੀਂਤਾਂ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ਜੇ (needed < n)
	dest[needed] = pass + 1 < l_ਅੰਕੜੇ->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ਜੇ (needed > 2 && needed == ਆਖਰੀ_needed + 1)
    {
      /* Remove the \1 byte.  */
      ਜੇ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ਵਾਪਸ needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ਸਥਿਰ size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ਅਚਲ locale_ਅੰਕੜੇ_t *l_ਅੰਕੜੇ,
		size_t idxmax, int32_t *idxarr, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulearr)
{
  uint32_t nrules = l_ਅੰਕੜੇ->nrules;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulesets = l_ਅੰਕੜੇ->rulesets;
  USTRING_TYPE *weights = l_ਅੰਕੜੇ->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t ਆਖਰੀ_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  ਲਈ (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      ਪੂਰਨ ਨਿਯਮ = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      ਪੂਰਨ position = ਨਿਯਮ & ਛਾਂਟੋ_position;

      ਆਖਰੀ_needed = needed;
      ਜੇ (position == 0)
	{
	  ਲਈ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ਜੇ ((ਨਿਯਮ & ਛਾਂਟੋ_forward) != 0)
		{
		  size_t len;

		  ਜੇ (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      ਲਈ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  ਜੇ (needed + len < n)
			    ਜਦੋਂ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  ਨਹੀਂਤਾਂ
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
		  ਜੇ (needed + len < n)
		    ਜਦੋਂ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  ਨਹੀਂਤਾਂ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Remember where the backwards series started.  */
		  ਜੇ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      ਨਿਯਮ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  ਜੇ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      ਜਦੋਂ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  ਜੇ (needed + len < n)
		    ਜਦੋਂ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  ਨਹੀਂਤਾਂ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  ਪੂਰਨ val = 1;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
	  ਅੱਖਰ buf[7];
	  size_t buflen;
#ਜੇ_ਅੰਤ
	  size_t i;

	  ਲਈ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ਜੇ ((ਨਿਯਮ & ਛਾਂਟੋ_forward) != 0)
		{
		  size_t len;

		  ਜੇ (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      ਲਈ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  ਜੇ (len != 0)
			    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
			      ਜੇ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ਲਈ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#ਨਹੀਂਤਾਂ
			      buflen = utf8_encode (buf, val);
			      ਜੇ (needed + buflen + len < n)
				{
				  ਲਈ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ਲਈ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#ਜੇ_ਅੰਤ
			      idxarr[backw] += len;
			      val = 1;
			    }
			  ਨਹੀਂਤਾਂ
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ਜੇ (len != 0)
		    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
		      ਜੇ (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#ਨਹੀਂਤਾਂ
		      buflen = utf8_encode (buf, val);
		      ਜੇ (needed + buflen + len < n)
			{
			  ਲਈ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#ਜੇ_ਅੰਤ
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  ਨਹੀਂਤਾਂ
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Remember where the backwards series started.  */
		  ਜੇ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      ਨਿਯਮ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  ਜੇ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      ਜਦੋਂ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  ਜੇ (len != 0)
		    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
		      ਜੇ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#ਨਹੀਂਤਾਂ
		      buflen = utf8_encode (buf, val);
		      ਜੇ (needed + buflen + len < n)
			{
			  ਲਈ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ਲਈ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#ਜੇ_ਅੰਤ
		      idxarr[backw] += len;
		      val = 1;
		    }
		  ਨਹੀਂਤਾਂ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ਜੇ (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ਜੇ (needed > 2 && needed == ਆਖਰੀ_needed + 1)
    {
      /* Remove the \1 byte.  */
      ਜੇ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ਵਾਪਸ needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ਅਚਲ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_ਅੰਕੜੇ_t l_ਅੰਕੜੇ;
  ਬਣਤਰ __locale_data *current = l->__locales[LC_COLLATE];
  l_ਅੰਕੜੇ.nrules = current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].ਸ਼ਬਦ;

  /* Handle byte comparison case.  */
  ਜੇ (l_ਅੰਕੜੇ.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      ਜੇ (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ਵਾਪਸ srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  ਜੇ (*src == L('\0'))
    {
      ਜੇ (n != 0)
	*dest = L('\0');
      ਵਾਪਸ 0;
    }

  /* Get the locale data.  */
  l_ਅੰਕੜੇ.rulesets = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_ਅੰਕੜੇ.ਸਾਰਣੀ = (int32_t *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਸਾਰਣੀ,SUFFIX))].string;
  l_ਅੰਕੜੇ.weights = (USTRING_TYPE *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਭਾਰ,SUFFIX))].string;
  l_ਅੰਕੜੇ.extra = (USTRING_TYPE *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_ਅੰਕੜੇ.ਅਸਿੱਧਾ = (int32_t *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਅਸਿੱਧਾ,SUFFIX))].string;

  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) l_ਅੰਕੜੇ.ਸਾਰਣੀ) % __alignof__ (l_ਅੰਕੜੇ.ਸਾਰਣੀ[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) l_ਅੰਕੜੇ.weights) % __alignof__ (l_ਅੰਕੜੇ.weights[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) l_ਅੰਕੜੇ.extra) % __alignof__ (l_ਅੰਕੜੇ.extra[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) l_ਅੰਕੜੇ.ਅਸਿੱਧਾ) % __alignof__ (l_ਅੰਕੜੇ.ਅਸਿੱਧਾ[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ਅਚਲ USTRING_TYPE *usrc = (ਅਚਲ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ਅਚਲ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_ਮਾਪ * ਆਕਾਰ (int32_t));
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulearr = alloca (SMALL_STR_ਮਾਪ + 1);

  ਕਰੋ
    {
      int32_t tmp = findidx (l_ਅੰਕੜੇ.ਸਾਰਣੀ, l_ਅੰਕੜੇ.ਅਸਿੱਧਾ, l_ਅੰਕੜੇ.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  ਜਦੋਂ (*cur != L('\0') && idxmax < SMALL_STR_ਮਾਪ);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  ਜੇ (*cur == L('\0'))
    ਵਾਪਸ do_xfrm_cached (dest, n, &l_ਅੰਕੜੇ, idxmax, idxarr, rulearr);
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ do_xfrm (usrc, dest, n, &l_ਅੰਕੜੇ);
}
libc_hidden_def (STRXFRM)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
weak_alias (__strxfrm_l, strxfrm_l)
#ਜੇ_ਅੰਤ
