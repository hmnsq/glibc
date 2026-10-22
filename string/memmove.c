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

#شامل <string.h>
#شامل <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#اگر_غیر_تعریف_شدہ	a1
#تعریف_کرو	a1	dest	/* First arg is DEST.  */
#تعریف_کرو	a1const
#تعریف_کرو	a2	src	/* Second arg is SRC.  */
#تعریف_کرو	a2const	ثابت
#تعریف_منسوخ memmove
#اگر_ختم
#اگر	!defined(RETURN) || !defined(rettype)
#تعریف_کرو	RETURN(s)	واپس (s)	/* Return DEST.  */
#تعریف_کرو	rettype		خالی *
#اگر_ختم

#اگر_غیر_تعریف_شدہ MEMMOVE
#تعریف_کرو MEMMOVE memmove
#اگر_ختم

rettype
inhibit_loop_مقصد_libcall
MEMMOVE (a1const خالی *a1, a2const خالی *a2, size_t len)
{
  غیرعلامتی طویل صحیح dstp = (طویل صحیح) dest;
  غیرعلامتی طویل صحیح srcp = (طویل صحیح) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  اگر (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#اگر MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = حافظہ_نقل (dest, src, len);
#ورنہ
      /* If there not too few bytes to copy, use word copy.  */
      اگر (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  صفحہ_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  لفظ_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#اگر_ختم /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  ورنہ
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      اگر (len >= OP_T_THRES)
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
#اگر_غیر_تعریف_شدہ memmove
libc_hidden_builtin_def (memmove)
#اگر_ختم
