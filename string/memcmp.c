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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#אם defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#endif

#undef memcmp

#ifndef MEMCMP
# define MEMCMP memcmp
#endif

#ifdef _LIBC

# include <memcopy.h>
# include <endian.h>

# אם __BYTE_ORDER == __BIG_ENDIAN
#  define WORDS_BIGENDIAN
# endif

#אחרת	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(حجم (op_t))

/* Type to use for unaligned operations.  */
تعريفنوع unsigned حرف byte;

# ifndef WORDS_BIGENDIAN
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# אחרת
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#endif	/* In the GNU C library.  */

#ifdef WORDS_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#אחרת
# define CMP_LT_OR_GT(a, b) memcmp_bytes ((a), (b))
#endif

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#ifndef WORDS_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

ساكن صحيح memcmp_bytes (op_t, op_t) __THROW;

ساكن صحيح
memcmp_bytes (op_t a, op_t b)
{
  long صحيح srcp1 = (long صحيح) &a;
  long صحيح srcp2 = (long صحيح) &b;
  op_t a0, b0;

  עשה
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  כלעוד (a0 == b0);
  החזר a0 - b0;
}
#endif

ساكن صحيح memcmp_common_alignment (long, long, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
ساكن صحيح
memcmp_common_alignment (long صحيح srcp1, long صحيح srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  بدل (len % 4)
    {
    افتراضي: /* Avoid warning about uninitialized local variables.  */
    حالة 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      اذهب do1;
    حالة 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      اذهب do2;
    حالة 0:
      אם (OP_T_THRES <= 3 * OPSIZ && len == 0)
	החזר 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      اذهب do3;
    حالة 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      אם (OP_T_THRES <= 3 * OPSIZ && len == 0)
	اذهب do0;
      /* Fall through.  */
    }

  עשה
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      אם (a1 != b1)
	החזר CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      אם (a0 != b0)
	החזר CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      אם (a1 != b1)
	החזר CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      אם (a0 != b0)
	החזר CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  כלעוד (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  אם (a1 != b1)
    החזר CMP_LT_OR_GT (a1, b1);
  החזר 0;
}

ساكن صحيح memcmp_not_common_alignment (long, long, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
ساكن صحيح
memcmp_not_common_alignment (long صحيح srcp1, long صحيح srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  صحيح shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  بدل (len % 4)
    {
    افتراضي: /* Avoid warning about uninitialized local variables.  */
    حالة 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      اذهب do1;
    حالة 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      اذهب do2;
    حالة 0:
      אם (OP_T_THRES <= 3 * OPSIZ && len == 0)
	החזר 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      اذهب do3;
    حالة 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      אם (OP_T_THRES <= 3 * OPSIZ && len == 0)
	اذهب do0;
      /* Fall through.  */
    }

  עשה
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = MERGE(a2, shl, a3, shr);
      אם (x != b3)
	החזר CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = MERGE(a3, shl, a0, shr);
      אם (x != b0)
	החזר CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = MERGE(a0, shl, a1, shr);
      אם (x != b1)
	החזר CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = MERGE(a1, shl, a2, shr);
      אם (x != b2)
	החזר CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  כלעוד (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = MERGE(a2, shl, a3, shr);
  אם (x != b3)
    החזר CMP_LT_OR_GT (x, b3);
  החזר 0;
}

صحيح
MEMCMP (ثابت فراغ *s1, ثابت فراغ *s2, size_t len)
{
  op_t a0;
  op_t b0;
  long صحيح srcp1 = (long صحيح) s1;
  long صحيح srcp2 = (long صحيح) s2;
  op_t res;

  אם (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      כלעוד (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  אם (res != 0)
	    החזר res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      אם (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      אחרת
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      אם (res != 0)
	החזר res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  כלעוד (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      אם (res != 0)
	החזר res;
      len -= 1;
    }

  החזר 0;
}
libc_hidden_builtin_def(memcmp)
#ifdef weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#endif

#undef __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
