/* _memcopy.c -- subroutines for memory copy functions.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE...!  */

#شامل <stddef.h>
#شامل <libc-diag.h>
/* Compiling with -O1 might warn that 'a2' and 'a3' may be used
   uninitialized.  There are only two ways to arrive at labels 'do4', 'do3'
   or 'do1', all of which use 'a2' or 'a3' in the MERGE macro: either from
   the earlier switch case statement or via a loop iteration.  In all cases
   the switch statement or previous loop sets both 'a2' and 'a3'.

   Since the usage is within the MERGE macro we disable the
   warning in the definition, but only in this file.  */
DIAG_افزودن_NEEDS_COMMENT;
DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
#شامل <memcopy.h>
DIAG_برداشت_NEEDS_COMMENT;

/* _wordcopy_fwd_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   Both SRCP and DSTP should be aligned for memory operations on `op_t's.  */

#ifndef WORDCOPY_FWD_ALIGNED
# define WORDCOPY_FWD_ALIGNED _wordcopy_fwd_aligned
#endif

تهی
WORDCOPY_FWD_ALIGNED (long صحیح dstp, long صحیح srcp, size_t len)
{
  op_t a0, a1;

  انتخاب (len % 8)
    {
    حالت 2:
      a0 = ((op_t *) srcp)[0];
      srcp -= 6 * OPSIZ;
      dstp -= 7 * OPSIZ;
      len += 6;
      برو do1;
    حالت 3:
      a1 = ((op_t *) srcp)[0];
      srcp -= 5 * OPSIZ;
      dstp -= 6 * OPSIZ;
      len += 5;
      برو do2;
    حالت 4:
      a0 = ((op_t *) srcp)[0];
      srcp -= 4 * OPSIZ;
      dstp -= 5 * OPSIZ;
      len += 4;
      برو do3;
    حالت 5:
      a1 = ((op_t *) srcp)[0];
      srcp -= 3 * OPSIZ;
      dstp -= 4 * OPSIZ;
      len += 3;
      برو do4;
    حالت 6:
      a0 = ((op_t *) srcp)[0];
      srcp -= 2 * OPSIZ;
      dstp -= 3 * OPSIZ;
      len += 2;
      برو do5;
    حالت 7:
      a1 = ((op_t *) srcp)[0];
      srcp -= 1 * OPSIZ;
      dstp -= 2 * OPSIZ;
      len += 1;
      برو do6;

    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	بازگشت;
      a0 = ((op_t *) srcp)[0];
      srcp -= 0 * OPSIZ;
      dstp -= 1 * OPSIZ;
      برو do7;
    حالت 1:
      a1 = ((op_t *) srcp)[0];
      srcp -=-1 * OPSIZ;
      dstp -= 0 * OPSIZ;
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	برو do0;
      برو do8;			/* No-op.  */
    }

  انجامبده
    {
    do8:
      a0 = ((op_t *) srcp)[0];
      /* Compiling with -O1 may warn that 'a1' may be used uninitialized.
	 There are only two ways to arrive at label 'do8' and they are via a
	 do-while loop iteration or directly via the earlier switch 'case 1:'
	 case. The switch case always sets 'a1' and all previous loop
	 iterations will also have set 'a1' before the use.  */
      DIAG_افزودن_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
      ((op_t *) dstp)[0] = a1;
      DIAG_برداشت_NEEDS_COMMENT;
    do7:
      a1 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = a0;
    do6:
      a0 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = a1;
    do5:
      a1 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = a0;
    do4:
      a0 = ((op_t *) srcp)[4];
      ((op_t *) dstp)[4] = a1;
    do3:
      a1 = ((op_t *) srcp)[5];
      ((op_t *) dstp)[5] = a0;
    do2:
      a0 = ((op_t *) srcp)[6];
      ((op_t *) dstp)[6] = a1;
    do1:
      a1 = ((op_t *) srcp)[7];
      ((op_t *) dstp)[7] = a0;

      srcp += 8 * OPSIZ;
      dstp += 8 * OPSIZ;
      len -= 8;
    }
  وقتی (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[0] = a1;
}

/* _wordcopy_fwd_dest_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   DSTP should be aligned for memory operations on `op_t's, but SRCP must
   *not* be aligned.  */

#ifndef WORDCOPY_FWD_DEST_ALIGNED
# define WORDCOPY_FWD_DEST_ALIGNED _wordcopy_fwd_dest_aligned
#endif

تهی
WORDCOPY_FWD_DEST_ALIGNED (long صحیح dstp, long صحیح srcp, size_t len)
{
  op_t a0, a1, a2, a3;
  صحیح sh_1, sh_2;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp to make it aligned for copy.  */

  sh_1 = 8 * (srcp % OPSIZ);
  sh_2 = 8 * OPSIZ - sh_1;

  /* Make SRCP aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp &= -OPSIZ;

  انتخاب (len % 4)
    {
    حالت 2:
      a1 = ((op_t *) srcp)[0];
      a2 = ((op_t *) srcp)[1];
      srcp -= 1 * OPSIZ;
      dstp -= 3 * OPSIZ;
      len += 2;
      برو do1;
    حالت 3:
      a0 = ((op_t *) srcp)[0];
      a1 = ((op_t *) srcp)[1];
      srcp -= 0 * OPSIZ;
      dstp -= 2 * OPSIZ;
      len += 1;
      برو do2;
    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	بازگشت;
      a3 = ((op_t *) srcp)[0];
      a0 = ((op_t *) srcp)[1];
      srcp -=-1 * OPSIZ;
      dstp -= 1 * OPSIZ;
      len += 0;
      برو do3;
    حالت 1:
      a2 = ((op_t *) srcp)[0];
      a3 = ((op_t *) srcp)[1];
      srcp -=-2 * OPSIZ;
      dstp -= 0 * OPSIZ;
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	برو do0;
      برو do4;			/* No-op.  */
    }

  انجامبده
    {
    do4:
      a0 = ((op_t *) srcp)[0];
      ((op_t *) dstp)[0] = MERGE (a2, sh_1, a3, sh_2);
    do3:
      a1 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = MERGE (a3, sh_1, a0, sh_2);
    do2:
      a2 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = MERGE (a0, sh_1, a1, sh_2);
    do1:
      a3 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = MERGE (a1, sh_1, a2, sh_2);

      srcp += 4 * OPSIZ;
      dstp += 4 * OPSIZ;
      len -= 4;
    }
  وقتی (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[0] = MERGE (a2, sh_1, a3, sh_2);
}

/* _wordcopy_bwd_aligned -- Copy block finishing right before
   SRCP to block finishing right before DSTP with LEN `op_t' words
   (not LEN bytes!).  Both SRCP and DSTP should be aligned for memory
   operations on `op_t's.  */

#ifndef WORDCOPY_BWD_ALIGNED
# define WORDCOPY_BWD_ALIGNED _wordcopy_bwd_aligned
#endif

تهی
WORDCOPY_BWD_ALIGNED (long صحیح dstp, long صحیح srcp, size_t len)
{
  op_t a0, a1;

  انتخاب (len % 8)
    {
    حالت 2:
      srcp -= 2 * OPSIZ;
      dstp -= 1 * OPSIZ;
      a0 = ((op_t *) srcp)[1];
      len += 6;
      برو do1;
    حالت 3:
      srcp -= 3 * OPSIZ;
      dstp -= 2 * OPSIZ;
      a1 = ((op_t *) srcp)[2];
      len += 5;
      برو do2;
    حالت 4:
      srcp -= 4 * OPSIZ;
      dstp -= 3 * OPSIZ;
      a0 = ((op_t *) srcp)[3];
      len += 4;
      برو do3;
    حالت 5:
      srcp -= 5 * OPSIZ;
      dstp -= 4 * OPSIZ;
      a1 = ((op_t *) srcp)[4];
      len += 3;
      برو do4;
    حالت 6:
      srcp -= 6 * OPSIZ;
      dstp -= 5 * OPSIZ;
      a0 = ((op_t *) srcp)[5];
      len += 2;
      برو do5;
    حالت 7:
      srcp -= 7 * OPSIZ;
      dstp -= 6 * OPSIZ;
      a1 = ((op_t *) srcp)[6];
      len += 1;
      برو do6;

    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	بازگشت;
      srcp -= 8 * OPSIZ;
      dstp -= 7 * OPSIZ;
      a0 = ((op_t *) srcp)[7];
      برو do7;
    حالت 1:
      srcp -= 9 * OPSIZ;
      dstp -= 8 * OPSIZ;
      a1 = ((op_t *) srcp)[8];
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	برو do0;
      برو do8;			/* No-op.  */
    }

  انجامبده
    {
    do8:
      a0 = ((op_t *) srcp)[7];
      /* Check the comment on WORDCOPY_FWD_ALIGNED.  */
      DIAG_افزودن_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
      ((op_t *) dstp)[7] = a1;
      DIAG_برداشت_NEEDS_COMMENT;
    do7:
      a1 = ((op_t *) srcp)[6];
      ((op_t *) dstp)[6] = a0;
    do6:
      a0 = ((op_t *) srcp)[5];
      ((op_t *) dstp)[5] = a1;
    do5:
      a1 = ((op_t *) srcp)[4];
      ((op_t *) dstp)[4] = a0;
    do4:
      a0 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = a1;
    do3:
      a1 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = a0;
    do2:
      a0 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = a1;
    do1:
      a1 = ((op_t *) srcp)[0];
      ((op_t *) dstp)[0] = a0;

      srcp -= 8 * OPSIZ;
      dstp -= 8 * OPSIZ;
      len -= 8;
    }
  وقتی (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[7] = a1;
}

/* _wordcopy_bwd_dest_aligned -- Copy block finishing right
   before SRCP to block finishing right before DSTP with LEN `op_t'
   words (not LEN bytes!).  DSTP should be aligned for memory
   operations on `op_t', but SRCP must *not* be aligned.  */

#ifndef WORDCOPY_BWD_DEST_ALIGNED
# define WORDCOPY_BWD_DEST_ALIGNED _wordcopy_bwd_dest_aligned
#endif

تهی
WORDCOPY_BWD_DEST_ALIGNED (long صحیح dstp, long صحیح srcp, size_t len)
{
  op_t a0, a1, a2, a3;
  صحیح sh_1, sh_2;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp to make it aligned for copy.  */

  sh_1 = 8 * (srcp % OPSIZ);
  sh_2 = 8 * OPSIZ - sh_1;

  /* Make srcp aligned by rounding it down to the beginning of the op_t
     it points in the middle of.  */
  srcp &= -OPSIZ;
  srcp += OPSIZ;

  انتخاب (len % 4)
    {
    حالت 2:
      srcp -= 3 * OPSIZ;
      dstp -= 1 * OPSIZ;
      a2 = ((op_t *) srcp)[2];
      a1 = ((op_t *) srcp)[1];
      len += 2;
      برو do1;
    حالت 3:
      srcp -= 4 * OPSIZ;
      dstp -= 2 * OPSIZ;
      a3 = ((op_t *) srcp)[3];
      a2 = ((op_t *) srcp)[2];
      len += 1;
      برو do2;
    حالت 0:
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	بازگشت;
      srcp -= 5 * OPSIZ;
      dstp -= 3 * OPSIZ;
      a0 = ((op_t *) srcp)[4];
      a3 = ((op_t *) srcp)[3];
      برو do3;
    حالت 1:
      srcp -= 6 * OPSIZ;
      dstp -= 4 * OPSIZ;
      a1 = ((op_t *) srcp)[5];
      a0 = ((op_t *) srcp)[4];
      len -= 1;
      اگر (OP_T_THRES <= 3 * OPSIZ && len == 0)
	برو do0;
      برو do4;			/* No-op.  */
    }

  انجامبده
    {
    do4:
      a3 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = MERGE (a0, sh_1, a1, sh_2);
    do3:
      a2 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = MERGE (a3, sh_1, a0, sh_2);
    do2:
      a1 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = MERGE (a2, sh_1, a3, sh_2);
    do1:
      a0 = ((op_t *) srcp)[0];
      ((op_t *) dstp)[0] = MERGE (a1, sh_1, a2, sh_2);

      srcp -= 4 * OPSIZ;
      dstp -= 4 * OPSIZ;
      len -= 4;
    }
  وقتی (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[3] = MERGE (a0, sh_1, a1, sh_2);
}
