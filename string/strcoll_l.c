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


#అన్తర్భావ <assert.h>
#అన్తర్భావ <langinfo.h>
#అన్తర్భావ <locale.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <libc-diag.h>

#నిర్వచితం_కాకపోతే STRING_TYPE
# define STRING_TYPE అక్షరం
# define USTRING_TYPE గుర్తులేని అక్షరం
# define STRCOLL __strcoll_l
# define STRCMP strcmp
# define బరువు_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#అయితే_ముగింపు

#నిర్వచించు CONCAT(a,b) CONCAT1(a,b)
#నిర్వచించు CONCAT1(a,b) a##b

#అన్తర్భావ "../locale/localeinfo.h"
#అన్తర్భావ బరువు_H

/* Track status while looking for sequences in a string.  */
రకనిర్వచనం నిర్మాణం
{
  పూర్ణాంకం len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  స్థిరరాశి USTRING_TYPE *us;	/* The string.  */
  గుర్తులేని అక్షరం నియమం;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  స్థిరరాశి USTRING_TYPE *వెనుక_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
స్థిర __always_inline శూన్య
get_తదుపరి_seq (coll_seq *seq, పూర్ణాంకం nrules, స్థిరరాశి గుర్తులేని అక్షరం *rulesets,
	      స్థిరరాశి USTRING_TYPE *weights, స్థిరరాశి int32_t *పట్టిక,
	      స్థిరరాశి USTRING_TYPE *extra, స్థిరరాశి int32_t *పరోక్ష,
	      పూర్ణాంకం pass)
{
  size_t val = seq->val = 0;
  పూర్ణాంకం len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  స్థిరరాశి USTRING_TYPE *us = seq->us;

  అయితే (len == 0)
    {
      ++val;
      ఒకవేళ (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  ఒకవేళ (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      ఒకవేళ (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      లేకపోతే
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  ఆపు;
	        }
	    }
	  లేకపోతే
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->వెనుక_us;
	      అయితే (i < backw)
		{
		  int32_t tmp = findidx (పట్టిక, పరోక్ష, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      లేకపోతే
	{
	  backw_stop = idxmax;
	  int32_t prev_idx = idx;

	  అయితే (*us != L('\0'))
	    {
	      int32_t tmp = findidx (పట్టిక, పరోక్ష, extra, &us, -1);
	      గుర్తులేని అక్షరం నియమం = tmp >> 24;
	      prev_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      ఒకవేళ (__glibc_unlikely (idxcnt == 0))
	        seq->నియమం = నియమం;

	      ఒకవేళ ((rulesets[నియమం * nrules + pass]
		   & క్రమీకరించు_backward) == 0)
		/* No more backward characters to push.  */
		ఆపు;
	      ++idxcnt;
	    }

	  ఒకవేళ (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      ఒకవేళ (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		ఆపు;

	      backw_stop = ~0ul;
	    }
	  లేకపోతే
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->వెనుక_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      ఒకవేళ (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = prev_idx;
		}
	      ఒకవేళ (backw > backw_stop)
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
      DIAG_నెట్టు_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_తీయి_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      కొరకు (పూర్ణాంకం i = 0; i < pass; i++)
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
స్థిర __always_inline పూర్ణాంకం
do_compare (coll_seq *seq1, coll_seq *seq2, పూర్ణాంకం position,
	    స్థిరరాశి USTRING_TYPE *weights)
{
  పూర్ణాంకం seq1len = seq1->len;
  పూర్ణాంకం seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  పూర్ణాంకం idx1 = seq1->idx;
  పూర్ణాంకం idx2 = seq2->idx;
  పూర్ణాంకం ఫలితం = 0;

  /* Test for position if necessary.  */
  ఒకవేళ (position && val1 != val2)
    {
      ఫలితం = val1 > val2 ? 1 : -1;
      వెళ్ళు బహిర్గతం;
    }

  /* Compare the two sequences.  */
  చేయి
    {
      ఒకవేళ (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  ఫలితం = weights[idx1] - weights[idx2];
	  వెళ్ళు బహిర్గతం;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  అయితే (seq1len > 0 && seq2len > 0);

  ఒకవేళ (position && seq1len != seq2len)
    ఫలితం = seq1len - seq2len;

బహిర్గతం:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  తిరిగి ఫలితం;
}

పూర్ణాంకం
STRCOLL (స్థిరరాశి STRING_TYPE *s1, స్థిరరాశి STRING_TYPE *s2, locale_t l)
{
  నిర్మాణం __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->విలువలు[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].మాట;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  స్థిరరాశి గుర్తులేని అక్షరం *rulesets;
  స్థిరరాశి int32_t *పట్టిక;
  స్థిరరాశి USTRING_TYPE *weights;
  స్థిరరాశి USTRING_TYPE *extra;
  స్థిరరాశి int32_t *పరోక్ష;

  ఒకవేళ (nrules == 0)
    తిరిగి STRCMP (s1, s2);

  /* Catch empty strings.  */
  ఒకవేళ (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    తిరిగి (*s1 != '\0') - (*s2 != '\0');

  rulesets = (స్థిరరాశి గుర్తులేని అక్షరం *)
    current->విలువలు[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  పట్టిక = (స్థిరరాశి int32_t *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_పట్టిక,SUFFIX))].string;
  weights = (స్థిరరాశి USTRING_TYPE *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_బరువు,SUFFIX))].string;
  extra = (స్థిరరాశి USTRING_TYPE *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  పరోక్ష = (స్థిరరాశి int32_t *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_పరోక్ష,SUFFIX))].string;

  ప్రతిజ్ఞా (((uintptr_t) పట్టిక) % __alignof__ (పట్టిక[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) పరోక్ష) % __alignof__ (పరోక్ష[0]) == 0);

  పూర్ణాంకం ఫలితం = 0, నియమం = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_నెట్టు_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_తీయి_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.నియమం = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  కొరకు (పూర్ణాంకం pass = 0; pass < nrules; ++pass)
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
      seq1.us = (స్థిరరాశి USTRING_TYPE *) s1;
      seq2.us = (స్థిరరాశి USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      పూర్ణాంకం position = rulesets[నియమం * nrules + pass] & క్రమీకరించు_position;

      అయితే (1)
	{
	  get_తదుపరి_seq (&seq1, nrules, rulesets, weights, పట్టిక,
				    extra, పరోక్ష, pass);
	  get_తదుపరి_seq (&seq2, nrules, rulesets, weights, పట్టిక,
				    extra, పరోక్ష, pass);
	  /* See whether any or both strings are empty.  */
	  ఒకవేళ (seq1.len == 0 || seq2.len == 0)
	    {
	      ఒకవేళ (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  ఒకవేళ (pass == 0 && STRCMP (s1, s2) == 0)
		    తిరిగి ఫలితం;
		  లేకపోతే
		    ఆపు;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      తిరిగి seq1.len == 0 ? -1 : 1;
	    }

	  ఫలితం = do_compare (&seq1, &seq2, position, weights);
	  ఒకవేళ (ఫలితం != 0)
	    తిరిగి ఫలితం;
	}

      నియమం = seq1.నియమం;
    }

  తిరిగి ఫలితం;
}
libc_hidden_def (STRCOLL)

#నిర్వచితం_కాకపోతే WIDE_CHAR_సంస్కరణ
weak_alias (__strcoll_l, strcoll_l)
#అయితే_ముగింపు
