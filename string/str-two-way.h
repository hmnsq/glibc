/* Byte-wise substring search, using the Two-Way algorithm.
   Copyright (C) 2008-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Eric Blake <ebb9@byu.net>, 2008.

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

/* Before including this file, you need to include <string.h> (and
   <config.h> before that, if not part of libc), and define:
     RETURN_TYPE             A macro that expands to the return type.
     AVAILABLE(h, h_l, j, n_l)
			     A macro that returns nonzero if there are
			     at least N_L bytes left starting at H[J].
			     H is 'unsigned char *', H_L, J, and N_L
			     are 'size_t'; H_L is an lvalue.  For
			     NUL-terminated searches, H_L can be
			     modified each iteration to avoid having
			     to compute the end of H up front.

  For case-insensitivity, you may optionally define:
     CMP_FUNC(p1, p2, l)     A macro that returns 0 iff the first L
			     characters of P1 and P2 are equal.
     CANON_ELEMENT(c)        A macro that canonicalizes an element right after
			     it has been fetched from one of the two strings.
			     The argument is an 'unsigned char'; the result
			     must be an 'unsigned char' as well.

  Other macros you may optionally define:
     RET0_IF_0(a)            Documented below at default definition.
     CHECK_EOL               Same.

  This file undefines the macros listed above, and defines
  LONG_NEEDLE_THRESHOLD.
*/

#समावेश <limits.h>
#समावेश <stdint.h>
#समावेश <sys/param.h>                  /* Defines MAX.  */

/* We use the Two-Way string matching algorithm, which guarantees
   linear complexity with constant space.  Additionally, for long
   needles, we also use a bad character shift table similar to the
   Boyer-Moore algorithm to achieve improved (potentially sub-linear)
   performance.

   See http://www-igm.univ-mlv.fr/~lecroq/string/node26.html#SECTION00260
   and http://en.wikipedia.org/wiki/Boyer-Moore_string_search_algorithm
*/

/* Point at which computing a bad-byte shift table is likely to be
   worthwhile.  Small needles should not compute a table, since it
   adds (1 << CHAR_BIT) + NEEDLE_LEN computations of preparation for a
   speedup no greater than a factor of NEEDLE_LEN.  The larger the
   needle, the better the potential performance gain.  On the other
   hand, on non-POSIX systems with CHAR_BIT larger than eight, the
   memory required for the table is prohibitive.  */
#अगर अक्षर_बिट < 10
# define LONG_NEEDLE_THRESHOLD 32U
#अन्यथा
# define LONG_NEEDLE_THRESHOLD SIZE_MAX
#पूर्ण_अगर

#अगर_अघोषित CANON_ELEMENT
# define CANON_ELEMENT(c) c
#पूर्ण_अगर
#अगर_अघोषित CMP_FUNC
# define CMP_FUNC स_भेद
#पूर्ण_अगर

/* Check for end-of-line in strstr and strcasestr routines.
   We piggy-back matching procedure for detecting EOL where possible,
   and use AVAILABLE macro otherwise.  */
#अगर_अघोषित CHECK_EOL
# define CHECK_EOL (0)
#पूर्ण_अगर

/* Return NULL if argument is '\0'.  */
#अगर_अघोषित RET0_IF_0
# define RET0_IF_0(a) /* nothing */
#पूर्ण_अगर

/* Perform a critical factorization of NEEDLE, of length NEEDLE_LEN.
   Return the index of the first byte in the right half, and set
   *PERIOD to the global period of the right half.

   The global period of a string is the smallest index (possibly its
   length) at which all remaining bytes in the string are repetitions
   of the prefix (the last repetition may be a subset of the prefix).

   When NEEDLE is factored into two halves, a local period is the
   length of the smallest word that shares a suffix with the left half
   and shares a prefix with the right half.  All factorizations of a
   non-empty NEEDLE have a local period of at least 1 and no greater
   than NEEDLE_LEN.

   A critical factorization has the property that the local period
   equals the global period.  All strings have at least one critical
   factorization with the left half smaller than the global period.

   Given an ordered alphabet, a critical factorization can be computed
   in linear time, with 2 * NEEDLE_LEN comparisons, by computing the
   larger of two ordered maximal suffixes.  The ordered maximal
   suffixes are determined by lexicographic comparison of
   periodicity.  */
