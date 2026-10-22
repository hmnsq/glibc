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

#ضمن <assert.h>
#ضمن <langinfo.h>
#ضمن <locale.h>
#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <sys/param.h>

#جے_بنا_تعریف STRING_TYPE
# define STRING_TYPE حرف
# define USTRING_TYPE بنانشانی حرف
# define STRXFRM __strxfrm_l
# define STRLEN لڑی_لمبائی
# define STPNCPY __stpncpy
# define بھار_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#جے_انت

#تعریف_کرو CONCAT(a,b) CONCAT1(a,b)
#تعریف_کرو CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#تعریف_کرو SMALL_STR_ناپ 4095

#ضمن "../locale/localeinfo.h"
#ضمن بھار_H

/* Group locale data for shorter parameter lists.  */
تعريفنوع بنية
{
  uint32_t nrules;
  بنانشانی حرف *rulesets;
  USTRING_TYPE *weights;
  int32_t *جدول;
  USTRING_TYPE *extra;
  int32_t *اسدھا;
} locale_انکڑے_t;

#جے_بنا_تعریف WIDE_CHAR_نسخہ

/* We need UTF-8 encoding of numbers.  */
ساكن صحيح
utf8_encode (حرف *buf, صحيح val)
{
  صحيح retval;

  إذا (val < 0x80)
    {
      *buf++ = (حرف) val;
      retval = 1;
    }
  وإلا
    {
      صحيح قدم;

      لكل (قدم = 2; قدم < 6; ++قدم)
	إذا ((val & (~(uint32_t)0 << (5 * قدم + 1))) == 0)
	  اكسر;
      retval = قدم;

      *buf = (بنانشانی حرف) (~0xff >> قدم);
      --قدم;
      افعل
	{
	  buf[قدم] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      طالما (--قدم > 0);
      *buf |= val;
    }

  أرجع retval;
}
#جے_انت

/* Find next weight and rule index.  Inlined since called for every char.  */
ساكن __always_inline size_t
لبھو_idx (ثابت USTRING_TYPE **us, int32_t *بھار_idx,
	  بنانشانی حرف *قاعدہ_idx, ثابت locale_انکڑے_t *l_انکڑے, ثابت صحيح pass)
{
  int32_t tmp = findidx (l_انکڑے->جدول, l_انکڑے->اسدھا, l_انکڑے->extra, us,
			 -1);
  *قاعدہ_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_انکڑے->weights[idx++];

  /* Skip over indices of previous levels.  */
  لكل (صحيح i = 0; i < pass; i++)
    {
      idx += len;
      len = l_انکڑے->weights[idx++];
    }

  *بھار_idx = idx;
  أرجع len;
}

ساكن صحيح
لبھو_position (ثابت USTRING_TYPE *us, ثابت locale_انکڑے_t *l_انکڑے,
	       ثابت صحيح pass)
{
  int32_t بھار_idx;
  بنانشانی حرف قاعدہ_idx;
  ثابت USTRING_TYPE *usrc = us;

  لبھو_idx (&usrc, &بھار_idx, &قاعدہ_idx, l_انکڑے, pass);
  أرجع l_انکڑے->rulesets[قاعدہ_idx * l_انکڑے->nrules + pass] & ترتیب_دیو_position;
}

/* Do the transformation.  */
ساكن size_t
do_xfrm (ثابت USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ثابت locale_انکڑے_t *l_انکڑے)
{
  int32_t بھار_idx;
  بنانشانی حرف قاعدہ_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t آخری_needed;

  /* Now the passes over the weights.  */
  لكل (pass = 0; pass < l_انکڑے->nrules; ++pass)
    {
      size_t backw_len = 0;
      آخری_needed = needed;
      ثابت USTRING_TYPE *cur = usrc;
      ثابت USTRING_TYPE *backw_شروع = عدم;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      صحيح position = لبھو_position (cur, l_انکڑے, pass);

      إذا (position == 0)
	{
	  طالما (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = لبھو_idx (&cur, &بھار_idx, &قاعدہ_idx, l_انکڑے,
				     pass);
	      صحيح قاعدہ = l_انکڑے->rulesets[قاعدہ_idx * l_انکڑے->nrules + pass];

	      إذا ((قاعدہ & ترتیب_دیو_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  إذا (backw_شروع != عدم)
		    {
		      لكل (size_t i = backw_len; i > 0; )
			{
			  int32_t بھار_idx;
			  بنانشانی حرف قاعدہ_idx;
			  size_t len = لبھو_idx (&backw_شروع, &بھار_idx,
						 &قاعدہ_idx, l_انکڑے, pass);
			  إذا (needed + i < n)
			    لكل (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_انکڑے->weights[بھار_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_شروع = عدم;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  إذا (needed + len < n)
		    طالما (len-- > 0)
		      dest[needed++] = l_انکڑے->weights[بھار_idx++];
		  وإلا
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      وإلا
		{
		  /* Remember start of the backward sequence & track length.  */
		  إذا (backw_شروع == عدم)
		    backw_شروع = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  إذا (backw_شروع != عدم)
	    {
	      لكل (size_t i = backw_len; i > 0; )
		{
		  size_t len = لبھو_idx (&backw_شروع, &بھار_idx, &قاعدہ_idx,
					 l_انکڑے, pass);
		  إذا (needed + i < n)
		    لكل (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_انکڑے->weights[بھار_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      وإلا
	{
	  صحيح val = 1;
#جے_بنا_تعریف WIDE_CHAR_نسخہ
	  حرف buf[7];
	  size_t buflen;
#جے_انت
	  size_t i;

	  طالما (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = لبھو_idx (&cur, &بھار_idx, &قاعدہ_idx, l_انکڑے,
				     pass);
	      صحيح قاعدہ = l_انکڑے->rulesets[قاعدہ_idx * l_انکڑے->nrules + pass];

	      إذا ((قاعدہ & ترتیب_دیو_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  إذا (backw_شروع != عدم)
		    {
		      لكل (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t بھار_idx;
			  بنانشانی حرف قاعدہ_idx;
			  ثابت USTRING_TYPE *backw_cur = backw_شروع;

			  /* To prevent a warning init the used vars.  */
			  len = لبھو_idx (&backw_cur, &بھار_idx,
					  &قاعدہ_idx, l_انکڑے, pass);

			  لكل (i = 1; i < p; i++)
			    len = لبھو_idx (&backw_cur, &بھار_idx,
					    &قاعدہ_idx, l_انکڑے, pass);

			  إذا (len != 0)
			    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
			      إذا (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  لكل (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_انکڑے->weights[بھار_idx + i];
				}
			      needed += 1 + len;
#وإلا
			      buflen = utf8_encode (buf, val);
			      إذا (needed + buflen + len < n)
				{
				  لكل (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  لكل (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_انکڑے->weights[بھار_idx + i];
				}
			      needed += buflen + len;
#جے_انت
			      val = 1;
			    }
			  وإلا
			    ++val;
			}

		      backw_شروع = عدم;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  إذا (len != 0)
		    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
		      إذا (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_انکڑے->weights[بھار_idx + i];
			}
		      needed += 1 + len;
#وإلا
		      buflen = utf8_encode (buf, val);
		      إذا (needed + buflen + len < n)
			{
			  لكل (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  لكل (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_انکڑے->weights[بھار_idx + i];
			}
		      needed += buflen + len;
#جے_انت
		      val = 1;
		    }
		  وإلا
		    ++val;
		}
	      وإلا
		{
		  /* Remember start of the backward sequence & track length.  */
		  إذا (backw_شروع == عدم)
		    backw_شروع = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  إذا (backw_شروع != عدم)
	    {
	      لكل (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t بھار_idx;
		  بنانشانی حرف قاعدہ_idx;
		  ثابت USTRING_TYPE *backw_cur = backw_شروع;

		  /* To prevent a warning init the used vars.  */
		  len = لبھو_idx (&backw_cur, &بھار_idx,
				  &قاعدہ_idx, l_انکڑے, pass);

		  لكل (i = 1; i < p; i++)
		    len = لبھو_idx (&backw_cur, &بھار_idx,
				    &قاعدہ_idx, l_انکڑے, pass);

		  إذا (len != 0)
		    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
		      إذا (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_انکڑے->weights[بھار_idx + i];
			}
		      needed += 1 + len;
#وإلا
		      buflen = utf8_encode (buf, val);
		      إذا (needed + buflen + len < n)
			{
			  لكل (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  لكل (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_انکڑے->weights[بھار_idx + i];
			}
		      needed += buflen + len;
#جے_انت
		      val = 1;
		    }
		  وإلا
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      إذا (needed < n)
	dest[needed] = pass + 1 < l_انکڑے->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  إذا (needed > 2 && needed == آخری_needed + 1)
    {
      /* Remove the \1 byte.  */
      إذا (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  أرجع needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ساكن size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ثابت locale_انکڑے_t *l_انکڑے,
		size_t idxmax, int32_t *idxarr, ثابت بنانشانی حرف *rulearr)
{
  uint32_t nrules = l_انکڑے->nrules;
  بنانشانی حرف *rulesets = l_انکڑے->rulesets;
  USTRING_TYPE *weights = l_انکڑے->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t آخری_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  لكل (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      صحيح قاعدہ = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      صحيح position = قاعدہ & ترتیب_دیو_position;

      آخری_needed = needed;
      إذا (position == 0)
	{
	  لكل (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      إذا ((قاعدہ & ترتیب_دیو_forward) != 0)
		{
		  size_t len;

		  إذا (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      لكل (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  إذا (needed + len < n)
			    طالما (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  وإلا
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
		  إذا (needed + len < n)
		    طالما (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  وإلا
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      وإلا
		{
		  /* Remember where the backwards series started.  */
		  إذا (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      قاعدہ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  إذا (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      طالما (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  إذا (needed + len < n)
		    طالما (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  وإلا
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      وإلا
	{
	  صحيح val = 1;
#جے_بنا_تعریف WIDE_CHAR_نسخہ
	  حرف buf[7];
	  size_t buflen;
#جے_انت
	  size_t i;

	  لكل (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      إذا ((قاعدہ & ترتیب_دیو_forward) != 0)
		{
		  size_t len;

		  إذا (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      لكل (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  إذا (len != 0)
			    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
			      إذا (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  لكل (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#وإلا
			      buflen = utf8_encode (buf, val);
			      إذا (needed + buflen + len < n)
				{
				  لكل (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  لكل (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#جے_انت
			      idxarr[backw] += len;
			      val = 1;
			    }
			  وإلا
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  إذا (len != 0)
		    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
		      إذا (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#وإلا
		      buflen = utf8_encode (buf, val);
		      إذا (needed + buflen + len < n)
			{
			  لكل (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  لكل (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#جے_انت
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  وإلا
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      وإلا
		{
		  /* Remember where the backwards series started.  */
		  إذا (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      قاعدہ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  إذا (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      طالما (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  إذا (len != 0)
		    {
#جے_تعریف_شدہ WIDE_CHAR_نسخہ
		      إذا (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#وإلا
		      buflen = utf8_encode (buf, val);
		      إذا (needed + buflen + len < n)
			{
			  لكل (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  لكل (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#جے_انت
		      idxarr[backw] += len;
		      val = 1;
		    }
		  وإلا
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      إذا (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  إذا (needed > 2 && needed == آخری_needed + 1)
    {
      /* Remove the \1 byte.  */
      إذا (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  أرجع needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ثابت STRING_TYPE *src, size_t n, locale_t l)
{
  locale_انکڑے_t l_انکڑے;
  بنية __locale_data *current = l->__locales[LC_COLLATE];
  l_انکڑے.nrules = current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].لفظ;

  /* Handle byte comparison case.  */
  إذا (l_انکڑے.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      إذا (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      أرجع srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  إذا (*src == L('\0'))
    {
      إذا (n != 0)
	*dest = L('\0');
      أرجع 0;
    }

  /* Get the locale data.  */
  l_انکڑے.rulesets = (بنانشانی حرف *)
    current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_انکڑے.جدول = (int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_جدول,SUFFIX))].string;
  l_انکڑے.weights = (USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_بھار,SUFFIX))].string;
  l_انکڑے.extra = (USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_انکڑے.اسدھا = (int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_اسدھا,SUFFIX))].string;

  أكد (((uintptr_t) l_انکڑے.جدول) % __alignof__ (l_انکڑے.جدول[0]) == 0);
  أكد (((uintptr_t) l_انکڑے.weights) % __alignof__ (l_انکڑے.weights[0]) == 0);
  أكد (((uintptr_t) l_انکڑے.extra) % __alignof__ (l_انکڑے.extra[0]) == 0);
  أكد (((uintptr_t) l_انکڑے.اسدھا) % __alignof__ (l_انکڑے.اسدھا[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ثابت USTRING_TYPE *usrc = (ثابت USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ثابت USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_ناپ * حجم (int32_t));
  بنانشانی حرف *rulearr = alloca (SMALL_STR_ناپ + 1);

  افعل
    {
      int32_t tmp = findidx (l_انکڑے.جدول, l_انکڑے.اسدھا, l_انکڑے.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  طالما (*cur != L('\0') && idxmax < SMALL_STR_ناپ);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  إذا (*cur == L('\0'))
    أرجع do_xfrm_cached (dest, n, &l_انکڑے, idxmax, idxarr, rulearr);
  وإلا
    أرجع do_xfrm (usrc, dest, n, &l_انکڑے);
}
libc_hidden_def (STRXFRM)

#جے_بنا_تعریف WIDE_CHAR_نسخہ
weak_alias (__strxfrm_l, strxfrm_l)
#جے_انت
