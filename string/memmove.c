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

#समावेश <string.h>
#समावेश <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#अगर_अघोषित	a1
#घोषणा	a1	dest	/* First arg is DEST.  */
#घोषणा	a1const
#घोषणा	a2	src	/* Second arg is SRC.  */
#घोषणा	a2const	स्थिर
#अघोषित स_हटाओ
#पूर्ण_अगर
#अगर	!defined(RETURN) || !defined(rettype)
#घोषणा	RETURN(s)	वापस (s)	/* Return DEST.  */
#घोषणा	rettype		व्योम *
#पूर्ण_अगर

#अगर_अघोषित MEMMOVE
#घोषणा MEMMOVE स_हटाओ
#पूर्ण_अगर

rettype
inhibit_loop_to_libcall
MEMMOVE (a1const व्योम *a1, a2const व्योम *a2, माप_प्रकार len)
{
  अचिन्हित दीर्घ पूर्णांक dstp = (दीर्घ पूर्णांक) dest;
  अचिन्हित दीर्घ पूर्णांक srcp = (दीर्घ पूर्णांक) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  अगर (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#अगर MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = स_नकल (dest, src, len);
#अन्यथा
      /* If there not too few bytes to copy, use word copy.  */
      अगर (len >= OP_T_THRES)
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
#पूर्ण_अगर /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  अन्यथा
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      अगर (len >= OP_T_THRES)
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
#अगर_अघोषित स_हटाओ
libc_hidden_builtin_def (स_हटाओ)
#पूर्ण_अगर
