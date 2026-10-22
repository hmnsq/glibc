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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string-fzb.h>
#అన్తర్భావ <string-fzc.h>
#అన్తర్భావ <string-fzi.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <memcopy.h>

#నిర్వచనం_రద్దు అక్షరశ్రేణి_పోలిక

#నిర్వచితం_కాకపోతే STRNCMP
#నిర్వచించు STRNCMP అక్షరశ్రేణి_పోలిక
#అయితే_ముగింపు

స్థిర అంతఃవరుస పూర్ణాంకం
final_cmp (స్థిరరాశి op_t w1, స్థిరరాశి op_t w2, size_t n)
{
  గుర్తులేని పూర్ణాంకం idx = సూచీ_మొదటి_zero_ne (w1, w2);
  ఒకవేళ (n <= idx)
    తిరిగి 0;
  తిరిగి extractbyte (w1, idx) - extractbyte (w2, idx);
}

/* Aligned loop: if a difference is found, exit to compare the bytes.  Else
   if a zero is found we have equal strings.  */
స్థిర అంతఃవరుస పూర్ణాంకం
strncmp_aligned_loop (స్థిరరాశి op_t *x1, స్థిరరాశి op_t *x2, op_t w1, size_t n)
{
  op_t w2 = *x2++;

  అయితే (w1 == w2)
    {
      ఒకవేళ (n <= పరిమాణం (op_t))
	ఆపు;
      n -= పరిమాణం (op_t);

      ఒకవేళ (has_zero (w1))
	తిరిగి 0;
      w1 = *x1++;
      w2 = *x2++;
    }

  తిరిగి final_cmp (w1, w2, n);
}

/* Unaligned loop: align the first partial of P2, with 0xff for the rest of
   the bytes so that we can also apply the has_zero test to see if we have
   already reached EOS.  If we have, then we can simply fall through to the
   final comparison.  */
స్థిర అంతఃవరుస పూర్ణాంకం
strncmp_unaligned_loop (స్థిరరాశి op_t *x1, స్థిరరాశి op_t *x2, op_t w1, uintptr_t ofs,
			size_t n)
{
  op_t w2a = *x2++;
  uintptr_t sh_1 = ofs * CHAR_BIT;
  uintptr_t sh_2 = పరిమాణం(op_t) * CHAR_BIT - sh_1;

  op_t w2 = విలీనం (w2a, sh_1, (op_t)-1, sh_2);
  ఒకవేళ (!has_zero (w2) && n > (పరిమాణం (op_t) - ofs))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      అయితే (1)
	{
	  w2b = *x2++;
	  w2 = విలీనం (w2a, sh_1, w2b, sh_2);
	  ఒకవేళ (n <= పరిమాణం (op_t) || w1 != w2)
	    తిరిగి final_cmp (w1, w2, n);
	  n -= పరిమాణం(op_t);
	  ఒకవేళ (has_zero (w2b) || n <= (పరిమాణం (op_t) - ofs))
	    ఆపు;
	  w1 = *x1++;
	  w2a = w2b;
	}

      /* Zero found in the second partial of P2.  If we had EOS in the aligned
	 word, we have equality.  */
      ఒకవేళ (has_zero (w1))
	తిరిగి 0;

      /* Load the final word of P1 and align the final partial of P2.  */
      w1 = *x1++;
      w2 = విలీనం (w2b, sh_1, 0, sh_2);
    }

  తిరిగి final_cmp (w1, w2, n);
}

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
పూర్ణాంకం
STRNCMP (స్థిరరాశి అక్షరం *p1, స్థిరరాశి అక్షరం *p2, size_t n)
{
  /* Handle the unaligned bytes of p1 first.  */
  uintptr_t a = MIN (-(uintptr_t)p1 % పరిమాణం(op_t), n);
  పూర్ణాంకం diff = 0;
  కొరకు (పూర్ణాంకం i = 0; i < a; ++i)
    {
      గుర్తులేని అక్షరం c1 = *p1++;
      గుర్తులేని అక్షరం c2 = *p2++;
      diff = c1 - c2;
      ఒకవేళ (c1 == '\0' || diff != 0)
	తిరిగి diff;
    }
  ఒకవేళ (a == n)
    తిరిగి 0;

  /* P1 is now aligned to op_t.  P2 may or may not be.  */
  స్థిరరాశి op_t *x1 = (స్థిరరాశి op_t *) p1;
  op_t w1 = *x1++;
  uintptr_t ofs = (uintptr_t) p2 % పరిమాణం(op_t);
  తిరిగి ofs == 0
    ? strncmp_aligned_loop (x1, (స్థిరరాశి op_t *) p2, w1, n - a)
    : strncmp_unaligned_loop (x1, (స్థిరరాశి op_t *) (p2 - ofs), w1, ofs, n - a);
}
libc_hidden_builtin_def (STRNCMP)
