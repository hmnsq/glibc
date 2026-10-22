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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>
/* Compiling with -O1 might warn that 'a2' and 'a3' may be used
   uninitialized.  There are only two ways to arrive at labels 'do4', 'do3'
   or 'do1', all of which use 'a2' or 'a3' in the MERGE macro: either from
   the earlier switch case statement or via a loop iteration.  In all cases
   the switch statement or previous loop sets both 'a2' and 'a3'.

   Since the usage is within the MERGE macro we disable the
   warning in the definition, but only in this file.  */
DIAG_ਧੱਕੋ_NEEDS_COMMENT;
DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
#ਅਨ੍ਤਰ੍ਭਾਵ <memcopy.h>
DIAG_ਕੱਢੋ_NEEDS_COMMENT;

/* _wordcopy_fwd_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   Both SRCP and DSTP should be aligned for memory operations on `op_t's.  */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WORDCOPY_FWD_ALIGNED
# define WORDCOPY_FWD_ALIGNED _wordcopy_fwd_aligned
#ਜੇ_ਅੰਤ

ਖਾਲੀ
WORDCOPY_FWD_ALIGNED (ਲੰਮਾ ਪੂਰਨ dstp, ਲੰਮਾ ਪੂਰਨ srcp, size_t len)
{
  op_t a0, a1;

  ਚੋਣ (len % 8)
    {
    ਹਾਲਤ 2:
      a0 = ((op_t *) srcp)[0];
      srcp -= 6 * OPSIZ;
      dstp -= 7 * OPSIZ;
      len += 6;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      a1 = ((op_t *) srcp)[0];
      srcp -= 5 * OPSIZ;
      dstp -= 6 * OPSIZ;
      len += 5;
      ਜਾਓ do2;
    ਹਾਲਤ 4:
      a0 = ((op_t *) srcp)[0];
      srcp -= 4 * OPSIZ;
      dstp -= 5 * OPSIZ;
      len += 4;
      ਜਾਓ do3;
    ਹਾਲਤ 5:
      a1 = ((op_t *) srcp)[0];
      srcp -= 3 * OPSIZ;
      dstp -= 4 * OPSIZ;
      len += 3;
      ਜਾਓ do4;
    ਹਾਲਤ 6:
      a0 = ((op_t *) srcp)[0];
      srcp -= 2 * OPSIZ;
      dstp -= 3 * OPSIZ;
      len += 2;
      ਜਾਓ do5;
    ਹਾਲਤ 7:
      a1 = ((op_t *) srcp)[0];
      srcp -= 1 * OPSIZ;
      dstp -= 2 * OPSIZ;
      len += 1;
      ਜਾਓ do6;

    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ;
      a0 = ((op_t *) srcp)[0];
      srcp -= 0 * OPSIZ;
      dstp -= 1 * OPSIZ;
      ਜਾਓ do7;
    ਹਾਲਤ 1:
      a1 = ((op_t *) srcp)[0];
      srcp -=-1 * OPSIZ;
      dstp -= 0 * OPSIZ;
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      ਜਾਓ do8;			/* No-op.  */
    }

  ਕਰੋ
    {
    do8:
      a0 = ((op_t *) srcp)[0];
      /* Compiling with -O1 may warn that 'a1' may be used uninitialized.
	 There are only two ways to arrive at label 'do8' and they are via a
	 do-while loop iteration or directly via the earlier switch 'case 1:'
	 case. The switch case always sets 'a1' and all previous loop
	 iterations will also have set 'a1' before the use.  */
      DIAG_ਧੱਕੋ_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
      ((op_t *) dstp)[0] = a1;
      DIAG_ਕੱਢੋ_NEEDS_COMMENT;
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
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[0] = a1;
}

/* _wordcopy_fwd_dest_aligned -- Copy block beginning at SRCP to
   block beginning at DSTP with LEN `op_t' words (not LEN bytes!).
   DSTP should be aligned for memory operations on `op_t's, but SRCP must
   *not* be aligned.  */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WORDCOPY_FWD_DEST_ALIGNED
# define WORDCOPY_FWD_DEST_ALIGNED _wordcopy_fwd_dest_aligned
#ਜੇ_ਅੰਤ

ਖਾਲੀ
WORDCOPY_FWD_DEST_ALIGNED (ਲੰਮਾ ਪੂਰਨ dstp, ਲੰਮਾ ਪੂਰਨ srcp, size_t len)
{
  op_t a0, a1, a2, a3;
  ਪੂਰਨ sh_1, sh_2;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp to make it aligned for copy.  */

  sh_1 = 8 * (srcp % OPSIZ);
  sh_2 = 8 * OPSIZ - sh_1;

  /* Make SRCP aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp &= -OPSIZ;

  ਚੋਣ (len % 4)
    {
    ਹਾਲਤ 2:
      a1 = ((op_t *) srcp)[0];
      a2 = ((op_t *) srcp)[1];
      srcp -= 1 * OPSIZ;
      dstp -= 3 * OPSIZ;
      len += 2;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      a0 = ((op_t *) srcp)[0];
      a1 = ((op_t *) srcp)[1];
      srcp -= 0 * OPSIZ;
      dstp -= 2 * OPSIZ;
      len += 1;
      ਜਾਓ do2;
    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ;
      a3 = ((op_t *) srcp)[0];
      a0 = ((op_t *) srcp)[1];
      srcp -=-1 * OPSIZ;
      dstp -= 1 * OPSIZ;
      len += 0;
      ਜਾਓ do3;
    ਹਾਲਤ 1:
      a2 = ((op_t *) srcp)[0];
      a3 = ((op_t *) srcp)[1];
      srcp -=-2 * OPSIZ;
      dstp -= 0 * OPSIZ;
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      ਜਾਓ do4;			/* No-op.  */
    }

  ਕਰੋ
    {
    do4:
      a0 = ((op_t *) srcp)[0];
      ((op_t *) dstp)[0] = ਮਿਲਾਓ (a2, sh_1, a3, sh_2);
    do3:
      a1 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = ਮਿਲਾਓ (a3, sh_1, a0, sh_2);
    do2:
      a2 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = ਮਿਲਾਓ (a0, sh_1, a1, sh_2);
    do1:
      a3 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = ਮਿਲਾਓ (a1, sh_1, a2, sh_2);

      srcp += 4 * OPSIZ;
      dstp += 4 * OPSIZ;
      len -= 4;
    }
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[0] = ਮਿਲਾਓ (a2, sh_1, a3, sh_2);
}

