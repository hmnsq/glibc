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

#अन्तर्भाव <string.h>
#अन्तर्भाव <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#यदि_अपरिभाषितम्	a1
#परिभाषय	a1	dest	/* First arg is DEST.  */
#परिभाषय	a1const
#परिभाषय	a2	src	/* Second arg is SRC.  */
#परिभाषय	a2const	ध्रुव
#अपरिभाषय memmove
#यदि_अन्तः
#यदि	!defined(RETURN) || !defined(rettype)
#परिभाषय	RETURN(s)	प्रत्यागम (s)	/* Return DEST.  */
#परिभाषय	rettype		शून्य *
#यदि_अन्तः

#यदि_अपरिभाषितम् MEMMOVE
#परिभाषय MEMMOVE memmove
#यदि_अन्तः

rettype
inhibit_loop_गन्तव्यम्_libcall
MEMMOVE (a1const शून्य *a1, a2const शून्य *a2, size_t len)
{
  अचिह्नित दीर्घ पूर्णाङ्क dstp = (दीर्घ पूर्णाङ्क) dest;
  अचिह्नित दीर्घ पूर्णाङ्क srcp = (दीर्घ पूर्णाङ्क) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  यदि (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#यदि MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = स्मृतिं_प्रतिलिख (dest, src, len);
#अन्यथा
      /* If there not too few bytes to copy, use word copy.  */
      यदि (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  WORD_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#यदि_अन्तः /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  अन्यथा
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      यदि (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= dstp % OPSIZ;
	  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  WORD_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#यदि_अपरिभाषितम् memmove
libc_hidden_builtin_def (memmove)
#यदि_अन्तः
