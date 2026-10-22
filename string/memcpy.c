/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is NOT handled correctly.
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

#ضمن <string.h>
#ضمن <memcopy.h>

#که_نه_تعریف_شوی MEMCPY
# define MEMCPY حافظه_نقل
#د_که_پای

فراغ *
MEMCPY (فراغ *dstpp, ثابت فراغ *srcpp, size_t len)
{
  بینښه اوږد صحيح dstp = (اوږد صحيح) dstpp;
  بینښه اوږد صحيح srcp = (اوږد صحيح) srcpp;

  /* Copy from the beginning to the end.  */

  /* If there not too few bytes to copy, use word copy.  */
  إذا (len >= OP_T_THRES)
    {
      /* Copy just a few bytes to make DSTP aligned.  */
      len -= (-dstp) % OPSIZ;
      BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

      /* Copy whole pages from SRCP to DSTP by virtual address manipulation,
	 as much as possible.  */

      پاڼه_COPY_FWD_MAYBE (dstp, srcp, len, len);

      /* Copy from SRCP to DSTP taking advantage of the known alignment of
	 DSTP.  Number of bytes remaining is put in the third argument,
	 i.e. in LEN.  This number may vary from machine to machine.  */

      کلمه_COPY_FWD (dstp, srcp, len, len);

      /* Fall out and copy the tail.  */
    }

  /* There are just a few bytes to copy.  Use byte memory operations.  */
  BYTE_COPY_FWD (dstp, srcp, len);

  أرجع dstpp;
}
libc_hidden_builtin_def (MEMCPY)
