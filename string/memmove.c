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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#ifndef	a1
#define	a1	dest	/* First arg is DEST.  */
#define	a1const
#define	a2	src	/* Second arg is SRC.  */
#define	a2const	സ്ഥിരം
#undef memmove
#endif
#എങ്കിൽ	!defined(RETURN) || !defined(rettype)
#define	RETURN(s)	തിരികെ (s)	/* Return DEST.  */
#define	rettype		ശൂന്യം *
#endif

#ifndef MEMMOVE
#define MEMMOVE memmove
#endif

rettype
inhibit_loop_to_libcall
MEMMOVE (a1const ശൂന്യം *a1, a2const ശൂന്യം *a2, size_t len)
{
  unsigned long പൂർണ്ണസംഖ്യ dstp = (long പൂർണ്ണസംഖ്യ) dest;
  unsigned long പൂർണ്ണസംഖ്യ srcp = (long പൂർണ്ണസംഖ്യ) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  എങ്കിൽ (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#എങ്കിൽ MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = memcpy (dest, src, len);
#അല്ലെങ്കിൽ
      /* If there not too few bytes to copy, use word copy.  */
      എങ്കിൽ (len >= OP_T_THRES)
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
#endif /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  അല്ലെങ്കിൽ
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      എങ്കിൽ (len >= OP_T_THRES)
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
#ifndef memmove
libc_hidden_builtin_def (memmove)
#endif
