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

#شامل <assert.h>
#شامل <langinfo.h>
#شامل <locale.h>
#شامل <stddef.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <sys/param.h>

#اگر_غیر_تعریف_شدہ STRING_TYPE
# define STRING_TYPE حرف
# define USTRING_TYPE غیرعلامتی حرف
# define STRXFRM __strxfrm_l
# define STRLEN لڑی_لمبائی
# define STPNCPY __stpncpy
# define وزن_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#اگر_ختم

#تعریف_کرو CONCAT(a,b) CONCAT1(a,b)
#تعریف_کرو CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#تعریف_کرو SMALL_STR_سائز 4095

#شامل "../locale/localeinfo.h"
#شامل وزن_H

/* Group locale data for shorter parameter lists.  */
قسمتعریف ساخت
{
  uint32_t nrules;
  غیرعلامتی حرف *rulesets;
  USTRING_TYPE *weights;
  int32_t *جدول;
  USTRING_TYPE *extra;
  int32_t *بالواسطہ;
} locale_ڈیٹا_t;

#اگر_غیر_تعریف_شدہ WIDE_CHAR_نسخہ

/* We need UTF-8 encoding of numbers.  */
ساکن صحیح
utf8_encode (حرف *buf, صحیح val)
{
  صحیح retval;

  اگر (val < 0x80)
    {
      *buf++ = (حرف) val;
      retval = 1;
    }
  ورنہ
    {
      صحیح قدم;

      برائے (قدم = 2; قدم < 6; ++قدم)
	اگر ((val & (~(uint32_t)0 << (5 * قدم + 1))) == 0)
	  توڑو;
      retval = قدم;

      *buf = (غیرعلامتی حرف) (~0xff >> قدم);
      --قدم;
      کرو
	{
	  buf[قدم] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      جب (--قدم > 0);
      *buf |= val;
    }

  واپس retval;
}
#اگر_ختم

/* Find next weight and rule index.  Inlined since called for every char.  */
ساکن __always_inline size_t
ڈھونڈو_idx (ثابت USTRING_TYPE **us, int32_t *وزن_idx,
	  غیرعلامتی حرف *قاعدہ_idx, ثابت locale_ڈیٹا_t *l_ڈیٹا, ثابت صحیح pass)
{
  int32_t tmp = findidx (l_ڈیٹا->جدول, l_ڈیٹا->بالواسطہ, l_ڈیٹا->extra, us,
			 -1);
  *قاعدہ_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_ڈیٹا->weights[idx++];

  /* Skip over indices of previous levels.  */
  برائے (صحیح i = 0; i < pass; i++)
    {
      idx += len;
      len = l_ڈیٹا->weights[idx++];
    }

  *وزن_idx = idx;
  واپس len;
}

ساکن صحیح
ڈھونڈو_position (ثابت USTRING_TYPE *us, ثابت locale_ڈیٹا_t *l_ڈیٹا,
	       ثابت صحیح pass)
{
  int32_t وزن_idx;
  غیرعلامتی حرف قاعدہ_idx;
  ثابت USTRING_TYPE *usrc = us;

  ڈھونڈو_idx (&usrc, &وزن_idx, &قاعدہ_idx, l_ڈیٹا, pass);
  واپس l_ڈیٹا->rulesets[قاعدہ_idx * l_ڈیٹا->nrules + pass] & ترتیب_دو_position;
}

/* Do the transformation.  */
ساکن size_t
do_xfrm (ثابت USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 ثابت locale_ڈیٹا_t *l_ڈیٹا)
{
  int32_t وزن_idx;
  غیرعلامتی حرف قاعدہ_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t آخری_needed;

  /* Now the passes over the weights.  */
  برائے (pass = 0; pass < l_ڈیٹا->nrules; ++pass)
    {
      size_t backw_len = 0;
      آخری_needed = needed;
      ثابت USTRING_TYPE *cur = usrc;
      ثابت USTRING_TYPE *backw_آغاز = تہی;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      صحیح position = ڈھونڈو_position (cur, l_ڈیٹا, pass);

      اگر (position == 0)
	{
	  جب (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = ڈھونڈو_idx (&cur, &وزن_idx, &قاعدہ_idx, l_ڈیٹا,
				     pass);
	      صحیح قاعدہ = l_ڈیٹا->rulesets[قاعدہ_idx * l_ڈیٹا->nrules + pass];

	      اگر ((قاعدہ & ترتیب_دو_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  اگر (backw_آغاز != تہی)
		    {
		      برائے (size_t i = backw_len; i > 0; )
			{
			  int32_t وزن_idx;
			  غیرعلامتی حرف قاعدہ_idx;
			  size_t len = ڈھونڈو_idx (&backw_آغاز, &وزن_idx,
						 &قاعدہ_idx, l_ڈیٹا, pass);
			  اگر (needed + i < n)
			    برائے (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_ڈیٹا->weights[وزن_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_آغاز = تہی;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  اگر (needed + len < n)
		    جب (len-- > 0)
		      dest[needed++] = l_ڈیٹا->weights[وزن_idx++];
		  ورنہ
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      ورنہ
		{
		  /* Remember start of the backward sequence & track length.  */
		  اگر (backw_آغاز == تہی)
		    backw_آغاز = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  اگر (backw_آغاز != تہی)
	    {
	      برائے (size_t i = backw_len; i > 0; )
		{
		  size_t len = ڈھونڈو_idx (&backw_آغاز, &وزن_idx, &قاعدہ_idx,
					 l_ڈیٹا, pass);
		  اگر (needed + i < n)
		    برائے (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_ڈیٹا->weights[وزن_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      ورنہ
	{
	  صحیح val = 1;
#اگر_غیر_تعریف_شدہ WIDE_CHAR_نسخہ
	  حرف buf[7];
	  size_t buflen;
#اگر_ختم
	  size_t i;

	  جب (*cur != L('\0'))
	    {
	      ثابت USTRING_TYPE *pos = cur;
	      size_t len = ڈھونڈو_idx (&cur, &وزن_idx, &قاعدہ_idx, l_ڈیٹا,
				     pass);
	      صحیح قاعدہ = l_ڈیٹا->rulesets[قاعدہ_idx * l_ڈیٹا->nrules + pass];

	      اگر ((قاعدہ & ترتیب_دو_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  اگر (backw_آغاز != تہی)
		    {
		      برائے (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t وزن_idx;
			  غیرعلامتی حرف قاعدہ_idx;
			  ثابت USTRING_TYPE *backw_cur = backw_آغاز;

			  /* To prevent a warning init the used vars.  */
			  len = ڈھونڈو_idx (&backw_cur, &وزن_idx,
					  &قاعدہ_idx, l_ڈیٹا, pass);

			  برائے (i = 1; i < p; i++)
			    len = ڈھونڈو_idx (&backw_cur, &وزن_idx,
					    &قاعدہ_idx, l_ڈیٹا, pass);

			  اگر (len != 0)
			    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
			      اگر (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  برائے (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_ڈیٹا->weights[وزن_idx + i];
				}
			      needed += 1 + len;
#ورنہ
			      buflen = utf8_encode (buf, val);
			      اگر (needed + buflen + len < n)
				{
				  برائے (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  برائے (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_ڈیٹا->weights[وزن_idx + i];
				}
			      needed += buflen + len;
#اگر_ختم
			      val = 1;
			    }
			  ورنہ
			    ++val;
			}

		      backw_آغاز = تہی;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  اگر (len != 0)
		    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برائے (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ڈیٹا->weights[وزن_idx + i];
			}
		      needed += 1 + len;
#ورنہ
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برائے (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برائے (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ڈیٹا->weights[وزن_idx + i];
			}
		      needed += buflen + len;
#اگر_ختم
		      val = 1;
		    }
		  ورنہ
		    ++val;
		}
	      ورنہ
		{
		  /* Remember start of the backward sequence & track length.  */
		  اگر (backw_آغاز == تہی)
		    backw_آغاز = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  اگر (backw_آغاز != تہی)
	    {
	      برائے (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t وزن_idx;
		  غیرعلامتی حرف قاعدہ_idx;
		  ثابت USTRING_TYPE *backw_cur = backw_آغاز;

		  /* To prevent a warning init the used vars.  */
		  len = ڈھونڈو_idx (&backw_cur, &وزن_idx,
				  &قاعدہ_idx, l_ڈیٹا, pass);

		  برائے (i = 1; i < p; i++)
		    len = ڈھونڈو_idx (&backw_cur, &وزن_idx,
				    &قاعدہ_idx, l_ڈیٹا, pass);

		  اگر (len != 0)
		    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برائے (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_ڈیٹا->weights[وزن_idx + i];
			}
		      needed += 1 + len;
#ورنہ
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برائے (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برائے (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_ڈیٹا->weights[وزن_idx + i];
			}
		      needed += buflen + len;
#اگر_ختم
		      val = 1;
		    }
		  ورنہ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      اگر (needed < n)
	dest[needed] = pass + 1 < l_ڈیٹا->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  اگر (needed > 2 && needed == آخری_needed + 1)
    {
      /* Remove the \1 byte.  */
      اگر (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  واپس needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
ساکن size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, ثابت locale_ڈیٹا_t *l_ڈیٹا,
		size_t idxmax, int32_t *idxarr, ثابت غیرعلامتی حرف *rulearr)
{
  uint32_t nrules = l_ڈیٹا->nrules;
  غیرعلامتی حرف *rulesets = l_ڈیٹا->rulesets;
  USTRING_TYPE *weights = l_ڈیٹا->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t آخری_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  برائے (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      صحیح قاعدہ = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      صحیح position = قاعدہ & ترتیب_دو_position;

      آخری_needed = needed;
      اگر (position == 0)
	{
	  برائے (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      اگر ((قاعدہ & ترتیب_دو_forward) != 0)
		{
		  size_t len;

		  اگر (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      برائے (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  اگر (needed + len < n)
			    جب (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  ورنہ
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
		  اگر (needed + len < n)
		    جب (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  ورنہ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      ورنہ
		{
		  /* Remember where the backwards series started.  */
		  اگر (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      قاعدہ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  اگر (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      جب (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  اگر (needed + len < n)
		    جب (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  ورنہ
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      ورنہ
	{
	  صحیح val = 1;
#اگر_غیر_تعریف_شدہ WIDE_CHAR_نسخہ
	  حرف buf[7];
	  size_t buflen;
#اگر_ختم
	  size_t i;

	  برائے (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      اگر ((قاعدہ & ترتیب_دو_forward) != 0)
		{
		  size_t len;

		  اگر (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      برائے (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  اگر (len != 0)
			    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
			      اگر (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  برائے (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#ورنہ
			      buflen = utf8_encode (buf, val);
			      اگر (needed + buflen + len < n)
				{
				  برائے (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  برائے (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#اگر_ختم
			      idxarr[backw] += len;
			      val = 1;
			    }
			  ورنہ
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  اگر (len != 0)
		    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
		      اگر (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  برائے (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#ورنہ
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برائے (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برائے (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#اگر_ختم
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  ورنہ
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      ورنہ
		{
		  /* Remember where the backwards series started.  */
		  اگر (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      قاعدہ = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  اگر (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      جب (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  اگر (len != 0)
		    {
#اگر_تعریف_شدہ WIDE_CHAR_نسخہ
		      اگر (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  برائے (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#ورنہ
		      buflen = utf8_encode (buf, val);
		      اگر (needed + buflen + len < n)
			{
			  برائے (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  برائے (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#اگر_ختم
		      idxarr[backw] += len;
		      val = 1;
		    }
		  ورنہ
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      اگر (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  اگر (needed > 2 && needed == آخری_needed + 1)
    {
      /* Remove the \1 byte.  */
      اگر (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  واپس needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, ثابت STRING_TYPE *src, size_t n, locale_t l)
{
  locale_ڈیٹا_t l_ڈیٹا;
  ساخت __locale_data *current = l->__locales[LC_COLLATE];
  l_ڈیٹا.nrules = current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].لفظ;

  /* Handle byte comparison case.  */
  اگر (l_ڈیٹا.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      اگر (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      واپس srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  اگر (*src == L('\0'))
    {
      اگر (n != 0)
	*dest = L('\0');
      واپس 0;
    }

  /* Get the locale data.  */
  l_ڈیٹا.rulesets = (غیرعلامتی حرف *)
    current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_ڈیٹا.جدول = (int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_جدول,SUFFIX))].string;
  l_ڈیٹا.weights = (USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_وزن,SUFFIX))].string;
  l_ڈیٹا.extra = (USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_ڈیٹا.بالواسطہ = (int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_بالواسطہ,SUFFIX))].string;

  أكد (((uintptr_t) l_ڈیٹا.جدول) % __alignof__ (l_ڈیٹا.جدول[0]) == 0);
  أكد (((uintptr_t) l_ڈیٹا.weights) % __alignof__ (l_ڈیٹا.weights[0]) == 0);
  أكد (((uintptr_t) l_ڈیٹا.extra) % __alignof__ (l_ڈیٹا.extra[0]) == 0);
  أكد (((uintptr_t) l_ڈیٹا.بالواسطہ) % __alignof__ (l_ڈیٹا.بالواسطہ[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  ثابت USTRING_TYPE *usrc = (ثابت USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  ثابت USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_سائز * حجم (int32_t));
  غیرعلامتی حرف *rulearr = alloca (SMALL_STR_سائز + 1);

  کرو
    {
      int32_t tmp = findidx (l_ڈیٹا.جدول, l_ڈیٹا.بالواسطہ, l_ڈیٹا.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  جب (*cur != L('\0') && idxmax < SMALL_STR_سائز);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  اگر (*cur == L('\0'))
    واپس do_xfrm_cached (dest, n, &l_ڈیٹا, idxmax, idxarr, rulearr);
  ورنہ
    واپس do_xfrm (usrc, dest, n, &l_ڈیٹا);
}
libc_hidden_def (STRXFRM)

#اگر_غیر_تعریف_شدہ WIDE_CHAR_نسخہ
weak_alias (__strxfrm_l, strxfrm_l)
#اگر_ختم
