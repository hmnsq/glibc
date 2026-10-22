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
#که_نه_تعریف_شوی	a1
#تعریف_کړه	a1	dest	/* First arg is DEST.  */
#تعریف_کړه	a1const
#تعریف_کړه	a2	src	/* Second arg is SRC.  */
#تعریف_کړه	a2const	ثابت
#تعریف_لغوه memmove
#د_که_پای
#إذا	!defined(RETURN) || !defined(rettype)
#تعریف_کړه	RETURN(s)	أرجع (s)	/* Return DEST.  */
#تعریف_کړه	rettype		فراغ *
#د_که_پای

#که_نه_تعریف_شوی MEMMOVE
#تعریف_کړه MEMMOVE memmove
#د_که_پای

rettype
inhibit_loop_منزل_libcall
MEMMOVE (a1const فراغ *a1, a2const فراغ *a2, size_t len)
{
  بینښه اوږد صحيح dstp = (اوږد صحيح) dest;
  بینښه اوږد صحيح srcp = (اوږد صحيح) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  إذا (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#إذا MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = حافظه_نقل (dest, src, len);
#وإلا
      /* If there not too few bytes to copy, use word copy.  */
      إذا (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  پاڼه_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  کلمه_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#د_که_پای /* MEMCPY_OK_FOR_FWD_MEMMOVE */
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

	  کلمه_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#که_نه_تعریف_شوی memmove
libc_hidden_builtin_def (memmove)
#د_که_پای
