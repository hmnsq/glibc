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

#ಯದಿ defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#endif

#undef memcmp

#ifndef MEMCMP
# define MEMCMP memcmp
#endif

#ifdef _LIBC

# include <memcopy.h>
# include <endian.h>

# ಯದಿ __BYTE_ORDER == __BIG_ENDIAN
#  define ಪದಗಳು_BIGENDIAN
# endif

#ಅನ್ಯಥಾ	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(ಪರಿಮಾಣ (op_t))

/* Type to use for unaligned operations.  */
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ವರ್ಣ byte;

# ifndef ಪದಗಳು_BIGENDIAN
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# ಅನ್ಯಥಾ
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#endif	/* In the GNU C library.  */

#ifdef ಪದಗಳು_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#ಅನ್ಯಥಾ
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

#ifndef ಪದಗಳು_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ memcmp_bytes (op_t, op_t) __THROW;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
memcmp_bytes (op_t a, op_t b)
{
  long ಪೂರ್ಣಾಙ್ಕ srcp1 = (long ಪೂರ್ಣಾಙ್ಕ) &a;
  long ಪೂರ್ಣಾಙ್ಕ srcp2 = (long ಪೂರ್ಣಾಙ್ಕ) &b;
  op_t a0, b0;

  ಕುರು
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  ಯಾವತ್ (a0 == b0);
  ಪ್ರತ್ಯಾಗಮ a0 - b0;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ memcmp_common_alignment (long, long, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
memcmp_common_alignment (long ಪೂರ್ಣಾಙ್ಕ srcp1, long ಪೂರ್ಣಾಙ್ಕ srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  ವಿಕಲ್ಪ (len % 4)
    {
    ಸ್ವಭಾವ: /* Avoid warning about uninitialized local variables.  */
    ಪಕ್ಷ 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ಗಚ್ಛ do1;
    ಪಕ್ಷ 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      ಗಚ್ಛ do2;
    ಪಕ್ಷ 0:
      ಯದಿ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಪ್ರತ್ಯಾಗಮ 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ಗಚ್ಛ do3;
    ಪಕ್ಷ 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      ಯದಿ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಗಚ್ಛ do0;
      /* Fall through.  */
    }

  ಕುರು
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ಯದಿ (a1 != b1)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      ಯದಿ (a0 != b0)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      ಯದಿ (a1 != b1)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      ಯದಿ (a0 != b0)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ಯಾವತ್ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ಯದಿ (a1 != b1)
    ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (a1, b1);
  ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ memcmp_not_common_alignment (long, long, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
memcmp_not_common_alignment (long ಪೂರ್ಣಾಙ್ಕ srcp1, long ಪೂರ್ಣಾಙ್ಕ srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  ಪೂರ್ಣಾಙ್ಕ shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  ವಿಕಲ್ಪ (len % 4)
    {
    ಸ್ವಭಾವ: /* Avoid warning about uninitialized local variables.  */
    ಪಕ್ಷ 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ಗಚ್ಛ do1;
    ಪಕ್ಷ 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      ಗಚ್ಛ do2;
    ಪಕ್ಷ 0:
      ಯದಿ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಪ್ರತ್ಯಾಗಮ 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      ಗಚ್ಛ do3;
    ಪಕ್ಷ 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      ಯದಿ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಗಚ್ಛ do0;
      /* Fall through.  */
    }

  ಕುರು
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = MERGE(a2, shl, a3, shr);
      ಯದಿ (x != b3)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = MERGE(a3, shl, a0, shr);
      ಯದಿ (x != b0)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = MERGE(a0, shl, a1, shr);
      ಯದಿ (x != b1)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = MERGE(a1, shl, a2, shr);
      ಯದಿ (x != b2)
	ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ಯಾವತ್ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = MERGE(a2, shl, a3, shr);
  ಯದಿ (x != b3)
    ಪ್ರತ್ಯಾಗಮ CMP_LT_OR_GT (x, b3);
  ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ
MEMCMP (ಧ್ರುವ ಶೂನ್ಯ *s1, ಧ್ರುವ ಶೂನ್ಯ *s2, size_t len)
{
  op_t a0;
  op_t b0;
  long ಪೂರ್ಣಾಙ್ಕ srcp1 = (long ಪೂರ್ಣಾಙ್ಕ) s1;
  long ಪೂರ್ಣಾಙ್ಕ srcp2 = (long ಪೂರ್ಣಾಙ್ಕ) s2;
  op_t res;

  ಯದಿ (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      ಯಾವತ್ (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  ಯದಿ (res != 0)
	    ಪ್ರತ್ಯಾಗಮ res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      ಯದಿ (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      ಅನ್ಯಥಾ
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      ಯದಿ (res != 0)
	ಪ್ರತ್ಯಾಗಮ res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  ಯಾವತ್ (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      ಯದಿ (res != 0)
	ಪ್ರತ್ಯಾಗಮ res;
      len -= 1;
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}
libc_hidden_builtin_def(memcmp)
#ifdef weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#endif

#undef __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