अटल माप_प्रकार
critical_factorization (स्थिर अचिन्हित अक्षर *needle, माप_प्रकार needle_len,
			माप_प्रकार *period)
{
  /* Index of last byte of left half, or SIZE_MAX.  */
  माप_प्रकार max_suffix, max_suffix_rev;
  माप_प्रकार j; /* Index into NEEDLE for current candidate suffix.  */
  माप_प्रकार k; /* Offset into current period.  */
  माप_प्रकार p; /* Intermediate period.  */
  अचिन्हित अक्षर a, b; /* Current comparison bytes.  */

  /* Invariants:
     0 <= j < NEEDLE_LEN - 1
     -1 <= max_suffix{,_rev} < j (treating SIZE_MAX as if it were signed)
     min(max_suffix, max_suffix_rev) < global period of NEEDLE
     1 <= p <= global period of NEEDLE
     p == global period of the substring NEEDLE[max_suffix{,_rev}+1...j]
     1 <= k <= p
  */

  /* Perform lexicographic search.  */
  max_suffix = SIZE_MAX;
  j = 0;
  k = p = 1;
  जबतक (j + k < needle_len)
    {
      a = CANON_ELEMENT (needle[j + k]);
      b = CANON_ELEMENT (needle[max_suffix + k]);
      अगर (a < b)
	{
	  /* Suffix is smaller, period is entire prefix so far.  */
	  j += k;
	  k = 1;
	  p = j - max_suffix;
	}
      अन्यथा अगर (a == b)
	{
	  /* Advance through repetition of the current period.  */
	  अगर (k != p)
	    ++k;
	  अन्यथा
	    {
	      j += p;
	      k = 1;
	    }
	}
      अन्यथा /* b < a */
	{
	  /* Suffix is larger, start over from current location.  */
	  max_suffix = j++;
	  k = p = 1;
	}
    }
  *period = p;

  /* Perform reverse lexicographic search.  */
  max_suffix_rev = SIZE_MAX;
  j = 0;
  k = p = 1;
  जबतक (j + k < needle_len)
    {
      a = CANON_ELEMENT (needle[j + k]);
      b = CANON_ELEMENT (needle[max_suffix_rev + k]);
      अगर (b < a)
	{
	  /* Suffix is smaller, period is entire prefix so far.  */
	  j += k;
	  k = 1;
	  p = j - max_suffix_rev;
	}
      अन्यथा अगर (a == b)
	{
	  /* Advance through repetition of the current period.  */
	  अगर (k != p)
	    ++k;
	  अन्यथा
	    {
	      j += p;
	      k = 1;
	    }
	}
      अन्यथा /* a < b */
	{
	  /* Suffix is larger, start over from current location.  */
	  max_suffix_rev = j++;
	  k = p = 1;
	}
    }

  /* Choose the longer suffix.  Return the first byte of the right
     half, rather than the last byte of the left half.  */
  अगर (max_suffix_rev + 1 < max_suffix + 1)
    वापस max_suffix + 1;
  *period = p;
  वापस max_suffix_rev + 1;
}

/* Return the first location of non-empty NEEDLE within HAYSTACK, or
   NULL.  HAYSTACK_LEN is the minimum known length of HAYSTACK.  This
   method is optimized for NEEDLE_LEN < LONG_NEEDLE_THRESHOLD.
   Performance is guaranteed to be linear, with an initialization cost
   of 2 * NEEDLE_LEN comparisons.

   If AVAILABLE does not modify HAYSTACK_LEN (as in memmem), then at
   most 2 * HAYSTACK_LEN - NEEDLE_LEN comparisons occur in searching.
   If AVAILABLE modifies HAYSTACK_LEN (as in strstr), then at most 3 *
   HAYSTACK_LEN - NEEDLE_LEN comparisons occur in searching.  */
