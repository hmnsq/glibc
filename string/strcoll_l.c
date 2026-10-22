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


#समावेश <assert.h>
#समावेश <langinfo.h>
#समावेश <locale.h>
#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <string.h>
#समावेश <sys/param.h>
#समावेश <libc-diag.h>

#अगर_अघोषित STRING_TYPE
# define STRING_TYPE अक्षर
# define USTRING_TYPE अचिन्हित अक्षर
# define STRCOLL __strcoll_l
# define STRCMP म_भेद
# define WEIGHT_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#पूर्ण_अगर

#घोषणा CONCAT(a,b) CONCAT1(a,b)
#घोषणा CONCAT1(a,b) a##b

#समावेश "../locale/localeinfo.h"
#समावेश WEIGHT_H

/* Track status while looking for sequences in a string.  */
प्रकार काष्ठा
{
  पूर्णांक len;			/* Length of the current sequence.  */
  माप_प्रकार val;			/* Position of the sequence relative to the
				   previous non-ignored sequence.  */
  माप_प्रकार idxmax;		/* Maximum index in sequences.  */
  माप_प्रकार idxcnt;		/* Current count of indices.  */
  माप_प्रकार backw;			/* Current Backward sequence index.  */
  माप_प्रकार backw_stop;		/* Index where the backward sequences stop.  */
  स्थिर USTRING_TYPE *us;	/* The string.  */
  अचिन्हित अक्षर rule;		/* Saved rule for the first sequence.  */
  int32_t idx;			/* Index to weight of the current sequence.  */
  int32_t save_idx;		/* Save looked up index of a forward
				   sequence after the last backward
				   sequence.  */
  स्थिर USTRING_TYPE *back_us;	/* Beginning of the backward sequence.  */
} coll_seq;

