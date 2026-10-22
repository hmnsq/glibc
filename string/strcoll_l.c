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
#شامل <string.h>
#شامل <sys/param.h>
#شامل <libc-diag.h>

#اگر_غیر_تعریف_شدہ STRING_TYPE
# define STRING_TYPE حرف
# define USTRING_TYPE غیرعلامتی حرف
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define وزن_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#اگر_ختم

#تعریف_کرو CONCAT(a,b) CONCAT1(a,b)
#تعریف_کرو CONCAT1(a,b) a##b

#شامل "../locale/localeinfo.h"
#شامل وزن_H

/* Track status while looking for sequences in a string.  */
قسمتعریف ساخت
{
  صحیح len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  ثابت USTRING_TYPE *us;	/* The string.  */
  غیرعلامتی حرف قاعدہ;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  ثابت USTRING_TYPE *عقب_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
ساکن __always_inline خالی
get_اگلا_seq (coll_seq *seq, صحیح nrules, ثابت غیرعلامتی حرف *rulesets,
	      ثابت USTRING_TYPE *weights, ثابت int32_t *جدول,
	      ثابت USTRING_TYPE *extra, ثابت int32_t *بالواسطہ,
	      صحیح pass)
{
  size_t val = seq->val = 0;
  صحیح len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  ثابت USTRING_TYPE *us = seq->us;

  جب (len == 0)
    {
      ++val;
      اگر (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  اگر (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      اگر (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      ورنہ
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  توڑو;
	        }
	    }
	  ورنہ
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->عقب_us;
	      جب (i < backw)
		{
		  int32_t tmp = findidx (جدول, بالواسطہ, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      ورنہ
	{
	  backw_stop = idxmax;
	  int32_t پچھلا_idx = idx;

	  جب (*us != L('\0'))
	    {
	      int32_t tmp = findidx (جدول, بالواسطہ, extra, &us, -1);
	      غیرعلامتی حرف قاعدہ = tmp >> 24;
	      پچھلا_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      اگر (__glibc_unlikely (idxcnt == 0))
	        seq->قاعدہ = قاعدہ;

	      اگر ((rulesets[قاعدہ * nrules + pass]
		   & ترتیب_دو_backward) == 0)
		/* No more backward characters to push.  */
		توڑو;
	      ++idxcnt;
	    }

	  اگر (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      اگر (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		توڑو;

	      backw_stop = ~0ul;
	    }
	  ورنہ
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->عقب_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      اگر (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = پچھلا_idx;
		}
	      اگر (backw > backw_stop)
		backw--;
	    }
	}

      /* With GCC 5.3 when compiling with -Os the compiler complains
	 that idx, taken from seq->idx (seq1 or seq2 from STRCOLL) may
	 be used uninitialized.  In general this can't possibly be true
	 since seq1.idx and seq2.idx are initialized to zero in the
	 outer function.  Only one case where seq->idx is restored from
	 seq->save_idx might result in an uninitialized idx value, but
	 it is guarded by a sequence of checks against backw_stop which
	 ensures that seq->save_idx was saved to first and contains a
	 valid value.  */
      DIAG_ڈالو_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_نکالو_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      برائے (صحیح i = 0; i < pass; i++)
	{
	  idx += len;
	  len = weights[idx];
	  idx++;
	}
    }

  /* Update the structure.  */
  seq->val = val;
  seq->len = len;
  seq->backw_stop = backw_stop;
  seq->backw = backw;
  seq->idxcnt = idxcnt;
  seq->idxmax = idxmax;
  seq->us = us;
  seq->idx = idx;
}

/* Compare two sequences.  */
ساکن __always_inline صحیح
do_compare (coll_seq *seq1, coll_seq *seq2, صحیح position,
	    ثابت USTRING_TYPE *weights)
{
  صحیح seq1len = seq1->len;
  صحیح seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  صحیح idx1 = seq1->idx;
  صحیح idx2 = seq2->idx;
  صحیح نتیجہ = 0;

  /* Test for position if necessary.  */
  اگر (position && val1 != val2)
    {
      نتیجہ = val1 > val2 ? 1 : -1;
      جاؤ برآمد;
    }

  /* Compare the two sequences.  */
  کرو
    {
      اگر (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  نتیجہ = weights[idx1] - weights[idx2];
	  جاؤ برآمد;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  جب (seq1len > 0 && seq2len > 0);

  اگر (position && seq1len != seq2len)
    نتیجہ = seq1len - seq2len;

برآمد:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  واپس نتیجہ;
}

صحیح
STRCOLL (ثابت STRING_TYPE *s1, ثابت STRING_TYPE *s2, locale_t l)
{
  ساخت __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].لفظ;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  ثابت غیرعلامتی حرف *rulesets;
  ثابت int32_t *جدول;
  ثابت USTRING_TYPE *weights;
  ثابت USTRING_TYPE *extra;
  ثابت int32_t *بالواسطہ;

  اگر (nrules == 0)
    واپس STRCMP (s1, s2);

  /* Catch empty strings.  */
  اگر (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    واپس (*s1 != '\0') - (*s2 != '\0');

  rulesets = (ثابت غیرعلامتی حرف *)
    current->اقدار[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  جدول = (ثابت int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_جدول,SUFFIX))].string;
  weights = (ثابت USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_وزن,SUFFIX))].string;
  extra = (ثابت USTRING_TYPE *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  بالواسطہ = (ثابت int32_t *)
    current->اقدار[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_بالواسطہ,SUFFIX))].string;

  أكد (((uintptr_t) جدول) % __alignof__ (جدول[0]) == 0);
  أكد (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  أكد (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  أكد (((uintptr_t) بالواسطہ) % __alignof__ (بالواسطہ[0]) == 0);

  صحیح نتیجہ = 0, قاعدہ = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_ڈالو_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_نکالو_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.قاعدہ = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  برائے (صحیح pass = 0; pass < nrules; ++pass)
    {
      seq1.idxcnt = 0;
      seq1.idx = 0;
      seq2.idx = 0;
      seq1.backw_stop = ~0ul;
      seq1.backw = ~0ul;
      seq2.idxcnt = 0;
      seq2.backw_stop = ~0ul;
      seq2.backw = ~0ul;

      /* We need the elements of the strings as unsigned values since they
	 are used as indices.  */
      seq1.us = (ثابت USTRING_TYPE *) s1;
      seq2.us = (ثابت USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      صحیح position = rulesets[قاعدہ * nrules + pass] & ترتیب_دو_position;

      جب (1)
	{
	  get_اگلا_seq (&seq1, nrules, rulesets, weights, جدول,
				    extra, بالواسطہ, pass);
	  get_اگلا_seq (&seq2, nrules, rulesets, weights, جدول,
				    extra, بالواسطہ, pass);
	  /* See whether any or both strings are empty.  */
	  اگر (seq1.len == 0 || seq2.len == 0)
	    {
	      اگر (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  اگر (pass == 0 && STRCMP (s1, s2) == 0)
		    واپس نتیجہ;
		  ورنہ
		    توڑو;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      واپس seq1.len == 0 ? -1 : 1;
	    }

	  نتیجہ = do_compare (&seq1, &seq2, position, weights);
	  اگر (نتیجہ != 0)
	    واپس نتیجہ;
	}

      قاعدہ = seq1.قاعدہ;
    }

  واپس نتیجہ;
}
libc_hidden_def (STRCOLL)

#اگر_غیر_تعریف_شدہ WIDE_CHAR_نسخہ
weak_alias (__strcoll_l, strcoll_l)
#اگر_ختم
