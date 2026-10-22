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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <string-fzb.h>
#অন্তর্ভাৱ <string-fzc.h>
#অন্তর্ভাৱ <string-fzi.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <memcopy.h>

#ifdef STRCMP
# define strcmp STRCMP
#endif

স্থির অন্তঃস্থ পূর্ণাঙ্ক
final_cmp (ধ্রুৱ op_t w1, ধ্রুৱ op_t w2)
{
  unsigned পূর্ণাঙ্ক idx = index_first_zero_ne (w1, w2);
  ঘূৰাই extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
স্থির অন্তঃস্থ পূর্ণাঙ্ক
strcmp_aligned_loop (ধ্রুৱ op_t *x1, ধ্রুৱ op_t *x2, op_t w1)
{
  op_t w2 = *x2++;

  যেতিয়ালৈ (w1 == w2)
    {
      যদি (has_zero (w1))
	ঘূৰাই 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  ঘূৰাই final_cmp (w1, w2);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
স্থির অন্তঃস্থ পূর্ণাঙ্ক
strcmp_unaligned_loop (ধ্রুৱ op_t *x1, ধ্রুৱ op_t *x2, op_t w1, uintptr_t ofs)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = পরিমাণ(op_t) * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  যদি (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      যেতিয়ালৈ (1)
	{
	  w2b = *x2++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  যদি (w1 != w2)
	    ঘূৰাই final_cmp (w1, w2);
	  যদি (has_zero (w2b))
	    ভঙ্গ;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      যদি (has_zero (w1))
	ঘূৰাই 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

  ঘূৰাই final_cmp (w1, w2);
}

/* Compare S1 and S2, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
পূর্ণাঙ্ক
strcmp (ধ্রুৱ ৱর্ণ *p1, ধ্রুৱ ৱর্ণ *p2)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t n = -(uintptr_t)p1 % পরিমাণ(op_t);
  বাবে (পূর্ণাঙ্ক i = 0; i < n; ++i)
    {
      unsigned ৱর্ণ c1 = *p1++;
      unsigned ৱর্ণ c2 = *p2++;
      পূর্ণাঙ্ক diff = c1 - c2;
      যদি (c1 == '\0' || diff != 0)
	ঘূৰাই diff;
    }

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  ধ্রুৱ op_t *x1 = (ধ্রুৱ op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % পরিমাণ(op_t);
  ঘূৰাই ofs == 0
    ? strcmp_aligned_loop (x1, (ধ্রুৱ op_t *)p2, w1)
    : strcmp_unaligned_loop (x1, (ধ্রুৱ op_t *)(p2 - ofs), w1, ofs);
}
#ifndef STRCMP
libc_hidden_builtin_def (strcmp)
#endif