/* Get next sequence.  Traverse the string as required.  */
अटल __always_inline व्योम
get_अग्र_seq (coll_seq *seq, पूर्णांक nrules, स्थिर अचिन्हित अक्षर *rulesets,
	      स्थिर USTRING_TYPE *weights, स्थिर int32_t *table,
	      स्थिर USTRING_TYPE *extra, स्थिर int32_t *indirect,
	      पूर्णांक pass)
{
  माप_प्रकार val = seq->val = 0;
  पूर्णांक len = seq->len;
  माप_प्रकार backw_stop = seq->backw_stop;
  माप_प्रकार backw = seq->backw;
  माप_प्रकार idxcnt = seq->idxcnt;
  माप_प्रकार idxmax = seq->idxmax;
  int32_t idx = seq->idx;
  स्थिर USTRING_TYPE *us = seq->us;

  जबतक (len == 0)
    {
      ++val;
      अगर (backw_stop != ~0ul)
	{
	  /* There is something pushed.  */
	  अगर (backw == backw_stop)
	    {
	      /* The last pushed character was handled.  Continue
		 with forward characters.  */
	      अगर (idxcnt < idxmax)
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
		  अवरोध;
	        }
	    }
	  अन्यथा
	    {
	      /* XXX Traverse BACKW sequences from the beginning of
		 BACKW_STOP to get the next sequence.  Is there a quicker way
	         to do this?  */
	      माप_प्रकार i = backw_stop;
	      us = seq->back_us;
	      जबतक (i < backw)
		{
		  int32_t tmp = findidx (table, indirect, extra, &us, -1);
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

	  जबतक (*us != L('\0'))
	    {
	      int32_t tmp = findidx (table, indirect, extra, &us, -1);
	      अचिन्हित अक्षर rule = tmp >> 24;
	      पूर्व_idx = idx;
	      idx = tmp & 0xffffff;
	      idxcnt = idxmax++;

	      /* Save the rule for the first sequence.  */
	      अगर (__glibc_unlikely (idxcnt == 0))
	        seq->rule = rule;

	      अगर ((rulesets[rule * nrules + pass]
		   & sort_backward) == 0)
		/* No more backward characters to push.  */
		अवरोध;
	      ++idxcnt;
	    }

	  अगर (backw_stop >= idxcnt)
	    {
	      /* No sequence at all or just one.  */
	      अगर (idxcnt == idxmax || backw_stop > idxcnt)
		/* Note that len is still zero.  */
		अवरोध;

	      backw_stop = ~0ul;
	    }
	  अन्यथा
	    {
	      /* We pushed backward sequences.  If the stream ended with the
		 backward sequence, then we process the last sequence we
		 found.  Otherwise we process the sequence before the last
		 one since the last one was a forward sequence.  */
	      seq->back_us = seq->us;
	      seq->us = us;
	      backw = idxcnt;
	      अगर (idxmax > idxcnt)
		{
		  backw--;
		  seq->save_idx = idx;
		  idx = पूर्व_idx;
		}
	      अगर (backw > backw_stop)
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
      DIAG_धकेलो_NEEDS_COMMENT;
      DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (5, "-Wmaybe-uninitialized");
      len = weights[idx++];
      DIAG_निकालो_NEEDS_COMMENT;
      /* Skip over indices of previous levels.  */
      क्रम (पूर्णांक i = 0; i < pass; i++)
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
अटल __always_inline पूर्णांक
do_compare (coll_seq *seq1, coll_seq *seq2, पूर्णांक position,
	    स्थिर USTRING_TYPE *weights)
{
  पूर्णांक seq1len = seq1->len;
  पूर्णांक seq2len = seq2->len;
  माप_प्रकार val1 = seq1->val;
  माप_प्रकार val2 = seq2->val;
  पूर्णांक idx1 = seq1->idx;
  पूर्णांक idx2 = seq2->idx;
  पूर्णांक परिणाम = 0;

  /* Test for position if necessary.  */
  अगर (position && val1 != val2)
    {
      परिणाम = val1 > val2 ? 1 : -1;
      जाओ out;
    }

  /* Compare the two sequences.  */
  करो
    {
      अगर (weights[idx1] != weights[idx2])
	{
	  /* The sequences differ.  */
	  परिणाम = weights[idx1] - weights[idx2];
	  जाओ out;
	}

      /* Increment the offsets.  */
      ++idx1;
      ++idx2;

      --seq1len;
      --seq2len;
    }
  जबतक (seq1len > 0 && seq2len > 0);

  अगर (position && seq1len != seq2len)
    परिणाम = seq1len - seq2len;

out:
  seq1->len = seq1len;
  seq2->len = seq2len;
  seq1->idx = idx1;
  seq2->idx = idx2;
  वापस परिणाम;
}

पूर्णांक
STRCOLL (स्थिर STRING_TYPE *s1, स्थिर STRING_TYPE *s2, locale_t l)
{
  काष्ठा __locale_data *current = l->__locales[LC_COLLATE];
  uint32_t nrules = current->मूल्यावली[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  स्थिर अचिन्हित अक्षर *rulesets;
  स्थिर int32_t *table;
  स्थिर USTRING_TYPE *weights;
  स्थिर USTRING_TYPE *extra;
  स्थिर int32_t *indirect;

  अगर (nrules == 0)
    वापस STRCMP (s1, s2);

  /* Catch empty strings.  */
  अगर (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    वापस (*s1 != '\0') - (*s2 != '\0');

  rulesets = (स्थिर अचिन्हित अक्षर *)
    current->मूल्यावली[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  table = (स्थिर int32_t *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  weights = (स्थिर USTRING_TYPE *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  extra = (स्थिर USTRING_TYPE *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  indirect = (स्थिर int32_t *)
    current->मूल्यावली[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  निश्चित (((uintptr_t) table) % __alignof__ (table[0]) == 0);
  निश्चित (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  निश्चित (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  निश्चित (((uintptr_t) indirect) % __alignof__ (indirect[0]) == 0);

  पूर्णांक परिणाम = 0, rule = 0;

  /* With GCC 7 when compiling with -Os the compiler warns that
     seq1.back_us and seq2.back_us might be used uninitialized.
     Sometimes this warning appears at locations in locale/weightwc.h
     where the actual use is, but on architectures other than x86_64,
     x86 and s390x, a warning appears at the definitions of seq1 and
     seq2.  This uninitialized use is impossible for the same reason
     as described in comments in locale/weightwc.h.  */
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_Os_NEEDS_COMMENT_GCC (7, "-Wmaybe-uninitialized");
  coll_seq seq1, seq2;
  DIAG_निकालो_NEEDS_COMMENT;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.rule = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  क्रम (पूर्णांक pass = 0; pass < nrules; ++pass)
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
      seq1.us = (स्थिर USTRING_TYPE *) s1;
      seq2.us = (स्थिर USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      पूर्णांक position = rulesets[rule * nrules + pass] & sort_position;

      जबतक (1)
	{
	  get_अग्र_seq (&seq1, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  get_अग्र_seq (&seq2, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  /* See whether any or both strings are empty.  */
	  अगर (seq1.len == 0 || seq2.len == 0)
	    {
	      अगर (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  अगर (pass == 0 && STRCMP (s1, s2) == 0)
		    वापस परिणाम;
		  अन्यथा
		    अवरोध;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      वापस seq1.len == 0 ? -1 : 1;
	    }

	  परिणाम = do_compare (&seq1, &seq2, position, weights);
	  अगर (परिणाम != 0)
	    वापस परिणाम;
	}

      rule = seq1.rule;
    }

  वापस परिणाम;
}
libc_hidden_def (STRCOLL)

#अगर_अघोषित WIDE_CHAR_VERSION
weak_alias (__strcoll_l, strcoll_l)
#पूर्ण_अगर
