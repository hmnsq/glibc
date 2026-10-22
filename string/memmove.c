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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ	a1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	a1	dest	/* First arg is DEST.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	a1const
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	a2	src	/* Second arg is SRC.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	a2const	ਅਚਲ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memmove
#ਜੇ_ਅੰਤ
#ਜੇ	!defined(RETURN) || !defined(rettype)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	RETURN(s)	ਵਾਪਸ (s)	/* Return DEST.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	rettype		ਖਾਲੀ *
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMMOVE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MEMMOVE memmove
#ਜੇ_ਅੰਤ

rettype
inhibit_loop_ਮੰਜ਼ਿਲ_libcall
MEMMOVE (a1const ਖਾਲੀ *a1, a2const ਖਾਲੀ *a2, size_t len)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਪੂਰਨ dstp = (ਲੰਮਾ ਪੂਰਨ) dest;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਪੂਰਨ srcp = (ਲੰਮਾ ਪੂਰਨ) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  ਜੇ (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#ਜੇ MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = ਸਮ੍ਰਿਤੀ_ਨਕਲ (dest, src, len);
#ਨਹੀਂਤਾਂ
      /* If there not too few bytes to copy, use word copy.  */
      ਜੇ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  ਪੰਨਾ_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  ਸ਼ਬਦ_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#ਜੇ_ਅੰਤ /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  ਨਹੀਂਤਾਂ
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      ਜੇ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= dstp % OPSIZ;
	  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  ਸ਼ਬਦ_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ memmove
libc_hidden_builtin_def (memmove)
#ਜੇ_ਅੰਤ
