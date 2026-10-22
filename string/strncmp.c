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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string-fzi.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <memcopy.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਲੜੀ_ਤੁਲਨਾ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRNCMP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRNCMP ਲੜੀ_ਤੁਲਨਾ
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ
final_cmp (ਅਚਲ op_t w1, ਅਚਲ op_t w2, size_t n)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ idx = ਸੂਚਕਾਂਕ_ਪਹਿਲਾ_zero_ne (w1, w2);
  ਜੇ (n <= idx)
    ਵਾਪਸ 0;
  ਵਾਪਸ extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ
strncmp_aligned_loop (ਅਚਲ op_t *x1, ਅਚਲ op_t *x2, op_t w1, size_t n)
{
  op_t w2 = *x2++;

  ਜਦੋਂ (w1 == w2)
    {
      ਜੇ (n <= ਆਕਾਰ (op_t))
	ਰੋਕੋ;
      n -= ਆਕਾਰ (op_t);

      ਜੇ (has_zero (w1))
	ਵਾਪਸ 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  ਵਾਪਸ final_cmp (w1, w2, n);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ
strncmp_unaligned_loop (ਅਚਲ op_t *x1, ਅਚਲ op_t *x2, op_t w1, uintptr_t ofs,
			size_t n)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = ਆਕਾਰ(op_t) * CHAR_BIT - sh_1;

  op_t w2 = ਮਿਲਾਓ (w2a, sh_1, (op_t)-1, sh_2);
  ਜੇ (!has_zero (w2) && n > (ਆਕਾਰ (op_t) - ofs))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      ਜਦੋਂ (1)
	{
	  w2b = *x2++;
	  w2 = ਮਿਲਾਓ (w2a, sh_1, w2b, sh_2);
	  ਜੇ (n <= ਆਕਾਰ (op_t) || w1 != w2)
	    ਵਾਪਸ final_cmp (w1, w2, n);
	  n -= ਆਕਾਰ(op_t);
	  ਜੇ (has_zero (w2b) || n <= (ਆਕਾਰ (op_t) - ofs))
	    ਰੋਕੋ;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      ਜੇ (has_zero (w1))
	ਵਾਪਸ 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = ਮਿਲਾਓ (w2b, sh_1, 0, sh_2);
    }

  ਵਾਪਸ final_cmp (w1, w2, n);
}

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
ਪੂਰਨ
STRNCMP (ਅਚਲ ਅੱਖਰ *p1, ਅਚਲ ਅੱਖਰ *p2, size_t n)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t a = MIN (-(uintptr_t)p1 % ਆਕਾਰ(op_t), n);
  ਪੂਰਨ diff = 0;
  ਲਈ (ਪੂਰਨ i = 0; i < a; ++i)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ c1 = *p1++;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ c2 = *p2++;
      diff = c1 - c2;
      ਜੇ (c1 == '\0' || diff != 0)
	ਵਾਪਸ diff;
    }
  ਜੇ (a == n)
    ਵਾਪਸ 0;

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  ਅਚਲ op_t *x1 = (ਅਚਲ op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % ਆਕਾਰ(op_t);
  ਵਾਪਸ ofs == 0
    ? strncmp_aligned_loop (x1, (ਅਚਲ op_t *) p2, w1, n - a)
    : strncmp_unaligned_loop (x1, (ਅਚਲ op_t *) (p2 - ofs), w1, ofs, n - a);
}
libc_hidden_builtin_def (STRNCMP)