/* _wordcopy_bwd_aligned -- Copy block finishing right before
   SRCP to block finishing right before DSTP with LEN `op_t' words
   (not LEN bytes!).  Both SRCP and DSTP should be aligned for memory
   operations on `op_t's.  */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WORDCOPY_BWD_ALIGNED
# define WORDCOPY_BWD_ALIGNED _wordcopy_bwd_aligned
#ਜੇ_ਅੰਤ

ਖਾਲੀ
WORDCOPY_BWD_ALIGNED (ਲੰਮਾ ਪੂਰਨ dstp, ਲੰਮਾ ਪੂਰਨ srcp, size_t len)
{
  op_t a0, a1;

  ਚੋਣ (len % 8)
    {
    ਹਾਲਤ 2:
      srcp -= 2 * OPSIZ;
      dstp -= 1 * OPSIZ;
      a0 = ((op_t *) srcp)[1];
      len += 6;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      srcp -= 3 * OPSIZ;
      dstp -= 2 * OPSIZ;
      a1 = ((op_t *) srcp)[2];
      len += 5;
      ਜਾਓ do2;
    ਹਾਲਤ 4:
      srcp -= 4 * OPSIZ;
      dstp -= 3 * OPSIZ;
      a0 = ((op_t *) srcp)[3];
      len += 4;
      ਜਾਓ do3;
    ਹਾਲਤ 5:
      srcp -= 5 * OPSIZ;
      dstp -= 4 * OPSIZ;
      a1 = ((op_t *) srcp)[4];
      len += 3;
      ਜਾਓ do4;
    ਹਾਲਤ 6:
      srcp -= 6 * OPSIZ;
      dstp -= 5 * OPSIZ;
      a0 = ((op_t *) srcp)[5];
      len += 2;
      ਜਾਓ do5;
    ਹਾਲਤ 7:
      srcp -= 7 * OPSIZ;
      dstp -= 6 * OPSIZ;
      a1 = ((op_t *) srcp)[6];
      len += 1;
      ਜਾਓ do6;

    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ;
      srcp -= 8 * OPSIZ;
      dstp -= 7 * OPSIZ;
      a0 = ((op_t *) srcp)[7];
      ਜਾਓ do7;
    ਹਾਲਤ 1:
      srcp -= 9 * OPSIZ;
      dstp -= 8 * OPSIZ;
      a1 = ((op_t *) srcp)[8];
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      ਜਾਓ do8;			/* No-op.  */
    }

  ਕਰੋ
    {
    do8:
      a0 = ((op_t *) srcp)[7];
      /* Check the comment on WORDCOPY_FWD_ALIGNED.  */
      DIAG_ਧੱਕੋ_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_GCC (6, "-Wmaybe-uninitialized");
      ((op_t *) dstp)[7] = a1;
      DIAG_ਕੱਢੋ_NEEDS_COMMENT;
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
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[7] = a1;
}

/* _wordcopy_bwd_dest_aligned -- Copy block finishing right
   before SRCP to block finishing right before DSTP with LEN `op_t'
   words (not LEN bytes!).  DSTP should be aligned for memory
   operations on `op_t', but SRCP must *not* be aligned.  */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WORDCOPY_BWD_DEST_ALIGNED
# define WORDCOPY_BWD_DEST_ALIGNED _wordcopy_bwd_dest_aligned
#ਜੇ_ਅੰਤ

ਖਾਲੀ
WORDCOPY_BWD_DEST_ALIGNED (ਲੰਮਾ ਪੂਰਨ dstp, ਲੰਮਾ ਪੂਰਨ srcp, size_t len)
{
  op_t a0, a1, a2, a3;
  ਪੂਰਨ sh_1, sh_2;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp to make it aligned for copy.  */

  sh_1 = 8 * (srcp % OPSIZ);
  sh_2 = 8 * OPSIZ - sh_1;

  /* Make srcp aligned by rounding it down to the beginning of the op_t
     it points in the middle of.  */
  srcp &= -OPSIZ;
  srcp += OPSIZ;

  ਚੋਣ (len % 4)
    {
    ਹਾਲਤ 2:
      srcp -= 3 * OPSIZ;
      dstp -= 1 * OPSIZ;
      a2 = ((op_t *) srcp)[2];
      a1 = ((op_t *) srcp)[1];
      len += 2;
      ਜਾਓ do1;
    ਹਾਲਤ 3:
      srcp -= 4 * OPSIZ;
      dstp -= 2 * OPSIZ;
      a3 = ((op_t *) srcp)[3];
      a2 = ((op_t *) srcp)[2];
      len += 1;
      ਜਾਓ do2;
    ਹਾਲਤ 0:
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਵਾਪਸ;
      srcp -= 5 * OPSIZ;
      dstp -= 3 * OPSIZ;
      a0 = ((op_t *) srcp)[4];
      a3 = ((op_t *) srcp)[3];
      ਜਾਓ do3;
    ਹਾਲਤ 1:
      srcp -= 6 * OPSIZ;
      dstp -= 4 * OPSIZ;
      a1 = ((op_t *) srcp)[5];
      a0 = ((op_t *) srcp)[4];
      len -= 1;
      ਜੇ (OP_T_THRES <= 3 * OPSIZ && len == 0)
	ਜਾਓ do0;
      ਜਾਓ do4;			/* No-op.  */
    }

  ਕਰੋ
    {
    do4:
      a3 = ((op_t *) srcp)[3];
      ((op_t *) dstp)[3] = ਮਿਲਾਓ (a0, sh_1, a1, sh_2);
    do3:
      a2 = ((op_t *) srcp)[2];
      ((op_t *) dstp)[2] = ਮਿਲਾਓ (a3, sh_1, a0, sh_2);
    do2:
      a1 = ((op_t *) srcp)[1];
      ((op_t *) dstp)[1] = ਮਿਲਾਓ (a2, sh_1, a3, sh_2);
    do1:
      a0 = ((op_t *) srcp)[0];
      ((op_t *) dstp)[0] = ਮਿਲਾਓ (a1, sh_1, a2, sh_2);

      srcp -= 4 * OPSIZ;
      dstp -= 4 * OPSIZ;
      len -= 4;
    }
  ਜਦੋਂ (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  ((op_t *) dstp)[3] = ਮਿਲਾਓ (a0, sh_1, a1, sh_2);
}
