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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRING_TYPE
# define STRING_TYPE ಅಕ್ಷರ
# define USTRING_TYPE ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define STRXFRM __strxfrm_l
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define STPNCPY __stpncpy
# define ತೂಕ_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು CONCAT(a,b) CONCAT1(a,b)
#ವ್ಯಾಖ್ಯಾನಿಸು CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#ವ್ಯಾಖ್ಯಾನಿಸು SMALL_STR_ಗಾತ್ರ 4095

#ಅನ್ತರ್ಭಾವ "../locale/localeinfo.h"
#ಅನ್ತರ್ಭಾವ ತೂಕ_H

/* Group locale data for shorter parameter lists.  */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  uint32_t nrules;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulesets;
  USTRING_TYPE *weights;
  int32_t *ಕೋಷ್ಟಕ;
  USTRING_TYPE *extra;
  int32_t *ಪರೋಕ್ಷ;
} locale_ದತ್ತಾಂಶ_t;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE_CHAR_ಆವೃತ್ತಿ

/* We need UTF-8 encoding of numbers.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
utf8_encode (ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ val)
{
  ಪೂರ್ಣಾಂಕ retval;

  ಆದರೆ (val < 0x80)
    {
      *buf++ = (ಅಕ್ಷರ) val;
      retval = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಪೂರ್ಣಾಂಕ ಹೆಜ್ಜೆ;

      ಗಾಗಿ (ಹೆಜ್ಜೆ = 2; ಹೆಜ್ಜೆ < 6; ++ಹೆಜ್ಜೆ)
	ಆದರೆ ((val & (~(uint32_t)0 << (5 * ಹೆಜ್ಜೆ + 1))) == 0)
	  ನಿಲ್ಲಿಸು;
      retval = ಹೆಜ್ಜೆ;

      *buf = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) (~0xff >> ಹೆಜ್ಜೆ);
      --ಹೆಜ್ಜೆ;
      ಮಾಡು
	{
	  buf[ಹೆಜ್ಜೆ] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      ಆಗ (--ಹೆಜ್ಜೆ > 0);
      *buf |= val;
    }

  ಹಿಂತಿರುಗಿ retval;
}
#ಆದರೆ_ಅಂತ್ಯ

/* Find next weight and rule index.  Inlined since called for every char.  */
ಸ್ಥಿರ __always_inline size_t
ಕಂಡುಹಿಡಿ_idx (ಸ್ಥಿರಾಂಕ USTRING_TYPE **us, int32_t *ತೂಕ_idx,
	  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ನಿಯಮ_idx, ಸ್ಥಿರಾಂಕ locale_ದತ್ತಾಂಶ_t *l_ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pass)
{
  int32_t tmp = findidx (l_ದತ್ತಾಂಶ->ಕೋಷ್ಟಕ, l_ದತ್ತಾಂಶ->ಪರೋಕ್ಷ, l_ದತ್ತಾಂಶ->extra, us,
			 -1);
  *ನಿಯಮ_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_ದತ್ತಾಂಶ->weights[idx++];

  /* Skip over indices of previous levels.  */
  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pass; i++)
    {
      idx += len;
      len = l_ದತ್ತಾಂಶ->weights[idx++];
    }

  *ತೂಕ_idx = idx;
  ಹಿಂತಿರುಗಿ len;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
ಕಂಡುಹಿಡಿ_position (ಸ್ಥಿರಾಂಕ USTRING_TYPE *us, ಸ್ಥಿರಾಂಕ locale_ದತ್ತಾಂಶ_t *l_ದತ್ತಾಂಶ,
	       ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pass)
{
  int32_t ತೂಕ_idx;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ_idx;
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *usrc = us;

  ಕಂಡುಹಿಡಿ_idx (&usrc, &ತೂಕ_idx, &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);
  ಹಿಂತಿರುಗಿ l_ದತ್ತಾಂಶ->rulesets[ನಿಯಮ_idx * l_ದತ್ತಾಂಶ->nrules + pass] & ವಿಂಗಡಿಸು_position;
}

