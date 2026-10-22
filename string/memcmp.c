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

#എങ്കിൽ defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#endif

#undef memcmp

#ifndef MEMCMP
# define MEMCMP memcmp
#endif

#ifdef _LIBC

# include <memcopy.h>
# include <endian.h>

# എങ്കിൽ __BYTE_ORDER == __BIG_ENDIAN
#  define വാക്കുകൾ_BIGENDIAN
# endif

#അല്ലെങ്കിൽ	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(വലുപ്പം (op_t))

/* Type to use for unaligned operations.  */
തരനിർവചനം unsigned അക്ഷരം byte;

# ifndef വാക്കുകൾ_BIGENDIAN
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# അല്ലെങ്കിൽ
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#endif	/* In the GNU C library.  */

#ifdef വാക്കുകൾ_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#അല്ലെങ്കിൽ
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

#ifndef വാക്കുകൾ_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

സ്ഥിതം പൂർണ്ണസംഖ്യ memcmp_bytes (op_t, op_t) __THROW;

സ്ഥിതം പൂർണ്ണസംഖ്യ
memcmp_bytes (op_t a, op_t b)
{
  long പൂർണ്ണസംഖ്യ srcp1 = (long പൂർണ്ണസംഖ്യ) &a;
  long പൂർണ്ണസംഖ്യ srcp2 = (long പൂർണ്ണസംഖ്യ) &b;
  op_t a0, b0;

  ചെയ്യുക
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  ആകുമ്പോൾ (a0 == b0);
  തിരികെ a0 - b0;
}
#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ memcmp_common_alignment (long, long, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ
memcmp_common_alignment (long പൂർണ്ണസംഖ്യ srcp1, long പൂർണ്ണസംഖ്യ srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  തിരഞ്ഞെടുപ്പ് (len % 4)
    {
    സ്ഥിരസ്ഥിതി: /* Avoid warning about uninitialized local variables.  */
    അവസ്ഥ 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      പോകുക do1;
    അവസ്ഥ 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      പോകുക do2;
    അവസ്ഥ 0:
      എങ്കിൽ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	തിരികെ 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      പോകുക do3;
    അവസ്ഥ 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      എങ്കിൽ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	പോകുക do0;
      /* Fall through.  */
    }

  ചെയ്യുക
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      എങ്കിൽ (a1 != b1)
	തിരികെ CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      എങ്കിൽ (a0 != b0)
	തിരികെ CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      എങ്കിൽ (a1 != b1)
	തിരികെ CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      എങ്കിൽ (a0 != b0)
	തിരികെ CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ആകുമ്പോൾ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  എങ്കിൽ (a1 != b1)
    തിരികെ CMP_LT_OR_GT (a1, b1);
  തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ memcmp_not_common_alignment (long, long, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ
memcmp_not_common_alignment (long പൂർണ്ണസംഖ്യ srcp1, long പൂർണ്ണസംഖ്യ srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  പൂർണ്ണസംഖ്യ shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  തിരഞ്ഞെടുപ്പ് (len % 4)
    {
    സ്ഥിരസ്ഥിതി: /* Avoid warning about uninitialized local variables.  */
    അവസ്ഥ 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      പോകുക do1;
    അവസ്ഥ 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      പോകുക do2;
    അവസ്ഥ 0:
      എങ്കിൽ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	തിരികെ 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      പോകുക do3;
    അവസ്ഥ 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      എങ്കിൽ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	പോകുക do0;
      /* Fall through.  */
    }

  ചെയ്യുക
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = MERGE(a2, shl, a3, shr);
      എങ്കിൽ (x != b3)
	തിരികെ CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = MERGE(a3, shl, a0, shr);
      എങ്കിൽ (x != b0)
	തിരികെ CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = MERGE(a0, shl, a1, shr);
      എങ്കിൽ (x != b1)
	തിരികെ CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = MERGE(a1, shl, a2, shr);
      എങ്കിൽ (x != b2)
	തിരികെ CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  ആകുമ്പോൾ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = MERGE(a2, shl, a3, shr);
  എങ്കിൽ (x != b3)
    തിരികെ CMP_LT_OR_GT (x, b3);
  തിരികെ 0;
}

പൂർണ്ണസംഖ്യ
MEMCMP (സ്ഥിരം ശൂന്യം *s1, സ്ഥിരം ശൂന്യം *s2, size_t len)
{
  op_t a0;
  op_t b0;
  long പൂർണ്ണസംഖ്യ srcp1 = (long പൂർണ്ണസംഖ്യ) s1;
  long പൂർണ്ണസംഖ്യ srcp2 = (long പൂർണ്ണസംഖ്യ) s2;
  op_t res;

  എങ്കിൽ (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      ആകുമ്പോൾ (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  എങ്കിൽ (res != 0)
	    തിരികെ res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      എങ്കിൽ (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      അല്ലെങ്കിൽ
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      എങ്കിൽ (res != 0)
	തിരികെ res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  ആകുമ്പോൾ (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      എങ്കിൽ (res != 0)
	തിരികെ res;
      len -= 1;
    }

  തിരികെ 0;
}
libc_hidden_builtin_def(memcmp)
#ifdef weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#endif

#undef __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