अटल अंतरभूत RETURN_TYPE
two_way_short_needle (स्थिर अचिन्हित अक्षर *haystack, माप_प्रकार haystack_len,
		      स्थिर अचिन्हित अक्षर *needle, माप_प्रकार needle_len)
{
  माप_प्रकार i; /* Index into current byte of NEEDLE.  */
  माप_प्रकार j; /* Index into current window of HAYSTACK.  */
  माप_प्रकार period; /* The period of the right half of needle.  */
  माप_प्रकार suffix; /* The index of the right half of needle.  */

  /* Factor the needle into two halves, such that the left half is
     smaller than the global period, and the right half is
     periodic (with a period as large as NEEDLE_LEN - suffix).  */
  suffix = critical_factorization (needle, needle_len, &period);

  /* Perform the search.  Each iteration compares the right half
     first.  */
  अगर (CMP_FUNC (needle, needle + period, suffix) == 0)
    {
      /* Entire needle is periodic; a mismatch can only advance by the
	 period, so use memory to avoid rescanning known occurrences
	 of the period.  */
      माप_प्रकार memory = 0;
      j = 0;
      जबतक (AVAILABLE (haystack, haystack_len, j, needle_len))
	{
	  स्थिर अचिन्हित अक्षर *pneedle;
	  स्थिर अचिन्हित अक्षर *phaystack;

	  /* Scan for matches in right half.  */
	  i = MAX (suffix, memory);
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  जबतक (i < needle_len && (CANON_ELEMENT (*pneedle++)
				    == CANON_ELEMENT (*phaystack++)))
	    ++i;
	  अगर (needle_len <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      जबतक (memory < i + 1 && (CANON_ELEMENT (*pneedle--)
					== CANON_ELEMENT (*phaystack--)))
		--i;
	      अगर (i + 1 < memory + 1)
		वापस (RETURN_TYPE) (haystack + j);
	      /* No match, so remember how many repetitions of period
		 on the right half were scanned.  */
	      j += period;
	      memory = needle_len - period;
	    }
	  अन्यथा
	    {
	      j += i - suffix + 1;
	      memory = 0;
	    }
	}
    }
  अन्यथा
    {
      स्थिर अचिन्हित अक्षर *phaystack;
      /* The comparison always starts from needle[suffix], so cache it
	 and use an optimized first-character loop.  */
      अचिन्हित अक्षर needle_suffix = CANON_ELEMENT (needle[suffix]);

      /* The two halves of needle are distinct; no extra memory is
	 required, and any mismatch results in a maximal shift.  */
      period = MAX (suffix, needle_len - suffix) + 1;
      j = 0;
      जबतक (AVAILABLE (haystack, haystack_len, j, needle_len))
	{
	  अचिन्हित अक्षर haystack_char;
	  स्थिर अचिन्हित अक्षर *pneedle;

	  phaystack = &haystack[suffix + j];

#अगर_घोषित FASTSEARCH
	  अगर (*phaystack++ != needle_suffix)
	    {
	      phaystack = FASTSEARCH (phaystack, needle_suffix,
				      haystack_len - needle_len - j);
	      अगर (phaystack == शून्य)
		जाओ ret0;
	      j = phaystack - &haystack[suffix];
	      phaystack++;
	    }
#अन्यथा
	  जबतक (needle_suffix
	      != (haystack_char = CANON_ELEMENT (*phaystack++)))
	    {
	      RET0_IF_0 (haystack_char);
# अगर !CHECK_EOL
	      ++j;
	      अगर (!AVAILABLE (haystack, haystack_len, j, needle_len))
		जाओ ret0;
# endif
	    }

# अगर CHECK_EOL
	  /* Calculate J if it wasn't kept up-to-date in the first-character
	     loop.  */
	  j = phaystack - &haystack[suffix] - 1;
# endif
#पूर्ण_अगर
	  /* Scan for matches in right half.  */
	  i = suffix + 1;
	  pneedle = &needle[i];
	  जबतक (i < needle_len)
	    {
	      अगर (CANON_ELEMENT (*pneedle++)
		  != (haystack_char = CANON_ELEMENT (*phaystack++)))
		{
		  RET0_IF_0 (haystack_char);
		  अवरोध;
		}
	      ++i;
	    }
#अगर CHECK_EOL
	  /* Update minimal length of haystack.  */
	  अगर (phaystack > haystack + haystack_len)
	    haystack_len = phaystack - haystack;
#पूर्ण_अगर
	  अगर (needle_len <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      जबतक (i != SIZE_MAX)
		{
		  अगर (CANON_ELEMENT (*pneedle--)
		      != (haystack_char = CANON_ELEMENT (*phaystack--)))
		    {
		      RET0_IF_0 (haystack_char);
		      अवरोध;
		    }
		  --i;
		}
	      अगर (i == SIZE_MAX)
		वापस (RETURN_TYPE) (haystack + j);
	      j += period;
	    }
	  अन्यथा
	    j += i - suffix + 1;
	}
    }
 ret0: __attribute__ ((unused))
  वापस शून्य;
}

/* Return the first location of non-empty NEEDLE within HAYSTACK, or
   NULL.  HAYSTACK_LEN is the minimum known length of HAYSTACK.  This
   method is optimized for LONG_NEEDLE_THRESHOLD <= NEEDLE_LEN.
   Performance is guaranteed to be linear, with an initialization cost
   of 3 * NEEDLE_LEN + (1 << CHAR_BIT) operations.

   If AVAILABLE does not modify HAYSTACK_LEN (as in memmem), then at
   most 2 * HAYSTACK_LEN - NEEDLE_LEN comparisons occur in searching,
   and sublinear performance O(HAYSTACK_LEN / NEEDLE_LEN) is possible.
   If AVAILABLE modifies HAYSTACK_LEN (as in strstr), then at most 3 *
   HAYSTACK_LEN - NEEDLE_LEN comparisons occur in searching, and
   sublinear performance is not possible.

   Since this function is large and complex, block inlining to avoid
   slowing down the common case of small needles.  */