/* Do the transformation.  */
ಸ್ಥಿರ size_t
do_xfrm (ಸ್ಥಿರಾಂಕ USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ಸ್ಥಿರಾಂಕ locale_ದತ್ತಾಂಶ_t *l_ದತ್ತಾಂಶ)
{
  int32_t ತೂಕ_idx;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t ಕೊನೆಯ_needed;

  /* Now the passes over the weights.  */
  ಗಾಗಿ (pass = 0; pass < l_ದತ್ತಾಂಶ->nrules; ++pass)
    {
      size_t backw_len = 0;
      ಕೊನೆಯ_needed = needed;
      ಸ್ಥಿರಾಂಕ USTRING_TYPE *cur = usrc;
      ಸ್ಥಿರಾಂಕ USTRING_TYPE *backw_ಆರಂಭ = ಖಾಲಿ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      ಪೂರ್ಣಾಂಕ position = ಕಂಡುಹಿಡಿ_position (cur, l_ದತ್ತಾಂಶ, pass);

      ಆದರೆ (position == 0)
	{
	  ಆಗ (*cur != L('\0'))
	    {
	      ಸ್ಥಿರಾಂಕ USTRING_TYPE *pos = cur;
	      size_t len = ಕಂಡುಹಿಡಿ_idx (&cur, &ತೂಕ_idx, &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ,
				     pass);
	      ಪೂರ್ಣಾಂಕ ನಿಯಮ = l_ದತ್ತಾಂಶ->rulesets[ನಿಯಮ_idx * l_ದತ್ತಾಂಶ->nrules + pass];

	      ಆದರೆ ((ನಿಯಮ & ವಿಂಗಡಿಸು_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ಆದರೆ (backw_ಆರಂಭ != ಖಾಲಿ)
		    {
		      ಗಾಗಿ (size_t i = backw_len; i > 0; )
			{
			  int32_t ತೂಕ_idx;
			  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ_idx;
			  size_t len = ಕಂಡುಹಿಡಿ_idx (&backw_ಆರಂಭ, &ತೂಕ_idx,
						 &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);
			  ಆದರೆ (needed + i < n)
			    ಗಾಗಿ (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_ಆರಂಭ = ಖಾಲಿ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ಆದರೆ (needed + len < n)
		    ಆಗ (len-- > 0)
		      dest[needed++] = l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx++];
		  ಇಲ್ಲದಿದ್ದರೆ
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ಆದರೆ (backw_ಆರಂಭ == ಖಾಲಿ)
		    backw_ಆರಂಭ = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  ಆದರೆ (backw_ಆರಂಭ != ಖಾಲಿ)
	    {
	      ಗಾಗಿ (size_t i = backw_len; i > 0; )
		{
		  size_t len = ಕಂಡುಹಿಡಿ_idx (&backw_ಆರಂಭ, &ತೂಕ_idx, &ನಿಯಮ_idx,
					 l_ದತ್ತಾಂಶ, pass);
		  ಆದರೆ (needed + i < n)
		    ಗಾಗಿ (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಪೂರ್ಣಾಂಕ val = 1;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
	  ಅಕ್ಷರ buf[7];
	  size_t buflen;
#ಆದರೆ_ಅಂತ್ಯ
	  size_t i;

	  ಆಗ (*cur != L('\0'))
	    {
	      ಸ್ಥಿರಾಂಕ USTRING_TYPE *pos = cur;
	      size_t len = ಕಂಡುಹಿಡಿ_idx (&cur, &ತೂಕ_idx, &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ,
				     pass);
	      ಪೂರ್ಣಾಂಕ ನಿಯಮ = l_ದತ್ತಾಂಶ->rulesets[ನಿಯಮ_idx * l_ದತ್ತಾಂಶ->nrules + pass];

	      ಆದರೆ ((ನಿಯಮ & ವಿಂಗಡಿಸು_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ಆದರೆ (backw_ಆರಂಭ != ಖಾಲಿ)
		    {
		      ಗಾಗಿ (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t ತೂಕ_idx;
			  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ_idx;
			  ಸ್ಥಿರಾಂಕ USTRING_TYPE *backw_cur = backw_ಆರಂಭ;

			  /* To prevent a warning init the used vars.  */
			  len = ಕಂಡುಹಿಡಿ_idx (&backw_cur, &ತೂಕ_idx,
					  &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);

			  ಗಾಗಿ (i = 1; i < p; i++)
			    len = ಕಂಡುಹಿಡಿ_idx (&backw_cur, &ತೂಕ_idx,
					    &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);

			  ಆದರೆ (len != 0)
			    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
			      ಆದರೆ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ಗಾಗಿ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
				}
			      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
			      buflen = utf8_encode (buf, val);
			      ಆದರೆ (needed + buflen + len < n)
				{
				  ಗಾಗಿ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ಗಾಗಿ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
				}
			      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
			      val = 1;
			    }
			  ಇಲ್ಲದಿದ್ದರೆ
			    ++val;
			}

		      backw_ಆರಂಭ = ಖಾಲಿ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ಆದರೆ (len != 0)
		    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
		      ಆದರೆ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
			}
		      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
		      buflen = utf8_encode (buf, val);
		      ಆದರೆ (needed + buflen + len < n)
			{
			  ಗಾಗಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
			}
		      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
		      val = 1;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    ++val;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* Remember start of the backward sequence & track length.  */
		  ಆದರೆ (backw_ಆರಂಭ == ಖಾಲಿ)
		    backw_ಆರಂಭ = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  ಆದರೆ (backw_ಆರಂಭ != ಖಾಲಿ)
	    {
	      ಗಾಗಿ (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t ತೂಕ_idx;
		  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ_idx;
		  ಸ್ಥಿರಾಂಕ USTRING_TYPE *backw_cur = backw_ಆರಂಭ;

		  /* To prevent a warning init the used vars.  */
		  len = ಕಂಡುಹಿಡಿ_idx (&backw_cur, &ತೂಕ_idx,
				  &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);

		  ಗಾಗಿ (i = 1; i < p; i++)
		    len = ಕಂಡುಹಿಡಿ_idx (&backw_cur, &ತೂಕ_idx,
				    &ನಿಯಮ_idx, l_ದತ್ತಾಂಶ, pass);

		  ಆದರೆ (len != 0)
		    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
		      ಆದರೆ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
			}
		      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
		      buflen = utf8_encode (buf, val);
		      ಆದರೆ (needed + buflen + len < n)
			{
			  ಗಾಗಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ದತ್ತಾಂಶ->weights[ತೂಕ_idx + i];
			}
		      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
		      val = 1;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ಆದರೆ (needed < n)
	dest[needed] = pass + 1 < l_ದತ್ತಾಂಶ->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ಆದರೆ (needed > 2 && needed == ಕೊನೆಯ_needed + 1)
    {
      /* Remove the \1 byte.  */
      ಆದರೆ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ಹಿಂತಿರುಗಿ needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ಸ್ಥಿರ size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ಸ್ಥಿರಾಂಕ locale_ದತ್ತಾಂಶ_t *l_ದತ್ತಾಂಶ,
		size_t idxmax, int32_t *idxarr, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulearr)
{
  uint32_t nrules = l_ದತ್ತಾಂಶ->nrules;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulesets = l_ದತ್ತಾಂಶ->rulesets;
  USTRING_TYPE *weights = l_ದತ್ತಾಂಶ->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t ಕೊನೆಯ_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  ಗಾಗಿ (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      ಪೂರ್ಣಾಂಕ ನಿಯಮ = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      ಪೂರ್ಣಾಂಕ position = ನಿಯಮ & ವಿಂಗಡಿಸು_position;

      ಕೊನೆಯ_needed = needed;
      ಆದರೆ (position == 0)
	{
	  ಗಾಗಿ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ಆದರೆ ((ನಿಯಮ & ವಿಂಗಡಿಸು_forward) != 0)
		{
		  size_t len;

		  ಆದರೆ (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      ಗಾಗಿ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  ಆದರೆ (needed + len < n)
			    ಆಗ (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  ಇಲ್ಲದಿದ್ದರೆ
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
		  ಆದರೆ (needed + len < n)
		    ಆಗ (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* Remember where the backwards series started.  */
		  ಆದರೆ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      ನಿಯಮ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  ಆದರೆ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      ಆಗ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  ಆದರೆ (needed + len < n)
		    ಆಗ (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಪೂರ್ಣಾಂಕ val = 1;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
	  ಅಕ್ಷರ buf[7];
	  size_t buflen;
#ಆದರೆ_ಅಂತ್ಯ
	  size_t i;

	  ಗಾಗಿ (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ಆದರೆ ((ನಿಯಮ & ವಿಂಗಡಿಸು_forward) != 0)
		{
		  size_t len;

		  ಆದರೆ (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      ಗಾಗಿ (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  ಆದರೆ (len != 0)
			    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
			      ಆದರೆ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  ಗಾಗಿ (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
			      buflen = utf8_encode (buf, val);
			      ಆದರೆ (needed + buflen + len < n)
				{
				  ಗಾಗಿ (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  ಗಾಗಿ (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
			      idxarr[backw] += len;
			      val = 1;
			    }
			  ಇಲ್ಲದಿದ್ದರೆ
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ಆದರೆ (len != 0)
		    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
		      ಆದರೆ (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
		      buflen = utf8_encode (buf, val);
		      ಆದರೆ (needed + buflen + len < n)
			{
			  ಗಾಗಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* Remember where the backwards series started.  */
		  ಆದರೆ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      ನಿಯಮ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  ಆದರೆ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      ಆಗ (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  ಆದರೆ (len != 0)
		    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
		      ಆದರೆ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#ಇಲ್ಲದಿದ್ದರೆ
		      buflen = utf8_encode (buf, val);
		      ಆದರೆ (needed + buflen + len < n)
			{
			  ಗಾಗಿ (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  ಗಾಗಿ (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#ಆದರೆ_ಅಂತ್ಯ
		      idxarr[backw] += len;
		      val = 1;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ಆದರೆ (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ಆದರೆ (needed > 2 && needed == ಕೊನೆಯ_needed + 1)
    {
      /* Remove the \1 byte.  */
      ಆದರೆ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  ಹಿಂತಿರುಗಿ needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ಸ್ಥಿರಾಂಕ STRING_TYPE *src, size_t n, locale_t l)
{
  locale_ದತ್ತಾಂಶ_t l_ದತ್ತಾಂಶ;
  ರಚನೆ __locale_data *current = l->__locales[LC_COLLATE];
  l_ದತ್ತಾಂಶ.nrules = current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].ಶಬ್ದ;

  /* Handle byte comparison case.  */
  ಆದರೆ (l_ದತ್ತಾಂಶ.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      ಆದರೆ (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      ಹಿಂತಿರುಗಿ srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  ಆದರೆ (*src == L('\0'))
    {
      ಆದರೆ (n != 0)
	*dest = L('\0');
      ಹಿಂತಿರುಗಿ 0;
    }

  /* Get the locale data.  */
  l_ದತ್ತಾಂಶ.rulesets = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_ದತ್ತಾಂಶ.ಕೋಷ್ಟಕ = (int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ಕೋಷ್ಟಕ,SUFFIX))].string;
  l_ದತ್ತಾಂಶ.weights = (USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ತೂಕ,SUFFIX))].string;
  l_ದತ್ತಾಂಶ.extra = (USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_ದತ್ತಾಂಶ.ಪರೋಕ್ಷ = (int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ಪರೋಕ್ಷ,SUFFIX))].string;

  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_ದತ್ತಾಂಶ.ಕೋಷ್ಟಕ) % __alignof__ (l_ದತ್ತಾಂಶ.ಕೋಷ್ಟಕ[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_ದತ್ತಾಂಶ.weights) % __alignof__ (l_ದತ್ತಾಂಶ.weights[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_ದತ್ತಾಂಶ.extra) % __alignof__ (l_ದತ್ತಾಂಶ.extra[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) l_ದತ್ತಾಂಶ.ಪರೋಕ್ಷ) % __alignof__ (l_ದತ್ತಾಂಶ.ಪರೋಕ್ಷ[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *usrc = (ಸ್ಥಿರಾಂಕ USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_ಗಾತ್ರ * ಗಾತ್ರ (int32_t));
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulearr = alloca (SMALL_STR_ಗಾತ್ರ + 1);

  ಮಾಡು
    {
      int32_t tmp = findidx (l_ದತ್ತಾಂಶ.ಕೋಷ್ಟಕ, l_ದತ್ತಾಂಶ.ಪರೋಕ್ಷ, l_ದತ್ತಾಂಶ.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  ಆಗ (*cur != L('\0') && idxmax < SMALL_STR_ಗಾತ್ರ);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  ಆದರೆ (*cur == L('\0'))
    ಹಿಂತಿರುಗಿ do_xfrm_cached (dest, n, &l_ದತ್ತಾಂಶ, idxmax, idxarr, rulearr);
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ do_xfrm (usrc, dest, n, &l_ದತ್ತಾಂಶ);
}
libc_hidden_def (STRXFRM)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
weak_alias (__strxfrm_l, strxfrm_l)
#ಆದರೆ_ಅಂತ್ಯ
