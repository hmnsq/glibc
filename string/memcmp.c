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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_CONFIG_H
# include "config.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memcmp

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMCMP
# define MEMCMP memcmp
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _LIBC

# include <memcopy.h>
# include <endian.h>

# ಆದರೆ __BYTE_ORDER == __BIG_ENDIAN
#  define ಪದಗಳು_BIGENDIAN
# endif

#ಇಲ್ಲದಿದ್ದರೆ	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(ಗಾತ್ರ (op_t))

/* Type to use for unaligned operations.  */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ byte;

# ifndef ಪದಗಳು_BIGENDIAN
#  define ವಿಲೀನ(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# ಇಲ್ಲದಿದ್ದರೆ
#  define ವಿಲೀನ(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#ಆದರೆ_ಅಂತ್ಯ	/* In the GNU C library.  */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪದಗಳು_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#ಇಲ್ಲದಿದ್ದರೆ
# define CMP_LT_OR_GT(a, b) memcmp_ಬೈಟುಗಳು ((a), (b))
#ಆದರೆ_ಅಂತ್ಯ

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪದಗಳು_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ memcmp_ಬೈಟುಗಳು (op_t, op_t) __THROW;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
memcmp_ಬೈಟುಗಳು (op_t a, op_t b)
{
  ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp1 = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) &a;
  ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp2 = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) &b;
  op_t a0, b0;

  ಮಾಡು
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  ಆಗ (a0 == b0);
  ಹಿಂತಿರುಗಿ a0 - b0;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ memcmp_common_alignment (ದೀರ್ಘ, ದೀರ್ಘ, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
memcmp_common_alignment (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp1, ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  ಆಯ್ಕೆ (len % 4)
    {
    ಪೂರ್ವನಿಯೋಜಿತ: /* Avoid warning about uninitialized local variables.  */
    ಸ್ಥಿತಿ 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ಹೋಗು do1;
    ಸ್ಥಿತಿ 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      ಹೋಗು do2;
    ಸ್ಥಿತಿ 0:
      ಆದರೆ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಹಿಂತಿರುಗಿ 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ಹೋಗು do3;
    ಸ್ಥಿತಿ 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      ಆದರೆ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಹೋಗು do0;
      /* Fall through.  */
    }

  ಮಾಡು
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ಆದರೆ (a1 != b1)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      ಆದರೆ (a0 != b0)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      ಆದರೆ (a1 != b1)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      ಆದರೆ (a0 != b0)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ಆಗ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ಆದರೆ (a1 != b1)
    ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (a1, b1);
  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ memcmp_not_common_alignment (ದೀರ್ಘ, ದೀರ್ಘ, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
memcmp_not_common_alignment (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp1, ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  ಪೂರ್ಣಾಂಕ shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  ಆಯ್ಕೆ (len % 4)
    {
    ಪೂರ್ವನಿಯೋಜಿತ: /* Avoid warning about uninitialized local variables.  */
    ಸ್ಥಿತಿ 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ಹೋಗು do1;
    ಸ್ಥಿತಿ 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      ಹೋಗು do2;
    ಸ್ಥಿತಿ 0:
      ಆದರೆ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಹಿಂತಿರುಗಿ 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      ಹೋಗು do3;
    ಸ್ಥಿತಿ 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      ಆದರೆ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ಹೋಗು do0;
      /* Fall through.  */
    }

  ಮಾಡು
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = ವಿಲೀನ(a2, shl, a3, shr);
      ಆದರೆ (x != b3)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = ವಿಲೀನ(a3, shl, a0, shr);
      ಆದರೆ (x != b0)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = ವಿಲೀನ(a0, shl, a1, shr);
      ಆದರೆ (x != b1)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = ವಿಲೀನ(a1, shl, a2, shr);
      ಆದರೆ (x != b2)
	ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ಆಗ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = ವಿಲೀನ(a2, shl, a3, shr);
  ಆದರೆ (x != b3)
    ಹಿಂತಿರುಗಿ CMP_LT_OR_GT (x, b3);
  ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ
MEMCMP (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s1, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s2, size_t len)
{
  op_t a0;
  op_t b0;
  ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp1 = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) s1;
  ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp2 = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) s2;
  op_t res;

  ಆದರೆ (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      ಆಗ (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  ಆದರೆ (res != 0)
	    ಹಿಂತಿರುಗಿ res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      ಆದರೆ (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      ಇಲ್ಲದಿದ್ದರೆ
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      ಆದರೆ (res != 0)
	ಹಿಂತಿರುಗಿ res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  ಆಗ (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      ಆದರೆ (res != 0)
	ಹಿಂತಿರುಗಿ res;
      len -= 1;
    }

  ಹಿಂತಿರುಗಿ 0;
}
libc_hidden_builtin_def(memcmp)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
