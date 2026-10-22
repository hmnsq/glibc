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
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRING_TYPE
# define STRING_TYPE ಅಕ್ಷರ
# define USTRING_TYPE ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define ತೂಕ_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು CONCAT(a,b) CONCAT1(a,b)
#ವ್ಯಾಖ್ಯಾನಿಸು CONCAT1(a,b) a##b

#ಅನ್ತರ್ಭಾವ "../locale/localeinfo.h"
#ಅನ್ತರ್ಭಾವ ತೂಕ_H

/* Track status while looking for sequences in a string.  */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  ಪೂರ್ಣಾಂಕ len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *us;	/* The string.  */
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *ಹಿಂಭಾಗ_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
ಸ್ಥಿರ __always_inline ಶೂನ್ಯ
get_ಮುಂದಿನ_seq (coll_seq *seq, ಪೂರ್ಣಾಂಕ nrules, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulesets,
	      ಸ್ಥಿರಾಂಕ USTRING_TYPE *weights, ಸ್ಥಿರಾಂಕ int32_t *ಕೋಷ್ಟಕ,
	      ಸ್ಥಿರಾಂಕ USTRING_TYPE *extra, ಸ್ಥಿರಾಂಕ int32_t *ಪರೋಕ್ಷ,
	      ಪೂರ್ಣಾಂಕ pass)
{
  size_t val = seq->val = 0;
  ಪೂರ್ಣಾಂಕ len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *us = seq->us;

  ಆಗ (len == 0)
    {
      ++val;
      ಆದರೆ (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  ಆದರೆ (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      ಆದರೆ (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  ನಿಲ್ಲಿಸು;
	        }
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->ಹಿಂಭಾಗ_us;
	      ಆಗ (i < backw)
		{
		  int32_t tmp = findidx (ಕೋಷ್ಟಕ, ಪರೋಕ್ಷ, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  backw_stop = idxmax;
	  int32_t prev_idx = idx;

	  ಆಗ (*us != L('\0'))
	    {
	      int32_t tmp = findidx (ಕೋಷ್ಟಕ, ಪರೋಕ್ಷ, extra, &us, -1);
	      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ನಿಯಮ = tmp >> 24;
	      prev_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      ಆದರೆ (__glibc_unlikely (idxcnt == 0))
	        seq->ನಿಯಮ = ನಿಯಮ;

	      ಆದರೆ ((rulesets[ನಿಯಮ * nrules + pass]
		   & ವಿಂಗಡಿಸು_backward) == 0)
		/* No more backward characters to push.  */
		ನಿಲ್ಲಿಸು;
	      ++idxcnt;
	    }

	  ಆದರೆ (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      ಆದರೆ (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		ನಿಲ್ಲಿಸು;

	      backw_stop = ~0ul;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->ಹಿಂಭಾಗ_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      ಆದರೆ (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = prev_idx;
		}
	      ಆದರೆ (backw > backw_stop)
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
      DIAG_ತಳ್ಳು_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_ತೆಗೆ_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pass; i++)
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
ಸ್ಥಿರ __always_inline ಪೂರ್ಣಾಂಕ
do_compare (coll_seq *seq1, coll_seq *seq2, ಪೂರ್ಣಾಂಕ position,
	    ಸ್ಥಿರಾಂಕ USTRING_TYPE *weights)
{
  ಪೂರ್ಣಾಂಕ seq1len = seq1->len;
  ಪೂರ್ಣಾಂಕ seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  ಪೂರ್ಣಾಂಕ idx1 = seq1->idx;
  ಪೂರ್ಣಾಂಕ idx2 = seq2->idx;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  /* Test for position if necessary.  */
  ಆದರೆ (position && val1 != val2)
    {
      ಫಲಿತಾಂಶ = val1 > val2 ? 1 : -1;
      ಹೋಗು ಹೊರಹೋಗು;
    }

  /* Compare the two sequences.  */
  ಮಾಡು
    {
      ಆದರೆ (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  ಫಲಿತಾಂಶ = weights[idx1] - weights[idx2];
	  ಹೋಗು ಹೊರಹೋಗು;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  ಆಗ (seq1len > 0 && seq2len > 0);

  ಆದರೆ (position && seq1len != seq2len)
    ಫಲಿತಾಂಶ = seq1len - seq2len;

ಹೊರಹೋಗು:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಪೂರ್ಣಾಂಕ
STRCOLL (ಸ್ಥಿರಾಂಕ STRING_TYPE *s1, ಸ್ಥಿರಾಂಕ STRING_TYPE *s2, locale_t l)
{
  ರಚನೆ __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].ಶಬ್ದ;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rulesets;
  ಸ್ಥಿರಾಂಕ int32_t *ಕೋಷ್ಟಕ;
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *weights;
  ಸ್ಥಿರಾಂಕ USTRING_TYPE *extra;
  ಸ್ಥಿರಾಂಕ int32_t *ಪರೋಕ್ಷ;

  ಆದರೆ (nrules == 0)
    ಹಿಂತಿರುಗಿ STRCMP (s1, s2);

  /* Catch empty strings.  */
  ಆದರೆ (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    ಹಿಂತಿರುಗಿ (*s1 != '\0') - (*s2 != '\0');

  rulesets = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  ಕೋಷ್ಟಕ = (ಸ್ಥಿರಾಂಕ int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ಕೋಷ್ಟಕ,SUFFIX))].string;
  weights = (ಸ್ಥಿರಾಂಕ USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ತೂಕ,SUFFIX))].string;
  extra = (ಸ್ಥಿರಾಂಕ USTRING_TYPE *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  ಪರೋಕ್ಷ = (ಸ್ಥಿರಾಂಕ int32_t *)
    current->ಮೌಲ್ಯಗಳು[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_ಪರೋಕ್ಷ,SUFFIX))].string;

  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) ಕೋಷ್ಟಕ) % __alignof__ (ಕೋಷ್ಟಕ[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  ಪ್ರತಿಜ್ಞಾ (((uintptr_t) ಪರೋಕ್ಷ) % __alignof__ (ಪರೋಕ್ಷ[0]) == 0);

  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0, ನಿಯಮ = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.ನಿಯಮ = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ pass = 0; pass < nrules; ++pass)
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
      seq1.us = (ಸ್ಥಿರಾಂಕ USTRING_TYPE *) s1;
      seq2.us = (ಸ್ಥಿರಾಂಕ USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      ಪೂರ್ಣಾಂಕ position = rulesets[ನಿಯಮ * nrules + pass] & ವಿಂಗಡಿಸು_position;

      ಆಗ (1)
	{
	  get_ಮುಂದಿನ_seq (&seq1, nrules, rulesets, weights, ಕೋಷ್ಟಕ,
				    extra, ಪರೋಕ್ಷ, pass);
	  get_ಮುಂದಿನ_seq (&seq2, nrules, rulesets, weights, ಕೋಷ್ಟಕ,
				    extra, ಪರೋಕ್ಷ, pass);
	  /* See whether any or both strings are empty.  */
	  ಆದರೆ (seq1.len == 0 || seq2.len == 0)
	    {
	      ಆದರೆ (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  ಆದರೆ (pass == 0 && STRCMP (s1, s2) == 0)
		    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
		  ಇಲ್ಲದಿದ್ದರೆ
		    ನಿಲ್ಲಿಸು;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      ಹಿಂತಿರುಗಿ seq1.len == 0 ? -1 : 1;
	    }

	  ಫಲಿತಾಂಶ = do_compare (&seq1, &seq2, position, weights);
	  ಆದರೆ (ಫಲಿತಾಂಶ != 0)
	    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
	}

      ನಿಯಮ = seq1.ನಿಯಮ;
    }

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
libc_hidden_def (STRCOLL)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE_CHAR_ಆವೃತ್ತಿ
weak_alias (__strcoll_l, strcoll_l)
#ಆದರೆ_ಅಂತ್ಯ
