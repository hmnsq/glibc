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
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/param.h>
#അന്തര്ഭാവ <libc-diag.h>

#ifndef STRING_TYPE
# define STRING_TYPE അക്ഷരം
# define USTRING_TYPE unsigned അക്ഷരം
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#endif

#define CONCAT(a,b) CONCAT1(a,b)
#define CONCAT1(a,b) a##b

#അന്തര്ഭാവ "../locale/localeinfo.h"
#അന്തര്ഭാവ WEIGHT_H

/* Track status while looking for sequences in a string.  */
തരനിർവചനം ഘടന
{
  പൂർണ്ണസംഖ്യ len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  സ്ഥിരം USTRING_TYPE *us;	/* The string.  */
  unsigned അക്ഷരം rule;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  സ്ഥിരം USTRING_TYPE *back_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
സ്ഥിതം __always_inline ശൂന്യം
get_next_seq (coll_seq *seq, പൂർണ്ണസംഖ്യ nrules, സ്ഥിരം unsigned അക്ഷരം *rulesets,
	      സ്ഥിരം USTRING_TYPE *weights, സ്ഥിരം int32_t *table,
	      സ്ഥിരം USTRING_TYPE *extra, സ്ഥിരം int32_t *indirect,
	      പൂർണ്ണസംഖ്യ pass)
{
  size_t val = seq->val = 0;
  പൂർണ്ണസംഖ്യ len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  സ്ഥിരം USTRING_TYPE *us = seq->us;

  ആകുമ്പോൾ (len == 0)
    {
      ++val;
      എങ്കിൽ (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  എങ്കിൽ (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      എങ്കിൽ (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      അല്ലെങ്കിൽ
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  നിർത്തുക;
	        }
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->back_us;
	      ആകുമ്പോൾ (i < backw)
		{
		  int32_t tmp = findidx (table, indirect, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      അല്ലെങ്കിൽ
	{
	  backw_stop = idxmax;
	  int32_t prev_idx = idx;

	  ആകുമ്പോൾ (*us != L('\0'))
	    {
	      int32_t tmp = findidx (table, indirect, extra, &us, -1);
	      unsigned അക്ഷരം rule = tmp >> 24;
	      prev_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      എങ്കിൽ (__glibc_unlikely (idxcnt == 0))
	        seq->rule = rule;

	      എങ്കിൽ ((rulesets[rule * nrules + pass]
		   & sort_backward) == 0)
		/* No more backward characters to push.  */
		നിർത്തുക;
	      ++idxcnt;
	    }

	  എങ്കിൽ (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      എങ്കിൽ (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		നിർത്തുക;

	      backw_stop = ~0ul;
	    }
	  അല്ലെങ്കിൽ
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->back_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      എങ്കിൽ (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = prev_idx;
		}
	      എങ്കിൽ (backw > backw_stop)
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
      DIAG_തള്ളുക_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_എടുക്കുക_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < pass; i++)
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
സ്ഥിതം __always_inline പൂർണ്ണസംഖ്യ
do_compare (coll_seq *seq1, coll_seq *seq2, പൂർണ്ണസംഖ്യ position,
	    സ്ഥിരം USTRING_TYPE *weights)
{
  പൂർണ്ണസംഖ്യ seq1len = seq1->len;
  പൂർണ്ണസംഖ്യ seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  പൂർണ്ണസംഖ്യ idx1 = seq1->idx;
  പൂർണ്ണസംഖ്യ idx2 = seq2->idx;
  പൂർണ്ണസംഖ്യ result = 0;

  /* Test for position if necessary.  */
  എങ്കിൽ (position && val1 != val2)
    {
      result = val1 > val2 ? 1 : -1;
      പോകുക out;
    }

  /* Compare the two sequences.  */
  ചെയ്യുക
    {
      എങ്കിൽ (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  result = weights[idx1] - weights[idx2];
	  പോകുക out;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  ആകുമ്പോൾ (seq1len > 0 && seq2len > 0);

  എങ്കിൽ (position && seq1len != seq2len)
    result = seq1len - seq2len;

out:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  തിരികെ result;
}

പൂർണ്ണസംഖ്യ
STRCOLL (സ്ഥിരം STRING_TYPE *s1, സ്ഥിരം STRING_TYPE *s2, locale_t l)
{
  ഘടന __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  സ്ഥിരം unsigned അക്ഷരം *rulesets;
  സ്ഥിരം int32_t *table;
  സ്ഥിരം USTRING_TYPE *weights;
  സ്ഥിരം USTRING_TYPE *extra;
  സ്ഥിരം int32_t *indirect;

  എങ്കിൽ (nrules == 0)
    തിരികെ STRCMP (s1, s2);

  /* Catch empty strings.  */
  എങ്കിൽ (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    തിരികെ (*s1 != '\0') - (*s2 != '\0');

  rulesets = (സ്ഥിരം unsigned അക്ഷരം *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  table = (സ്ഥിരം int32_t *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  weights = (സ്ഥിരം USTRING_TYPE *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  extra = (സ്ഥിരം USTRING_TYPE *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  indirect = (സ്ഥിരം int32_t *)
    current->മൂല്യങ്ങൾ[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  പ്രതിജ്ഞാ (((uintptr_t) table) % __alignof__ (table[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  പ്രതിജ്ഞാ (((uintptr_t) indirect) % __alignof__ (indirect[0]) == 0);

  പൂർണ്ണസംഖ്യ result = 0, rule = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_തള്ളുക_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.rule = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  വേണ്ടി (പൂർണ്ണസംഖ്യ pass = 0; pass < nrules; ++pass)
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
      seq1.us = (സ്ഥിരം USTRING_TYPE *) s1;
      seq2.us = (സ്ഥിരം USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      പൂർണ്ണസംഖ്യ position = rulesets[rule * nrules + pass] & sort_position;

      ആകുമ്പോൾ (1)
	{
	  get_next_seq (&seq1, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  get_next_seq (&seq2, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  /* See whether any or both strings are empty.  */
	  എങ്കിൽ (seq1.len == 0 || seq2.len == 0)
	    {
	      എങ്കിൽ (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  എങ്കിൽ (pass == 0 && STRCMP (s1, s2) == 0)
		    തിരികെ result;
		  അല്ലെങ്കിൽ
		    നിർത്തുക;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      തിരികെ seq1.len == 0 ? -1 : 1;
	    }

	  result = do_compare (&seq1, &seq2, position, weights);
	  എങ്കിൽ (result != 0)
	    തിരികെ result;
	}

      rule = seq1.rule;
    }

  തിരികെ result;
}
libc_hidden_def (STRCOLL)

#ifndef WIDE_CHAR_VERSION
weak_alias (__strcoll_l, strcoll_l)
#endif
