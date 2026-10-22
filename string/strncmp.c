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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string-fzb.h>
#അന്തര്ഭാവ <string-fzc.h>
#അന്തര്ഭാവ <string-fzi.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/param.h>
#അന്തര്ഭാവ <memcopy.h>

#undef strncmp

#ifndef STRNCMP
#define STRNCMP strncmp
#endif

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ
final_cmp (സ്ഥിരം op_t w1, സ്ഥിരം op_t w2, size_t n)
{
  unsigned പൂർണ്ണസംഖ്യ idx = index_first_zero_ne (w1, w2);
  എങ്കിൽ (n <= idx)
    തിരികെ 0;
  തിരികെ extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ
strncmp_aligned_loop (സ്ഥിരം op_t *x1, സ്ഥിരം op_t *x2, op_t w1, size_t n)
{
  op_t w2 = *x2++;

  ആകുമ്പോൾ (w1 == w2)
    {
      എങ്കിൽ (n <= വലുപ്പം (op_t))
	നിർത്തുക;
      n -= വലുപ്പം (op_t);

      എങ്കിൽ (has_zero (w1))
	തിരികെ 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  തിരികെ final_cmp (w1, w2, n);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ
strncmp_unaligned_loop (സ്ഥിരം op_t *x1, സ്ഥിരം op_t *x2, op_t w1, uintptr_t ofs,
			size_t n)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = വലുപ്പം(op_t) * CHAR_BIT - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  എങ്കിൽ (!has_zero (w2) && n > (വലുപ്പം (op_t) - ofs))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ആകുമ്പോൾ (1)
	{
	  w2b = *x2++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  എങ്കിൽ (n <= വലുപ്പം (op_t) || w1 != w2)
	    തിരികെ final_cmp (w1, w2, n);
	  n -= വലുപ്പം(op_t);
	  എങ്കിൽ (has_zero (w2b) || n <= (വലുപ്പം (op_t) - ofs))
	    നിർത്തുക;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      എങ്കിൽ (has_zero (w1))
	തിരികെ 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

  തിരികെ final_cmp (w1, w2, n);
}

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
പൂർണ്ണസംഖ്യ
STRNCMP (സ്ഥിരം അക്ഷരം *p1, സ്ഥിരം അക്ഷരം *p2, size_t n)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t a = MIN (-(uintptr_t)p1 % വലുപ്പം(op_t), n);
  പൂർണ്ണസംഖ്യ diff = 0;
  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < a; ++i)
    {
      unsigned അക്ഷരം c1 = *p1++;
      unsigned അക്ഷരം c2 = *p2++;
      diff = c1 - c2;
      എങ്കിൽ (c1 == '\0' || diff != 0)
	തിരികെ diff;
    }
  എങ്കിൽ (a == n)
    തിരികെ 0;

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  സ്ഥിരം op_t *x1 = (സ്ഥിരം op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % വലുപ്പം(op_t);
  തിരികെ ofs == 0
    ? strncmp_aligned_loop (x1, (സ്ഥിരം op_t *) p2, w1, n - a)
    : strncmp_unaligned_loop (x1, (സ്ഥിരം op_t *) (p2 - ofs), w1, ofs, n - a);
}
libc_hidden_builtin_def (STRNCMP)
