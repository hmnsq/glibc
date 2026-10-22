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

#اگر_تعریف_شدہ HAVE_CONFIG_H
# include "config.h"
#اگر_ختم

#اگر defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#اگر_ختم

#تعریف_منسوخ memcmp

#اگر_غیر_تعریف_شدہ MEMCMP
# define MEMCMP memcmp
#اگر_ختم

#اگر_تعریف_شدہ _LIBC

# include <memcopy.h>
# include <endian.h>

# اگر __BYTE_ORDER == __BIG_ENDIAN
#  define الفاظ_BIGENDIAN
# endif

#ورنہ	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(حجم (op_t))

/* Type to use for unaligned operations.  */
قسمتعریف غیرعلامتی حرف byte;

# ifndef الفاظ_BIGENDIAN
#  define ملاؤ(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# ورنہ
#  define ملاؤ(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#اگر_ختم	/* In the GNU C library.  */

#اگر_تعریف_شدہ الفاظ_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#ورنہ
# define CMP_LT_OR_GT(a, b) memcmp_بائٹیں ((a), (b))
#اگر_ختم

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#اگر_غیر_تعریف_شدہ الفاظ_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

ساکن صحیح memcmp_بائٹیں (op_t, op_t) __THROW;

ساکن صحیح
memcmp_بائٹیں (op_t a, op_t b)
{
  طویل صحیح srcp1 = (طویل صحیح) &a;
  طویل صحیح srcp2 = (طویل صحیح) &b;
  op_t a0, b0;

  کرو
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  جب (a0 == b0);
  واپس a0 - b0;
}
#اگر_ختم

ساکن صحیح memcmp_common_alignment (طویل, طویل, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
ساکن صحیح
memcmp_common_alignment (طویل صحیح srcp1, طویل صحیح srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  انتخاب (len % 4)
    {
    طےشدہ: /* Avoid warning about uninitialized local variables.  */
    حالت 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      جاؤ do1;
    حالت 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      جاؤ do2;
    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	واپس 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      جاؤ do3;
    حالت 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	جاؤ do0;
      /* Fall through.  */
    }

  کرو
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      اگر (a1 != b1)
	واپس CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      اگر (a0 != b0)
	واپس CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      اگر (a1 != b1)
	واپس CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      اگر (a0 != b0)
	واپس CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  جب (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  اگر (a1 != b1)
    واپس CMP_LT_OR_GT (a1, b1);
  واپس 0;
}

ساکن صحیح memcmp_not_common_alignment (طویل, طویل, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
ساکن صحیح
memcmp_not_common_alignment (طویل صحیح srcp1, طویل صحیح srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  صحیح shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  انتخاب (len % 4)
    {
    طےشدہ: /* Avoid warning about uninitialized local variables.  */
    حالت 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      جاؤ do1;
    حالت 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      جاؤ do2;
    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	واپس 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      جاؤ do3;
    حالت 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	جاؤ do0;
      /* Fall through.  */
    }

  کرو
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = ملاؤ(a2, shl, a3, shr);
      اگر (x != b3)
	واپس CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = ملاؤ(a3, shl, a0, shr);
      اگر (x != b0)
	واپس CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = ملاؤ(a0, shl, a1, shr);
      اگر (x != b1)
	واپس CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = ملاؤ(a1, shl, a2, shr);
      اگر (x != b2)
	واپس CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  جب (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = ملاؤ(a2, shl, a3, shr);
  اگر (x != b3)
    واپس CMP_LT_OR_GT (x, b3);
  واپس 0;
}

صحیح
MEMCMP (ثابت خالی *s1, ثابت خالی *s2, size_t len)
{
  op_t a0;
  op_t b0;
  طویل صحیح srcp1 = (طویل صحیح) s1;
  طویل صحیح srcp2 = (طویل صحیح) s2;
  op_t res;

  اگر (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      جب (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  اگر (res != 0)
	    واپس res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      اگر (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      ورنہ
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      اگر (res != 0)
	واپس res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  جب (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      اگر (res != 0)
	واپس res;
      len -= 1;
    }

  واپس 0;
}
libc_hidden_builtin_def(memcmp)
#اگر_تعریف_شدہ weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#اگر_ختم

#تعریف_منسوخ __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
