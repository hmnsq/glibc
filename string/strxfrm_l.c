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

#اگر_تعریف_نشده STRING_TYPE
# define STRING_TYPE حرف
# define USTRING_TYPE بیعلامت حرف
# define STRXFRM __strxfrm_l
# define STRLEN طول_رشته
# define STPNCPY __stpncpy
# define وزن_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#پایان_اگر

#تعریف_کن CONCAT(a,b) CONCAT1(a,b)
#تعریف_کن CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#تعریف_کن SMALL_STR_اندازه 4095

#ضمن "../locale/localeinfo.h"
#ضمن وزن_H

/* Group locale data for shorter parameter lists.  */
تعريفنوع بنية
{
  uint32_t nrules;
  بیعلامت حرف *rulesets;
  USTRING_TYPE *weights;
  int32_t *جدول;
  USTRING_TYPE *extra;
  int32_t *غیرمستقیم;
} locale_داده_t;

#اگر_تعریف_نشده WIDE_CHAR_نسخه

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
      صحيح گام;

      لكل (گام = 2; گام < 6; ++گام)
	إذا ((val & (~(uint32_t)0 << (5 * گام + 1))) == 0)
	  اكسر;
      retval = گام;

      *buf = (بیعلامت حرف) (~0xff >> گام);
      --گام;
      افعل
	{
	  buf[گام] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      طالما (--گام > 0);
      *buf |= val;
    }

  أرجع retval;
}
#پایان_اگر

/* Find next weight and rule index.  Inlined since called for every char.  */
ساكن __always_inline size_t
پیدا_کن_idx (ثابت USTRING_TYPE **us, int32_t *وزن_idx,
	  بیعلامت حرف *قاعده_idx, ثابت locale_داده_t *l_داده, ثابت صحيح pass)
{
  int32_t tmp = findidx (l_داده->جدول, l_داده->غیرمستقیم, l_داده->extra, us,
			 -1);
  *قاعده_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_داده->weights[idx++];

  /* Skip over indices of previous levels.  */
  لكل (صحيح i = 0; i < pass; i++)
    {
      idx += len;
      len = l_داده->weights[idx++];
    }

  *وزن_idx = idx;
  أرجع len;
}

ساكن صحيح
پیدا_کن_position (ثابت USTRING_TYPE *us, ثابت locale_داده_t *l_داده,
	       ثابت صحيح pass)
{
  int32_t وزن_idx;
  بیعلامت حرف قاعده_idx;
  ثابت USTRING_TYPE *usrc = us;

  پیدا_کن_idx (&usrc, &وزن_idx, &قاعده_idx, l_داده, pass);
  أرجع l_داده->rulesets[قاعده_idx * l_داده->nrules + pass] & مرتب_سازی_position;
}