__attribute__((noinline)) अटल RETURN_TYPE
two_way_long_needle (स्थिर अचिन्हित अक्षर *haystack, माप_प्रकार haystack_len,
		     स्थिर अचिन्हित अक्षर *needle, माप_प्रकार needle_len)
{
  माप_प्रकार i; /* Index into current byte of NEEDLE.  */
  माप_प्रकार j; /* Index into current window of HAYSTACK.  */
  माप_प्रकार period; /* The period of the right half of needle.  */
  माप_प्रकार suffix; /* The index of the right half of needle.  */
  माप_प्रकार shift_table[1U << अक्षर_बिट]; /* See below.  */

  /* Factor the needle into two halves, such that the left half is
     smaller than the global period, and the right half is
     periodic (with a period as large as NEEDLE_LEN - suffix).  */
  suffix = critical_factorization (needle, needle_len, &period);

  /* Populate shift_table.  For each possible byte value c,
     shift_table[c] is the distance from the last occurrence of c to
     the end of NEEDLE, or NEEDLE_LEN if c is absent from the NEEDLE.
     shift_table[NEEDLE[NEEDLE_LEN - 1]] contains the only 0.  */
  क्रम (i = 0; i < 1U << अक्षर_बिट; i++)
    shift_table[i] = needle_len;
  क्रम (i = 0; i < needle_len; i++)
    shift_table[CANON_ELEMENT (needle[i])] = needle_len - i - 1;

  /* Perform the search.  Each iteration compares the right half
     first.  */
  अगर (CMP_FUNC (needle, needle + period, suffix) == 0)
    {
      /* Entire needle is periodic; a mismatch can only advance by the
	 period, so use memory to avoid rescanning known occurrences
	 of the period.  */
      माप_प्रकार memory = 0;
      माप_प्रकार shift;
      j = 0;
      जबतक (AVAILABLE (haystack, haystack_len, j, needle_len))
	{
	  स्थिर अचिन्हित अक्षर *pneedle;
	  स्थिर अचिन्हित अक्षर *phaystack;

	  /* Check the last byte first; if it does not match, then
	     shift to the next possible match location.  */
	  shift = shift_table[CANON_ELEMENT (haystack[j + needle_len - 1])];
	  अगर (0 < shift)
	    {
	      अगर (memory && shift < period)
		{
		  /* Since needle is periodic, but the last period has
		     a byte out of place, there can be no match until
		     after the mismatch.  */
		  shift = needle_len - period;
		}
	      memory = 0;
	      j += shift;
	      जारी;
	    }
	  /* Scan for matches in right half.  The last byte has
	     already been matched, by virtue of the shift table.  */
	  i = MAX (suffix, memory);
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  जबतक (i < needle_len - 1 && (CANON_ELEMENT (*pneedle++)
					== CANON_ELEMENT (*phaystack++)))
	    ++i;
	  अगर (needle_len - 1 <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      जबतक (memory < i + 1 && (CANON_ELEMENT (*pneedle--)
					== CANON_ELEMENT (*phaystack--)))
		--i;
	      अगर (i + 1 < memory + 1)
		वापस (RETURN_TYPE) (haystack + j);
	      /* No match, so remember how many repetitions of period
		 on the right half were scanned.  */
	      j += period;
	      memory = needle_len - period;
	    }
	  अन्यथा
	    {
	      j += i - suffix + 1;
	      memory = 0;
	    }
	}
    }
  अन्यथा
    {
      /* The two halves of needle are distinct; no extra memory is
	 required, and any mismatch results in a maximal shift.  */
      माप_प्रकार shift;
      period = MAX (suffix, needle_len - suffix) + 1;
      j = 0;
      जबतक (AVAILABLE (haystack, haystack_len, j, needle_len))
	{
	  स्थिर अचिन्हित अक्षर *pneedle;
	  स्थिर अचिन्हित अक्षर *phaystack;

	  /* Check the last byte first; if it does not match, then
	     shift to the next possible match location.  */
	  shift = shift_table[CANON_ELEMENT (haystack[j + needle_len - 1])];
	  अगर (0 < shift)
	    {
	      j += shift;
	      जारी;
	    }
	  /* Scan for matches in right half.  The last byte has
	     already been matched, by virtue of the shift table.  */
	  i = suffix;
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  जबतक (i < needle_len - 1 && (CANON_ELEMENT (*pneedle++)
					== CANON_ELEMENT (*phaystack++)))
	    ++i;
	  अगर (needle_len - 1 <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      जबतक (i != SIZE_MAX && (CANON_ELEMENT (*pneedle--)
				       == CANON_ELEMENT (*phaystack--)))
		--i;
	      अगर (i == SIZE_MAX)
		वापस (RETURN_TYPE) (haystack + j);
	      j += period;
	    }
	  अन्यथा
	    j += i - suffix + 1;
	}
    }
  वापस शून्य;
}

#अघोषित AVAILABLE
#अघोषित CANON_ELEMENT
#अघोषित CMP_FUNC
#अघोषित RET0_IF_0
#अघोषित RETURN_TYPE
#अघोषित CHECK_EOL
