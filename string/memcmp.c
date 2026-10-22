/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Torbjorn Granlund (tege@sics.se).

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

#నిర్వచితమైతే HAVE_CONFIG_H
# include "config.h"
#అయితే_ముగింపు

#ఒకవేళ defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#అయితే_ముగింపు

#నిర్వచనం_రద్దు memcmp

#నిర్వచితం_కాకపోతే MEMCMP
# define MEMCMP memcmp
#అయితే_ముగింపు

#నిర్వచితమైతే _LIBC

# include <memcopy.h>
# include <endian.h>

# ఒకవేళ __BYTE_ORDER == __BIG_ENDIAN
#  define పదాలు_BIGENDIAN
# endif

#లేకపోతే	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(పరిమాణం (op_t))

/* Type to use for unaligned operations.  */
రకనిర్వచనం గుర్తులేని అక్షరం byte;

# ifndef పదాలు_BIGENDIAN
#  define విలీనం(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# లేకపోతే
#  define విలీనం(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#అయితే_ముగింపు	/* In the GNU C library.  */

#నిర్వచితమైతే పదాలు_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#లేకపోతే
# define CMP_LT_OR_GT(a, b) memcmp_బైట్లు ((a), (b))
#అయితే_ముగింపు

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#నిర్వచితం_కాకపోతే పదాలు_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

స్థిర పూర్ణాంకం memcmp_బైట్లు (op_t, op_t) __THROW;

స్థిర పూర్ణాంకం
memcmp_బైట్లు (op_t a, op_t b)
{
  దీర్ఘ పూర్ణాంకం srcp1 = (దీర్ఘ పూర్ణాంకం) &a;
  దీర్ఘ పూర్ణాంకం srcp2 = (దీర్ఘ పూర్ణాంకం) &b;
  op_t a0, b0;

  చేయి
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  అయితే (a0 == b0);
  తిరిగి a0 - b0;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం memcmp_common_alignment (దీర్ఘ, దీర్ఘ, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
స్థిర పూర్ణాంకం
memcmp_common_alignment (దీర్ఘ పూర్ణాంకం srcp1, దీర్ఘ పూర్ణాంకం srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  ఎంపిక (len % 4)
    {
    అప్రమేయ: /* Avoid warning about uninitialized local variables.  */
    స్థితి 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      వెళ్ళు do1;
    స్థితి 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      వెళ్ళు do2;
    స్థితి 0:
      ఒకవేళ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	తిరిగి 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      వెళ్ళు do3;
    స్థితి 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      ఒకవేళ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	వెళ్ళు do0;
      /* Fall through.  */
    }

  చేయి
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ఒకవేళ (a1 != b1)
	తిరిగి CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      ఒకవేళ (a0 != b0)
	తిరిగి CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      ఒకవేళ (a1 != b1)
	తిరిగి CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      ఒకవేళ (a0 != b0)
	తిరిగి CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  అయితే (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ఒకవేళ (a1 != b1)
    తిరిగి CMP_LT_OR_GT (a1, b1);
  తిరిగి 0;
}

స్థిర పూర్ణాంకం memcmp_not_common_alignment (దీర్ఘ, దీర్ఘ, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
స్థిర పూర్ణాంకం
memcmp_not_common_alignment (దీర్ఘ పూర్ణాంకం srcp1, దీర్ఘ పూర్ణాంకం srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  పూర్ణాంకం shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  ఎంపిక (len % 4)
    {
    అప్రమేయ: /* Avoid warning about uninitialized local variables.  */
    స్థితి 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      వెళ్ళు do1;
    స్థితి 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      వెళ్ళు do2;
    స్థితి 0:
      ఒకవేళ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	తిరిగి 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      వెళ్ళు do3;
    స్థితి 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      ఒకవేళ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	వెళ్ళు do0;
      /* Fall through.  */
    }

  చేయి
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = విలీనం(a2, shl, a3, shr);
      ఒకవేళ (x != b3)
	తిరిగి CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = విలీనం(a3, shl, a0, shr);
      ఒకవేళ (x != b0)
	తిరిగి CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = విలీనం(a0, shl, a1, shr);
      ఒకవేళ (x != b1)
	తిరిగి CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = విలీనం(a1, shl, a2, shr);
      ఒకవేళ (x != b2)
	తిరిగి CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  అయితే (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = విలీనం(a2, shl, a3, shr);
  ఒకవేళ (x != b3)
    తిరిగి CMP_LT_OR_GT (x, b3);
  తిరిగి 0;
}

పూర్ణాంకం
MEMCMP (స్థిరరాశి శూన్య *s1, స్థిరరాశి శూన్య *s2, size_t len)
{
  op_t a0;
  op_t b0;
  దీర్ఘ పూర్ణాంకం srcp1 = (దీర్ఘ పూర్ణాంకం) s1;
  దీర్ఘ పూర్ణాంకం srcp2 = (దీర్ఘ పూర్ణాంకం) s2;
  op_t res;

  ఒకవేళ (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      అయితే (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  ఒకవేళ (res != 0)
	    తిరిగి res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      ఒకవేళ (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      లేకపోతే
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      ఒకవేళ (res != 0)
	తిరిగి res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  అయితే (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      ఒకవేళ (res != 0)
	తిరిగి res;
      len -= 1;
    }

  తిరిగి 0;
}
libc_hidden_builtin_def(memcmp)
#నిర్వచితమైతే weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#అయితే_ముగింపు

#నిర్వచనం_రద్దు __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
