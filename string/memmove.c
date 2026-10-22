/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is handled correctly.
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

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#جيڪڏهن_وصف_نه_ٿيل	a1
#وصف_ڪريو	a1	dest	/* First arg is DEST.  */
#وصف_ڪريو	a1const
#وصف_ڪريو	a2	src	/* Second arg is SRC.  */
#وصف_ڪريو	a2const	ثابت
#وصف_رد memmove
#جيڪڏهن_پورو
#إذا	!defined(RETURN) || !defined(rettype)
#وصف_ڪريو	RETURN(s)	أرجع (s)	/* Return DEST.  */
#وصف_ڪريو	rettype		فراغ *
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل MEMMOVE
#وصف_ڪريو MEMMOVE memmove
#جيڪڏهن_پورو

rettype
inhibit_loop_منزل_libcall
MEMMOVE (a1const فراغ *a1, a2const فراغ *a2, size_t len)
{
  بنانشان ڊگهو صحيح dstp = (ڊگهو صحيح) dest;
  بنانشان ڊگهو صحيح srcp = (ڊگهو صحيح) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  إذا (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#إذا MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = يادگيري_نقل (dest, src, len);
#وإلا
      /* If there not too few bytes to copy, use word copy.  */
      إذا (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  صفحو_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  لفظ_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#جيڪڏهن_پورو /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  وإلا
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      إذا (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= dstp % OPSIZ;
	  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  لفظ_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#جيڪڏهن_وصف_نه_ٿيل memmove
libc_hidden_builtin_def (memmove)
#جيڪڏهن_پورو
