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


#अन्तर्भाव <assert.h>
#अन्तर्भाव <langinfo.h>
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <libc-diag.h>

#यदि_अपरिभाषितम् STRING_TYPE
# define STRING_TYPE वर्ण
# define USTRING_TYPE अचिह्नित वर्ण
# define STRCOLL __strcoll_l
# define STRCMP वाक्यं_तुलय
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#यदि_अन्तः

#परिभाषय CONCAT(a,b) CONCAT1(a,b)
#परिभाषय CONCAT1(a,b) a##b

#अन्तर्भाव "../locale/localeinfo.h"
#अन्तर्भाव WEIGHT_H

/* Track status while looking for sequences in a string.  */
प्रकारनिर्देश संरचना
{
  पूर्णाङ्क len;			/* Length of the current sequence.  */
  size_t val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  size_t idxmax;		/* Maximum index in sequences.  */
  size_t idxcnt;		/* Current count of indices.  */
  size_t backw;			/* Current Backward sequence index.  */
  size_t backw_stop;		/* Index where the backward sequences stop.  */
  ध्रुव USTRING_TYPE *us;	/* The string.  */
  अचिह्नित वर्ण नियमः;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  ध्रुव USTRING_TYPE *पृष्ठभागः_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
स्थिर __always_inline शून्य
get_अग्र_seq (coll_seq *seq, पूर्णाङ्क nrules, ध्रुव अचिह्नित वर्ण *rulesets,
	      ध्रुव USTRING_TYPE *weights, ध्रुव int32_t *सारणी,
	      ध्रुव USTRING_TYPE *extra, ध्रुव int32_t *परोक्षम्,
	      पूर्णाङ्क pass)
{
  size_t val = seq->val = 0;
  पूर्णाङ्क len = seq->len;
  size_t backw_stop = seq->backw_stop;
  size_t backw = seq->backw;
  size_t idxcnt = seq->idxcnt;
  size_t idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  ध्रुव USTRING_TYPE *us = seq->us;

  यावत् (len == 0)
    {
      ++val;
      यदि (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  यदि (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      यदि (idxcnt < idxmax)
		{
		  idx = seq->save_idx;
		  backw_stop = ~0ul;
		}
	      अन्यथा
		{
		  /* Nothing anymore.  The backward sequence ended with
		     the last sequence in the string.  Note that len is
		     still zero.  */
		  idx = 0;
		  भङ्ग;
	        }
	    }
	  अन्यथा
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      size_t i = backw_stop;
	      us = seq->पृष्ठभागः_us;
	      यावत् (i < backw)
		{
		  int32_t tmp = findidx (सारणी, परोक्षम्, extra, &us, -1);
		  idx = tmp & 0xffffff;
		  i++;
		}
	      --backw;
	      us = seq->us;
	    }
	}
      अन्यथा
	{
	  backw_stop = idxmax;
	  int32_t पूर्व_idx = idx;

	  यावत् (*us != L('\0'))
	    {
	      int32_t tmp = findidx (सारणी, परोक्षम्, extra, &us, -1);
	      अचिह्नित वर्ण नियमः = tmp >> 24;
	      पूर्व_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      यदि (__glibc_unlikely (idxcnt == 0))
	        seq->नियमः = नियमः;

	      यदि ((rulesets[नियमः * nrules + pass]
		   & क्रमय_backward) == 0)
		/* No more backward characters to push.  */
		भङ्ग;
	      ++idxcnt;
	    }

	  यदि (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      यदि (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		भङ्ग;

	      backw_stop = ~0ul;
	    }
	  अन्यथा
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->पृष्ठभागः_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      यदि (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = पूर्व_idx;
		}
	      यदि (backw > backw_stop)
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
      DIAG_प्रक्षिप_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_निष्कासय_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      प्रति (पूर्णाङ्क i = 0; i < pass; i++)
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
स्थिर __always_inline पूर्णाङ्क
do_compare (coll_seq *seq1, coll_seq *seq2, पूर्णाङ्क position,
	    ध्रुव USTRING_TYPE *weights)
{
  पूर्णाङ्क seq1len = seq1->len;
  पूर्णाङ्क seq2len = seq2->len;
  size_t val1 = seq1->val;
  size_t val2 = seq2->val;
  पूर्णाङ्क idx1 = seq1->idx;
  पूर्णाङ्क idx2 = seq2->idx;
  पूर्णाङ्क परिणाम = 0;

  /* Test for position if necessary.  */
  यदि (position && val1 != val2)
    {
      परिणाम = val1 > val2 ? 1 : -1;
      गच्छ बहिर्गमनम्;
    }

  /* Compare the two sequences.  */
  कुरु
    {
      यदि (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  परिणाम = weights[idx1] - weights[idx2];
	  गच्छ बहिर्गमनम्;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  यावत् (seq1len > 0 && seq2len > 0);

  यदि (position && seq1len != seq2len)
    परिणाम = seq1len - seq2len;

बहिर्गमनम्:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  प्रत्यागम परिणाम;
}

पूर्णाङ्क
STRCOLL (ध्रुव STRING_TYPE *s1, ध्रुव STRING_TYPE *s2, locale_t l)
{
  संरचना __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  ध्रुव अचिह्नित वर्ण *rulesets;
  ध्रुव int32_t *सारणी;
  ध्रुव USTRING_TYPE *weights;
  ध्रुव USTRING_TYPE *extra;
  ध्रुव int32_t *परोक्षम्;

  यदि (nrules == 0)
    प्रत्यागम STRCMP (s1, s2);

  /* Catch empty strings.  */
  यदि (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    प्रत्यागम (*s1 != '\0') - (*s2 != '\0');

  rulesets = (ध्रुव अचिह्नित वर्ण *)
    current->मानानि[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  सारणी = (ध्रुव int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_सारणी,SUFFIX))].string;
  weights = (ध्रुव USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  extra = (ध्रुव USTRING_TYPE *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  परोक्षम् = (ध्रुव int32_t *)
    current->मानानि[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_परोक्षम्,SUFFIX))].string;

  प्रतिज्ञा (((uintptr_t) सारणी) % __alignof__ (सारणी[0]) == 0);
  प्रतिज्ञा (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  प्रतिज्ञा (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  प्रतिज्ञा (((uintptr_t) परोक्षम्) % __alignof__ (परोक्षम्[0]) == 0);

  पूर्णाङ्क परिणाम = 0, नियमः = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_प्रक्षिप_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_निष्कासय_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.नियमः = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  प्रति (पूर्णाङ्क pass = 0; pass < nrules; ++pass)
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
      seq1.us = (ध्रुव USTRING_TYPE *) s1;
      seq2.us = (ध्रुव USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      पूर्णाङ्क position = rulesets[नियमः * nrules + pass] & क्रमय_position;

      यावत् (1)
	{
	  get_अग्र_seq (&seq1, nrules, rulesets, weights, सारणी,
				    extra, परोक्षम्, pass);
	  get_अग्र_seq (&seq2, nrules, rulesets, weights, सारणी,
				    extra, परोक्षम्, pass);
	  /* See whether any or both strings are empty.  */
	  यदि (seq1.len == 0 || seq2.len == 0)
	    {
	      यदि (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  यदि (pass == 0 && STRCMP (s1, s2) == 0)
		    प्रत्यागम परिणाम;
		  अन्यथा
		    भङ्ग;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      प्रत्यागम seq1.len == 0 ? -1 : 1;
	    }

	  परिणाम = do_compare (&seq1, &seq2, position, weights);
	  यदि (परिणाम != 0)
	    प्रत्यागम परिणाम;
	}

      नियमः = seq1.नियमः;
    }

  प्रत्यागम परिणाम;
}
libc_hidden_def (STRCOLL)

#यदि_अपरिभाषितम् WIDE_CHAR_संस्करणम्
weak_alias (__strcoll_l, strcoll_l)
#यदि_अन्तः
