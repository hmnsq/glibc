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

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <sys/param.h>                  /* Defines MAX.  */

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
#إذا CHAR_BIT < 10
# define LONG_NEEDLE_پوله 32U
#وإلا
# define LONG_NEEDLE_پوله SIZE_MAX
#د_که_پای

#که_نه_تعریف_شوی CANON_ELEMENT
# define CANON_ELEMENT(c) c
#د_که_پای
#که_نه_تعریف_شوی CMP_FUNC
# define CMP_FUNC memcmp
#د_که_پای

/* Check for end-of-line in strstr and strcasestr routines.
   We piggy-back matching procedure for detecting EOL where possible,
   and use AVAILABLE macro otherwise.  */
#که_نه_تعریف_شوی CHECK_EOL
# define CHECK_EOL (0)
#د_که_پای

/* Return NULL if argument is '\0'.  */
#که_نه_تعریف_شوی RET0_IF_0
# define RET0_IF_0(a) /* nothing */
#د_که_پای

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
ساكن size_t
critical_factorization (ثابت بینښه حرف *needle, size_t needle_len,
			size_t *period)
{
  /* Index of last byte of left half, or SIZE_MAX.  */
  size_t max_suffix, max_suffix_rev;
  size_t j; /* Index into NEEDLE for current candidate suffix.  */
  size_t k; /* Offset into current period.  */
  size_t p; /* Intermediate period.  */
  بینښه حرف a, b; /* Current comparison bytes.  */

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
  طالما (j + k < needle_len)
    {
      a = CANON_ELEMENT (needle[j + k]);
      b = CANON_ELEMENT (needle[max_suffix + k]);
      إذا (a < b)
	{
	  /* Suffix is smaller, period is entire prefix so far.  */
	  j += k;
	  k = 1;
	  p = j - max_suffix;
	}
      وإلا إذا (a == b)
	{
	  /* Advance through repetition of the current period.  */
	  إذا (k != p)
	    ++k;
	  وإلا
	    {
	      j += p;
	      k = 1;
	    }
	}
      وإلا /* b < a */
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
  طالما (j + k < needle_len)
    {
      a = CANON_ELEMENT (needle[j + k]);
      b = CANON_ELEMENT (needle[max_suffix_rev + k]);
      إذا (b < a)
	{
	  /* Suffix is smaller, period is entire prefix so far.  */
	  j += k;
	  k = 1;
	  p = j - max_suffix_rev;
	}
      وإلا إذا (a == b)
	{
	  /* Advance through repetition of the current period.  */
	  إذا (k != p)
	    ++k;
	  وإلا
	    {
	      j += p;
	      k = 1;
	    }
	}
      وإلا /* a < b */
	{
	  /* Suffix is larger, start over from current location.  */
	  max_suffix_rev = j++;
	  k = p = 1;
	}
    }

  /* Choose the longer suffix.  Return the first byte of the right
     half, rather than the last byte of the left half.  */
  إذا (max_suffix_rev + 1 < max_suffix + 1)
    أرجع max_suffix + 1;
  *period = p;
  أرجع max_suffix_rev + 1;
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
ساكن مضمن RETURN_TYPE
two_way_short_needle (ثابت بینښه حرف *haystack, size_t haystack_len,
		      ثابت بینښه حرف *needle, size_t needle_len)
{
  size_t i; /* Index into current byte of NEEDLE.  */
  size_t j; /* Index into current window of HAYSTACK.  */
  size_t period; /* The period of the right half of needle.  */
  size_t suffix; /* The index of the right half of needle.  */

  /* Factor the needle into two halves, such that the left half is
     smaller than the global period, and the right half is
     periodic (with a period as large as NEEDLE_LEN - suffix).  */
  suffix = critical_factorization (needle, needle_len, &period);

  /* Perform the search.  Each iteration compares the right half
     first.  */
  إذا (CMP_FUNC (needle, needle + period, suffix) == 0)
    {
      /* Entire needle is periodic; a mismatch can only advance by the
	 period, so use memory to avoid rescanning known occurrences
	 of the period.  */
      size_t حافظه = 0;
      j = 0;
      طالما (شته (haystack, haystack_len, j, needle_len))
	{
	  ثابت بینښه حرف *pneedle;
	  ثابت بینښه حرف *phaystack;

	  /* Scan for matches in right half.  */
	  i = MAX (suffix, حافظه);
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  طالما (i < needle_len && (CANON_ELEMENT (*pneedle++)
				    == CANON_ELEMENT (*phaystack++)))
	    ++i;
	  إذا (needle_len <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      طالما (حافظه < i + 1 && (CANON_ELEMENT (*pneedle--)
					== CANON_ELEMENT (*phaystack--)))
		--i;
	      إذا (i + 1 < حافظه + 1)
		أرجع (RETURN_TYPE) (haystack + j);
	      /* No match, so remember how many repetitions of period
		 on the right half were scanned.  */
	      j += period;
	      حافظه = needle_len - period;
	    }
	  وإلا
	    {
	      j += i - suffix + 1;
	      حافظه = 0;
	    }
	}
    }
  وإلا
    {
      ثابت بینښه حرف *phaystack;
      /* The comparison always starts from needle[suffix], so cache it
	 and use an optimized first-character loop.  */
      بینښه حرف needle_suffix = CANON_ELEMENT (needle[suffix]);

      /* The two halves of needle are distinct; no extra memory is
	 required, and any mismatch results in a maximal shift.  */
      period = MAX (suffix, needle_len - suffix) + 1;
      j = 0;
      طالما (شته (haystack, haystack_len, j, needle_len))
	{
	  بینښه حرف haystack_char;
	  ثابت بینښه حرف *pneedle;

	  phaystack = &haystack[suffix + j];

#که_تعریف_شوی FASTSEARCH
	  إذا (*phaystack++ != needle_suffix)
	    {
	      phaystack = FASTSEARCH (phaystack, needle_suffix,
				      haystack_len - needle_len - j);
	      إذا (phaystack == عدم)
		اذهب ret0;
	      j = phaystack - &haystack[suffix];
	      phaystack++;
	    }
#وإلا
	  طالما (needle_suffix
	      != (haystack_char = CANON_ELEMENT (*phaystack++)))
	    {
	      RET0_IF_0 (haystack_char);
# إذا !CHECK_EOL
	      ++j;
	      إذا (!شته (haystack, haystack_len, j, needle_len))
		اذهب ret0;
# endif
	    }

# إذا CHECK_EOL
	  /* Calculate J if it wasn't kept up-to-date in the first-character
	     loop.  */
	  j = phaystack - &haystack[suffix] - 1;
# endif
#د_که_پای
	  /* Scan for matches in right half.  */
	  i = suffix + 1;
	  pneedle = &needle[i];
	  طالما (i < needle_len)
	    {
	      إذا (CANON_ELEMENT (*pneedle++)
		  != (haystack_char = CANON_ELEMENT (*phaystack++)))
		{
		  RET0_IF_0 (haystack_char);
		  اكسر;
		}
	      ++i;
	    }
#إذا CHECK_EOL
	  /* Update minimal length of haystack.  */
	  إذا (phaystack > haystack + haystack_len)
	    haystack_len = phaystack - haystack;
#د_که_پای
	  إذا (needle_len <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      طالما (i != SIZE_MAX)
		{
		  إذا (CANON_ELEMENT (*pneedle--)
		      != (haystack_char = CANON_ELEMENT (*phaystack--)))
		    {
		      RET0_IF_0 (haystack_char);
		      اكسر;
		    }
		  --i;
		}
	      إذا (i == SIZE_MAX)
		أرجع (RETURN_TYPE) (haystack + j);
	      j += period;
	    }
	  وإلا
	    j += i - suffix + 1;
	}
    }
 ret0: __attribute__ ((ناکارول_شوی))
  أرجع عدم;
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
__attribute__((noinline)) ساكن RETURN_TYPE
two_way_long_needle (ثابت بینښه حرف *haystack, size_t haystack_len,
		     ثابت بینښه حرف *needle, size_t needle_len)
{
  size_t i; /* Index into current byte of NEEDLE.  */
  size_t j; /* Index into current window of HAYSTACK.  */
  size_t period; /* The period of the right half of needle.  */
  size_t suffix; /* The index of the right half of needle.  */
  size_t ښويدنه_جدول[1U << CHAR_BIT]; /* See below.  */

  /* Factor the needle into two halves, such that the left half is
     smaller than the global period, and the right half is
     periodic (with a period as large as NEEDLE_LEN - suffix).  */
  suffix = critical_factorization (needle, needle_len, &period);

  /* Populate shift_table.  For each possible byte value c,
     shift_table[c] is the distance from the last occurrence of c to
     the end of NEEDLE, or NEEDLE_LEN if c is absent from the NEEDLE.
     shift_table[NEEDLE[NEEDLE_LEN - 1]] contains the only 0.  */
  لكل (i = 0; i < 1U << CHAR_BIT; i++)
    ښويدنه_جدول[i] = needle_len;
  لكل (i = 0; i < needle_len; i++)
    ښويدنه_جدول[CANON_ELEMENT (needle[i])] = needle_len - i - 1;

  /* Perform the search.  Each iteration compares the right half
     first.  */
  إذا (CMP_FUNC (needle, needle + period, suffix) == 0)
    {
      /* Entire needle is periodic; a mismatch can only advance by the
	 period, so use memory to avoid rescanning known occurrences
	 of the period.  */
      size_t حافظه = 0;
      size_t ښويدنه;
      j = 0;
      طالما (شته (haystack, haystack_len, j, needle_len))
	{
	  ثابت بینښه حرف *pneedle;
	  ثابت بینښه حرف *phaystack;

	  /* Check the last byte first; if it does not match, then
	     shift to the next possible match location.  */
	  ښويدنه = ښويدنه_جدول[CANON_ELEMENT (haystack[j + needle_len - 1])];
	  إذا (0 < ښويدنه)
	    {
	      إذا (حافظه && ښويدنه < period)
		{
		  /* Since needle is periodic, but the last period has
		     a byte out of place, there can be no match until
		     after the mismatch.  */
		  ښويدنه = needle_len - period;
		}
	      حافظه = 0;
	      j += ښويدنه;
	      استمر;
	    }
	  /* Scan for matches in right half.  The last byte has
	     already been matched, by virtue of the shift table.  */
	  i = MAX (suffix, حافظه);
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  طالما (i < needle_len - 1 && (CANON_ELEMENT (*pneedle++)
					== CANON_ELEMENT (*phaystack++)))
	    ++i;
	  إذا (needle_len - 1 <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      طالما (حافظه < i + 1 && (CANON_ELEMENT (*pneedle--)
					== CANON_ELEMENT (*phaystack--)))
		--i;
	      إذا (i + 1 < حافظه + 1)
		أرجع (RETURN_TYPE) (haystack + j);
	      /* No match, so remember how many repetitions of period
		 on the right half were scanned.  */
	      j += period;
	      حافظه = needle_len - period;
	    }
	  وإلا
	    {
	      j += i - suffix + 1;
	      حافظه = 0;
	    }
	}
    }
  وإلا
    {
      /* The two halves of needle are distinct; no extra memory is
	 required, and any mismatch results in a maximal shift.  */
      size_t ښويدنه;
      period = MAX (suffix, needle_len - suffix) + 1;
      j = 0;
      طالما (شته (haystack, haystack_len, j, needle_len))
	{
	  ثابت بینښه حرف *pneedle;
	  ثابت بینښه حرف *phaystack;

	  /* Check the last byte first; if it does not match, then
	     shift to the next possible match location.  */
	  ښويدنه = ښويدنه_جدول[CANON_ELEMENT (haystack[j + needle_len - 1])];
	  إذا (0 < ښويدنه)
	    {
	      j += ښويدنه;
	      استمر;
	    }
	  /* Scan for matches in right half.  The last byte has
	     already been matched, by virtue of the shift table.  */
	  i = suffix;
	  pneedle = &needle[i];
	  phaystack = &haystack[i + j];
	  طالما (i < needle_len - 1 && (CANON_ELEMENT (*pneedle++)
					== CANON_ELEMENT (*phaystack++)))
	    ++i;
	  إذا (needle_len - 1 <= i)
	    {
	      /* Scan for matches in left half.  */
	      i = suffix - 1;
	      pneedle = &needle[i];
	      phaystack = &haystack[i + j];
	      طالما (i != SIZE_MAX && (CANON_ELEMENT (*pneedle--)
				       == CANON_ELEMENT (*phaystack--)))
		--i;
	      إذا (i == SIZE_MAX)
		أرجع (RETURN_TYPE) (haystack + j);
	      j += period;
	    }
	  وإلا
	    j += i - suffix + 1;
	}
    }
  أرجع عدم;
}

#تعریف_لغوه شته
#تعریف_لغوه CANON_ELEMENT
#تعریف_لغوه CMP_FUNC
#تعریف_لغوه RET0_IF_0
#تعریف_لغوه RETURN_TYPE
#تعریف_لغوه CHECK_EOL
