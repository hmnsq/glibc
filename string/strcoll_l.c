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


#அந்தர்பாவ <assert.h>
#அந்தர்பாவ <langinfo.h>
#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <sys/param.h>
#அந்தர்பாவ <libc-diag.h>

#ifndef STRING_TYPE
# define STRING_TYPE எழுத்து
# define USTRING_TYPE unsigned எழுத்து
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#endif

#define CONCAT(a,b) CONCAT1(a,b)
#define CONCAT1(a,b) a##b

#அந்தர்பாவ "../locale/localeinfo.h"
#அந்தர்பாவ WEIGHT_H

/* Track status while looking for sequences in a string.  */
வகைவரை கட்டமைப்பு
{
  முழு len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  மாறிலி USTRING_TYPE *us;	/* The string.  */
  unsigned எழுத்து rule;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  மாறிலி USTRING_TYPE *back_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
நிலையான __always_inline வெறுமை
get_next_seq (coll_seq *seq, முழு nrules, மாறிலி unsigned எழுத்து *rulesets,
	      மாறிலி USTRING_TYPE *weights, மாறிலி int32_t *table,
	      மாறிலி USTRING_TYPE *extra, மாறிலி int32_t *indirect,
	      முழு pass)
{
  size_t val = seq->val = 0;
  முழு len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  மாறிலி USTRING_TYPE *us = seq->us;

  போது (len == 0)
    {
      ++val;
      எனில் (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  எனில் (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      எனில் (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      இல்லையெனில்
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  நிறுத்து;
	        }
	    }
	  இல்லையெனில்
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->back_us;
	      போது (i < backw)
		{
		  int32_t tmp = findidx (table, indirect, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      இல்லையெனில்
	{
	  backw_stop = idxmax;
	  int32_t prev_idx = idx;

	  போது (*us != L('\0'))
	    {
	      int32_t tmp = findidx (table, indirect, extra, &us, -1);
	      unsigned எழுத்து rule = tmp >> 24;
	      prev_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      எனில் (__glibc_unlikely (idxcnt == 0))
	        seq->rule = rule;

	      எனில் ((rulesets[rule * nrules + pass]
		   & sort_backward) == 0)
		/* No more backward characters to push.  */
		நிறுத்து;
	      ++idxcnt;
	    }

	  எனில் (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      எனில் (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		நிறுத்து;

	      backw_stop = ~0ul;
	    }
	  இல்லையெனில்
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->back_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      எனில் (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = prev_idx;
		}
	      எனில் (backw > backw_stop)
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
      DIAG_தள்ளு_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_எடு_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      க்கு (முழு i = 0; i < pass; i++)
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
நிலையான __always_inline முழு
do_compare (coll_seq *seq1, coll_seq *seq2, முழு position,
	    மாறிலி USTRING_TYPE *weights)
{
  முழு seq1len = seq1->len;
  முழு seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  முழு idx1 = seq1->idx;
  முழு idx2 = seq2->idx;
  முழு result = 0;

  /* Test for position if necessary.  */
  எனில் (position && val1 != val2)
    {
      result = val1 > val2 ? 1 : -1;
      செல் out;
    }

  /* Compare the two sequences.  */
  செய்
    {
      எனில் (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  result = weights[idx1] - weights[idx2];
	  செல் out;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  போது (seq1len > 0 && seq2len > 0);

  எனில் (position && seq1len != seq2len)
    result = seq1len - seq2len;

out:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  திரும்பு result;
}

முழு
STRCOLL (மாறிலி STRING_TYPE *s1, மாறிலி STRING_TYPE *s2, locale_t l)
{
  கட்டமைப்பு __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->மதிப்புகள்[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  மாறிலி unsigned எழுத்து *rulesets;
  மாறிலி int32_t *table;
  மாறிலி USTRING_TYPE *weights;
  மாறிலி USTRING_TYPE *extra;
  மாறிலி int32_t *indirect;

  எனில் (nrules == 0)
    திரும்பு STRCMP (s1, s2);

  /* Catch empty strings.  */
  எனில் (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    திரும்பு (*s1 != '\0') - (*s2 != '\0');

  rulesets = (மாறிலி unsigned எழுத்து *)
    current->மதிப்புகள்[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  table = (மாறிலி int32_t *)
    current->மதிப்புகள்[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  weights = (மாறிலி USTRING_TYPE *)
    current->மதிப்புகள்[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  extra = (மாறிலி USTRING_TYPE *)
    current->மதிப்புகள்[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  indirect = (மாறிலி int32_t *)
    current->மதிப்புகள்[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  ப்ரதிஜ்ஞா (((uintptr_t) table) % __alignof__ (table[0]) == 0);
  ப்ரதிஜ்ஞா (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  ப்ரதிஜ்ஞா (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  ப்ரதிஜ்ஞா (((uintptr_t) indirect) % __alignof__ (indirect[0]) == 0);

  முழு result = 0, rule = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_தள்ளு_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_எடு_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.rule = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  க்கு (முழு pass = 0; pass < nrules; ++pass)
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
      seq1.us = (மாறிலி USTRING_TYPE *) s1;
      seq2.us = (மாறிலி USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      முழு position = rulesets[rule * nrules + pass] & sort_position;

      போது (1)
	{
	  get_next_seq (&seq1, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  get_next_seq (&seq2, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  /* See whether any or both strings are empty.  */
	  எனில் (seq1.len == 0 || seq2.len == 0)
	    {
	      எனில் (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  எனில் (pass == 0 && STRCMP (s1, s2) == 0)
		    திரும்பு result;
		  இல்லையெனில்
		    நிறுத்து;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      திரும்பு seq1.len == 0 ? -1 : 1;
	    }

	  result = do_compare (&seq1, &seq2, position, weights);
	  எனில் (result != 0)
	    திரும்பு result;
	}

      rule = seq1.rule;
    }

  திரும்பு result;
}
libc_hidden_def (STRCOLL)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strcoll_l, strcoll_l)
#endif
