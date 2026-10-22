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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRING_TYPE
# define STRING_TYPE ਅੱਖਰ
# define USTRING_TYPE ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define ਭਾਰ_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONCAT(a,b) CONCAT1(a,b)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONCAT1(a,b) a##b

#ਅਨ੍ਤਰ੍ਭਾਵ "../locale/localeinfo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ ਭਾਰ_H

/* Track status while looking for sequences in a string.  */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  ਪੂਰਨ len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  ਅਚਲ USTRING_TYPE *us;	/* The string.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  ਅਚਲ USTRING_TYPE *ਪਿੱਠ_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
ਸਥਿਰ __always_inline ਖਾਲੀ
get_ਅਗਲਾ_seq (coll_seq *seq, ਪੂਰਨ nrules, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulesets,
	      ਅਚਲ USTRING_TYPE *weights, ਅਚਲ int32_t *ਸਾਰਣੀ,
	      ਅਚਲ USTRING_TYPE *extra, ਅਚਲ int32_t *ਅਸਿੱਧਾ,
	      ਪੂਰਨ pass)
{
  size_t val = seq->val = 0;
  ਪੂਰਨ len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  ਅਚਲ USTRING_TYPE *us = seq->us;

  ਜਦੋਂ (len == 0)
    {
      ++val;
      ਜੇ (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  ਜੇ (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      ਜੇ (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  ਰੋਕੋ;
	        }
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->ਪਿੱਠ_us;
	      ਜਦੋਂ (i < backw)
		{
		  int32_t tmp = findidx (ਸਾਰਣੀ, ਅਸਿੱਧਾ, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  backw_stop = idxmax;
	  int32_t prev_idx = idx;

	  ਜਦੋਂ (*us != L('\0'))
	    {
	      int32_t tmp = findidx (ਸਾਰਣੀ, ਅਸਿੱਧਾ, extra, &us, -1);
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਿਯਮ = tmp >> 24;
	      prev_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      ਜੇ (__glibc_unlikely (idxcnt == 0))
	        seq->ਨਿਯਮ = ਨਿਯਮ;

	      ਜੇ ((rulesets[ਨਿਯਮ * nrules + pass]
		   & ਛਾਂਟੋ_backward) == 0)
		/* No more backward characters to push.  */
		ਰੋਕੋ;
	      ++idxcnt;
	    }

	  ਜੇ (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      ਜੇ (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		ਰੋਕੋ;

	      backw_stop = ~0ul;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->ਪਿੱਠ_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      ਜੇ (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = prev_idx;
		}
	      ਜੇ (backw > backw_stop)
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
      DIAG_ਧੱਕੋ_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_ਕੱਢੋ_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      ਲਈ (ਪੂਰਨ i = 0; i < pass; i++)
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
ਸਥਿਰ __always_inline ਪੂਰਨ
do_compare (coll_seq *seq1, coll_seq *seq2, ਪੂਰਨ position,
	    ਅਚਲ USTRING_TYPE *weights)
{
  ਪੂਰਨ seq1len = seq1->len;
  ਪੂਰਨ seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  ਪੂਰਨ idx1 = seq1->idx;
  ਪੂਰਨ idx2 = seq2->idx;
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  /* Test for position if necessary.  */
  ਜੇ (position && val1 != val2)
    {
      ਨਤੀਜਾ = val1 > val2 ? 1 : -1;
      ਜਾਓ ਬਾਹਰਲਾ;
    }

  /* Compare the two sequences.  */
  ਕਰੋ
    {
      ਜੇ (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  ਨਤੀਜਾ = weights[idx1] - weights[idx2];
	  ਜਾਓ ਬਾਹਰਲਾ;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  ਜਦੋਂ (seq1len > 0 && seq2len > 0);

  ਜੇ (position && seq1len != seq2len)
    ਨਤੀਜਾ = seq1len - seq2len;

ਬਾਹਰਲਾ:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  ਵਾਪਸ ਨਤੀਜਾ;
}

ਪੂਰਨ
STRCOLL (ਅਚਲ STRING_TYPE *s1, ਅਚਲ STRING_TYPE *s2, locale_t l)
{
  ਬਣਤਰ __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].ਸ਼ਬਦ;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rulesets;
  ਅਚਲ int32_t *ਸਾਰਣੀ;
  ਅਚਲ USTRING_TYPE *weights;
  ਅਚਲ USTRING_TYPE *extra;
  ਅਚਲ int32_t *ਅਸਿੱਧਾ;

  ਜੇ (nrules == 0)
    ਵਾਪਸ STRCMP (s1, s2);

  /* Catch empty strings.  */
  ਜੇ (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    ਵਾਪਸ (*s1 != '\0') - (*s2 != '\0');

  rulesets = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  ਸਾਰਣੀ = (ਅਚਲ int32_t *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਸਾਰਣੀ,SUFFIX))].string;
  weights = (ਅਚਲ USTRING_TYPE *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਭਾਰ,SUFFIX))].string;
  extra = (ਅਚਲ USTRING_TYPE *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  ਅਸਿੱਧਾ = (ਅਚਲ int32_t *)
    current->ਮੁੱਲਾਂ[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ਅਸਿੱਧਾ,SUFFIX))].string;

  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) ਸਾਰਣੀ) % __alignof__ (ਸਾਰਣੀ[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  ਪ੍ਰਤਿਜ੍ਞਾ (((uintptr_t) ਅਸਿੱਧਾ) % __alignof__ (ਅਸਿੱਧਾ[0]) == 0);

  ਪੂਰਨ ਨਤੀਜਾ = 0, ਨਿਯਮ = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.ਨਿਯਮ = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  ਲਈ (ਪੂਰਨ pass = 0; pass < nrules; ++pass)
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
      seq1.us = (ਅਚਲ USTRING_TYPE *) s1;
      seq2.us = (ਅਚਲ USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      ਪੂਰਨ position = rulesets[ਨਿਯਮ * nrules + pass] & ਛਾਂਟੋ_position;

      ਜਦੋਂ (1)
	{
	  get_ਅਗਲਾ_seq (&seq1, nrules, rulesets, weights, ਸਾਰਣੀ,
				    extra, ਅਸਿੱਧਾ, pass);
	  get_ਅਗਲਾ_seq (&seq2, nrules, rulesets, weights, ਸਾਰਣੀ,
				    extra, ਅਸਿੱਧਾ, pass);
	  /* See whether any or both strings are empty.  */
	  ਜੇ (seq1.len == 0 || seq2.len == 0)
	    {
	      ਜੇ (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  ਜੇ (pass == 0 && STRCMP (s1, s2) == 0)
		    ਵਾਪਸ ਨਤੀਜਾ;
		  ਨਹੀਂਤਾਂ
		    ਰੋਕੋ;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      ਵਾਪਸ seq1.len == 0 ? -1 : 1;
	    }

	  ਨਤੀਜਾ = do_compare (&seq1, &seq2, position, weights);
	  ਜੇ (ਨਤੀਜਾ != 0)
	    ਵਾਪਸ ਨਤੀਜਾ;
	}

      ਨਿਯਮ = seq1.ਨਿਯਮ;
    }

  ਵਾਪਸ ਨਤੀਜਾ;
}
libc_hidden_def (STRCOLL)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE_CHAR_ਸੰਸਕਰਣ
weak_alias (__strcoll_l, strcoll_l)
#ਜੇ_ਅੰਤ