/* Do the transformation.  */
ساكن size_t
do_xfrm (ثابت USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ثابت locale_داده_t *l_داده)
{
  int32_t وزن_idx;
  بیعلامت حرف قاعده_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t آخرین_needed;

  /* Now the passes over the weights.  */
  لكل (pass = 0; pass < l_داده->nrules; ++pass)
    {
      size_t backw_len = 0;
      آخرین_needed = needed;
      ثابت USTRING_TYPE *cur = usrc;
      ثابت USTRING_TYPE *backw_شروع = عدم;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      صحيح position = پیدا_کن_position (cur, l_داده, pass);

      إذا (position == 0)
	{
	  طالما (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = پیدا_کن_idx (&cur, &وزن_idx, &قاعده_idx, l_داده,
				     pass);
	      صحيح قاعده = l_داده->rulesets[قاعده_idx * l_داده->nrules + pass];

	      إذا ((قاعده & مرتب_سازی_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  إذا (backw_شروع != عدم)
		    {
		      لكل (size_t i = backw_len; i > 0; )
			{
			  int32_t وزن_idx;
			  بیعلامت حرف قاعده_idx;
			  size_t len = پیدا_کن_idx (&backw_شروع, &وزن_idx,
						 &قاعده_idx, l_داده, pass);
			  إذا (needed + i < n)
			    لكل (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_داده->weights[وزن_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_شروع = عدم;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  إذا (needed + len < n)
		    طالما (len-- > 0)
		      dest[needed++] = l_داده->weights[وزن_idx++];
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
		  size_t len = پیدا_کن_idx (&backw_شروع, &وزن_idx, &قاعده_idx,
					 l_داده, pass);
		  إذا (needed + i < n)
		    لكل (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_داده->weights[وزن_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      وإلا
	{
	  صحيح val = 1;
#اگر_تعریف_نشده WIDE_CHAR_نسخه
	  حرف buf[7];
	  size_t buflen;
#پایان_اگر
	  size_t i;

	  طالما (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = پیدا_کن_idx (&cur, &وزن_idx, &قاعده_idx, l_داده,
				     pass);
	      صحيح قاعده = l_داده->rulesets[قاعده_idx * l_داده->nrules + pass];

	      إذا ((قاعده & مرتب_سازی_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  إذا (backw_شروع != عدم)
		    {
		      لكل (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t وزن_idx;
			  بیعلامت حرف قاعده_idx;
			  ثابت USTRING_TYPE *backw_cur = backw_شروع;

			  /* To prevent a warning init the used vars.  */
			  len = پیدا_کن_idx (&backw_cur, &وزن_idx,
					  &قاعده_idx, l_داده, pass);

			  لكل (i = 1; i < p; i++)
			    len = پیدا_کن_idx (&backw_cur, &وزن_idx,
					    &قاعده_idx, l_داده, pass);

			  إذا (len != 0)
			    {
#اگر_تعریف_شده WIDE_CHAR_نسخه
			      إذا (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  لكل (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_داده->weights[وزن_idx + i];
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
				      l_داده->weights[وزن_idx + i];
				}
			      needed += buflen + len;
#پایان_اگر
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
#اگر_تعریف_شده WIDE_CHAR_نسخه
		      إذا (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_داده->weights[وزن_idx + i];
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
			      l_داده->weights[وزن_idx + i];
			}
		      needed += buflen + len;
#پایان_اگر
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
		  int32_t وزن_idx;
		  بیعلامت حرف قاعده_idx;
		  ثابت USTRING_TYPE *backw_cur = backw_شروع;

		  /* To prevent a warning init the used vars.  */
		  len = پیدا_کن_idx (&backw_cur, &وزن_idx,
				  &قاعده_idx, l_داده, pass);

		  لكل (i = 1; i < p; i++)
		    len = پیدا_کن_idx (&backw_cur, &وزن_idx,
				    &قاعده_idx, l_داده, pass);

		  إذا (len != 0)
		    {
#اگر_تعریف_شده WIDE_CHAR_نسخه
		      إذا (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  لكل (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_داده->weights[وزن_idx + i];
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
			      l_داده->weights[وزن_idx + i];
			}
		      needed += buflen + len;
#پایان_اگر
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
	dest[needed] = pass + 1 < l_داده->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  إذا (needed > 2 && needed == آخرین_needed + 1)
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
do_xfrm_cached (STRING_TYPE *dest, size_t n, ثابت locale_داده_t *l_داده,
		size_t idxmax, int32_t *idxarr, ثابت بیعلامت حرف *rulearr)
{
  uint32_t nrules = l_داده->nrules;
  بیعلامت حرف *rulesets = l_داده->rulesets;
  USTRING_TYPE *weights = l_داده->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t آخرین_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  لكل (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      صحيح قاعده = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      صحيح position = قاعده & مرتب_سازی_position;

      آخرین_needed = needed;
      إذا (position == 0)
	{
	  لكل (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      إذا ((قاعده & مرتب_سازی_forward) != 0)
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

	      قاعده = rulesets[rulearr[idxcnt + 1] * nrules + pass];
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
#اگر_تعریف_نشده WIDE_CHAR_نسخه
	  حرف buf[7];
	  size_t buflen;
#پایان_اگر
	  size_t i;

	  لكل (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      إذا ((قاعده & مرتب_سازی_forward) != 0)
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
#اگر_تعریف_شده WIDE_CHAR_نسخه
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
#پایان_اگر
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
#اگر_تعریف_شده WIDE_CHAR_نسخه
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
#پایان_اگر
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

	      قاعده = rulesets[rulearr[idxcnt + 1] * nrules + pass];
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
#اگر_تعریف_شده WIDE_CHAR_نسخه
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
#پایان_اگر
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
  إذا (needed > 2 && needed == آخرین_needed + 1)
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
  locale_داده_t l_داده;
  بنية __locale_data *current = l->__locales[LC_COLLATE];
  l_داده.nrules = current->مقادیر[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].کلمه;

  /* Handle byte comparison case.  */
  إذا (l_داده.nrules == 0)
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
  l_داده.rulesets = (بیعلامت حرف *)
    current->مقادیر[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_داده.جدول = (int32_t *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_جدول,SUFFIX))].string;
  l_داده.weights = (USTRING_TYPE *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_وزن,SUFFIX))].string;
  l_داده.extra = (USTRING_TYPE *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_داده.غیرمستقیم = (int32_t *)
    current->مقادیر[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_غیرمستقیم,SUFFIX))].string;

  أكد (((uintptr_t) l_داده.جدول) % __alignof__ (l_داده.جدول[0]) == 0);
  أكد (((uintptr_t) l_داده.weights) % __alignof__ (l_داده.weights[0]) == 0);
  أكد (((uintptr_t) l_داده.extra) % __alignof__ (l_داده.extra[0]) == 0);
  أكد (((uintptr_t) l_داده.غیرمستقیم) % __alignof__ (l_داده.غیرمستقیم[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ثابت USTRING_TYPE *usrc = (ثابت USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ثابت USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_اندازه * حجم (int32_t));
  بیعلامت حرف *rulearr = alloca (SMALL_STR_اندازه + 1);

  افعل
    {
      int32_t tmp = findidx (l_داده.جدول, l_داده.غیرمستقیم, l_داده.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  طالما (*cur != L('\0') && idxmax < SMALL_STR_اندازه);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  إذا (*cur == L('\0'))
    أرجع do_xfrm_cached (dest, n, &l_داده, idxmax, idxarr, rulearr);
  وإلا
    أرجع do_xfrm (usrc, dest, n, &l_داده);
}
libc_hidden_def (STRXFRM)

#اگر_تعریف_نشده WIDE_CHAR_نسخه
weak_alias (__strxfrm_l, strxfrm_l)
#پایان_اگر
