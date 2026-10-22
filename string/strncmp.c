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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string-fzb.h>
#अन्तर्भाव <string-fzc.h>
#अन्तर्भाव <string-fzi.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <memcopy.h>

#undef म_भेदन

#ifndef STRNCMP
#define STRNCMP म_भेदन
#endif

स्थिर अन्तःस्थ पूर्णाङ्क
final_cmp (ध्रुव op_t w1, ध्रुव op_t w2, माप_प्रकार n)
{
  अचिन्हित पूर्णाङ्क idx = index_first_zero_ne (w1, w2);
  यदि (n <= idx)
    प्रत्यागम 0;
  प्रत्यागम extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
स्थिर अन्तःस्थ पूर्णाङ्क
strncmp_aligned_loop (ध्रुव op_t *x1, ध्रुव op_t *x2, op_t w1, माप_प्रकार n)
{
  op_t w2 = *x2++;

  यावत् (w1 == w2)
    {
      यदि (n <= परिमाण (op_t))
	भङ्ग;
      n -= परिमाण (op_t);

      यदि (has_zero (w1))
	प्रत्यागम 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  प्रत्यागम final_cmp (w1, w2, n);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
स्थिर अन्तःस्थ पूर्णाङ्क
strncmp_unaligned_loop (ध्रुव op_t *x1, ध्रुव op_t *x2, op_t w1, uintptr_t ofs,
			माप_प्रकार n)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * अक्षर_बिट;
  uintptr_t sh_2 = परिमाण(op_t) * अक्षर_बिट - sh_1;

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  यदि (!has_zero (w2) && n > (परिमाण (op_t) - ofs))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      यावत् (1)
	{
	  w2b = *x2++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  यदि (n <= परिमाण (op_t) || w1 != w2)
	    प्रत्यागम final_cmp (w1, w2, n);
	  n -= परिमाण(op_t);
	  यदि (has_zero (w2b) || n <= (परिमाण (op_t) - ofs))
	    भङ्ग;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      यदि (has_zero (w1))
	प्रत्यागम 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

  प्रत्यागम final_cmp (w1, w2, n);
}

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
पूर्णाङ्क
STRNCMP (ध्रुव वर्ण *p1, ध्रुव वर्ण *p2, माप_प्रकार n)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t a = MIN (-(uintptr_t)p1 % परिमाण(op_t), n);
  पूर्णाङ्क diff = 0;
  प्रति (पूर्णाङ्क i = 0; i < a; ++i)
    {
      अचिन्हित वर्ण c1 = *p1++;
      अचिन्हित वर्ण c2 = *p2++;
      diff = c1 - c2;
      यदि (c1 == '\0' || diff != 0)
	प्रत्यागम diff;
    }
  यदि (a == n)
    प्रत्यागम 0;

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  ध्रुव op_t *x1 = (ध्रुव op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % परिमाण(op_t);
  प्रत्यागम ofs == 0
    ? strncmp_aligned_loop (x1, (ध्रुव op_t *) p2, w1, n - a)
    : strncmp_unaligned_loop (x1, (ध्रुव op_t *) (p2 - ofs), w1, ofs, n - a);
}
libc_hidden_builtin_def (STRNCMP)
