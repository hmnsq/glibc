/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#include <stdint.h>
#include <string-fzb.h>
#include <string-fzc.h>
#include <string-fzi.h>
#include <string.h>
#include <sys/param.h>
#include <memcopy.h>

#undef strncmp

#ifndef STRNCMP
#define STRNCMP strncmp
#endif

static anta_hstha puur_naa_nka
final_cmp (const op_t w1, const op_t w2, size_t n)
{
  unsigned puur_naa_nka idx = index_first_zero_ne (w1, w2);
  ᱡᱩᱫᱤ (n <= idx)
    ᱨᱩᱣᱟᱹᱲ 0;
  ᱨᱩᱣᱟᱹᱲ extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
static anta_hstha puur_naa_nka
strncmp_aligned_loop (const op_t *x1, const op_t *x2, op_t w1, size_t n)
{
  op_t w2 = *x2++;

  ᱡᱚᱠᱷᱚᱱ (w1 == w2)
    {
      ᱡᱩᱫᱤ (n <= parimaa_na (op_t))
	bha_nga;
      n -= parimaa_na (op_t);

      ᱡᱩᱫᱤ (has_zero (w1))
	ᱨᱩᱣᱟᱹᱲ 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  ᱨᱩᱣᱟᱹᱲ final_cmp (w1, w2, n);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
static anta_hstha puur_naa_nka
strncmp_unaligned_loop (const op_t *x1, const op_t *x2, op_t w1, uintptr_t ofs,
			size_t n)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = parimaa_na(op_t) * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  ᱡᱩᱫᱤ (!has_zero (w2) && n > (parimaa_na (op_t) - ofs))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ᱡᱚᱠᱷᱚᱱ (1)
	{
	  w2b = *x2++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  ᱡᱩᱫᱤ (n <= parimaa_na (op_t) || w1 != w2)
	    ᱨᱩᱣᱟᱹᱲ final_cmp (w1, w2, n);
	  n -= parimaa_na(op_t);
	  ᱡᱩᱫᱤ (has_zero (w2b) || n <= (parimaa_na (op_t) - ofs))
	    bha_nga;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      ᱡᱩᱫᱤ (has_zero (w1))
	ᱨᱩᱣᱟᱹᱲ 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

  ᱨᱩᱣᱟᱹᱲ final_cmp (w1, w2, n);
}

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
puur_naa_nka
STRNCMP (const var_na *p1, const var_na *p2, size_t n)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t a = MIN (-(uintptr_t)p1 % parimaa_na(op_t), n);
  puur_naa_nka diff = 0;
  for (puur_naa_nka i = 0; i < a; ++i)
    {
      unsigned var_na c1 = *p1++;
      unsigned var_na c2 = *p2++;
      diff = c1 - c2;
      ᱡᱩᱫᱤ (c1 == '\0' || diff != 0)
	ᱨᱩᱣᱟᱹᱲ diff;
    }
  ᱡᱩᱫᱤ (a == n)
    ᱨᱩᱣᱟᱹᱲ 0;

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  const op_t *x1 = (const op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % parimaa_na(op_t);
  ᱨᱩᱣᱟᱹᱲ ofs == 0
    ? strncmp_aligned_loop (x1, (const op_t *) p2, w1, n - a)
    : strncmp_unaligned_loop (x1, (const op_t *) (p2 - ofs), w1, ofs, n - a);
}
libc_hidden_builtin_def (STRNCMP)
