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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_CONFIG_H
# include "config.h"
#ਜੇ_ਅੰਤ

#ਜੇ defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memcmp

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMCMP
# define MEMCMP memcmp
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _LIBC

# include <memcopy.h>
# include <endian.h>

# ਜੇ __BYTE_ORDER == __BIG_ENDIAN
#  define ਸ਼ਬਦ_BIGENDIAN
# endif

#ਨਹੀਂਤਾਂ	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(ਆਕਾਰ (op_t))

/* Type to use for unaligned operations.  */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ byte;

# ifndef ਸ਼ਬਦ_BIGENDIAN
#  define ਮਿਲਾਓ(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# ਨਹੀਂਤਾਂ
#  define ਮਿਲਾਓ(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#ਜੇ_ਅੰਤ	/* In the GNU C library.  */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਸ਼ਬਦ_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#ਨਹੀਂਤਾਂ
# define CMP_LT_OR_GT(a, b) memcmp_ਬਾਈਟਾਂ ((a), (b))
#ਜੇ_ਅੰਤ

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਸ਼ਬਦ_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

ਸਥਿਰ ਪੂਰਨ memcmp_ਬਾਈਟਾਂ (op_t, op_t) __THROW;

ਸਥਿਰ ਪੂਰਨ
memcmp_ਬਾਈਟਾਂ (op_t a, op_t b)
{
  ਲੰਮਾ ਪੂਰਨ srcp1 = (ਲੰਮਾ ਪੂਰਨ) &a;
  ਲੰਮਾ ਪੂਰਨ srcp2 = (ਲੰਮਾ ਪੂਰਨ) &b;
  op_t a0, b0;

  ਕਰੋ
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  ਜਦੋਂ (a0 == b0);
  ਵਾਪਸ a0 - b0;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ memcmp_common_alignment (ਲੰਮਾ, ਲੰਮਾ, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
ਸਥਿਰ ਪੂਰਨ
memcmp_common_alignment (ਲੰਮਾ ਪੂਰਨ srcp1, ਲੰਮਾ ਪੂਰਨ srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  ਚੋਣ (len % 4)
    {
    ਮੂਲ: /* Avoid warning about uninitialized local variables.  */
    ਹਾਲਤ 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      ਜਾਓ do2;
    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ਜਾਓ do3;
    ਹਾਲਤ 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      /* Fall through.  */
    }

  ਕਰੋ
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      ਜੇ (a1 != b1)
	ਵਾਪਸ CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      ਜੇ (a0 != b0)
	ਵਾਪਸ CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      ਜੇ (a1 != b1)
	ਵਾਪਸ CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      ਜੇ (a0 != b0)
	ਵਾਪਸ CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ਜੇ (a1 != b1)
    ਵਾਪਸ CMP_LT_OR_GT (a1, b1);
  ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ memcmp_not_common_alignment (ਲੰਮਾ, ਲੰਮਾ, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
ਸਥਿਰ ਪੂਰਨ
memcmp_not_common_alignment (ਲੰਮਾ ਪੂਰਨ srcp1, ਲੰਮਾ ਪੂਰਨ srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  ਪੂਰਨ shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  ਚੋਣ (len % 4)
    {
    ਮੂਲ: /* Avoid warning about uninitialized local variables.  */
    ਹਾਲਤ 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      ਜਾਓ do2;
    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      ਜਾਓ do3;
    ਹਾਲਤ 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      /* Fall through.  */
    }

  ਕਰੋ
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = ਮਿਲਾਓ(a2, shl, a3, shr);
      ਜੇ (x != b3)
	ਵਾਪਸ CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = ਮਿਲਾਓ(a3, shl, a0, shr);
      ਜੇ (x != b0)
	ਵਾਪਸ CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = ਮਿਲਾਓ(a0, shl, a1, shr);
      ਜੇ (x != b1)
	ਵਾਪਸ CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = ਮਿਲਾਓ(a1, shl, a2, shr);
      ਜੇ (x != b2)
	ਵਾਪਸ CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = ਮਿਲਾਓ(a2, shl, a3, shr);
  ਜੇ (x != b3)
    ਵਾਪਸ CMP_LT_OR_GT (x, b3);
  ਵਾਪਸ 0;
}

ਪੂਰਨ
MEMCMP (ਅਚਲ ਖਾਲੀ *s1, ਅਚਲ ਖਾਲੀ *s2, size_t len)
{
  op_t a0;
  op_t b0;
  ਲੰਮਾ ਪੂਰਨ srcp1 = (ਲੰਮਾ ਪੂਰਨ) s1;
  ਲੰਮਾ ਪੂਰਨ srcp2 = (ਲੰਮਾ ਪੂਰਨ) s2;
  op_t res;

  ਜੇ (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      ਜਦੋਂ (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  ਜੇ (res != 0)
	    ਵਾਪਸ res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      ਜੇ (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      ਨਹੀਂਤਾਂ
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      ਜੇ (res != 0)
	ਵਾਪਸ res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  ਜਦੋਂ (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      ਜੇ (res != 0)
	ਵਾਪਸ res;
      len -= 1;
    }

  ਵਾਪਸ 0;
}
libc_hidden_builtin_def(memcmp)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
