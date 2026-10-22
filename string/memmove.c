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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ	a1
#ವ್ಯಾಖ್ಯಾನಿಸು	a1	dest	/* First arg is DEST.  */
#ವ್ಯಾಖ್ಯಾನಿಸು	a1const
#ವ್ಯಾಖ್ಯಾನಿಸು	a2	src	/* Second arg is SRC.  */
#ವ್ಯಾಖ್ಯಾನಿಸು	a2const	ಸ್ಥಿರಾಂಕ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memmove
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ	!defined(RETURN) || !defined(rettype)
#ವ್ಯಾಖ್ಯಾನಿಸು	RETURN(s)	ಹಿಂತಿರುಗಿ (s)	/* Return DEST.  */
#ವ್ಯಾಖ್ಯಾನಿಸು	rettype		ಶೂನ್ಯ *
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMMOVE
#ವ್ಯಾಖ್ಯಾನಿಸು MEMMOVE memmove
#ಆದರೆ_ಅಂತ್ಯ

rettype
inhibit_loop_ಗಮ್ಯ_libcall
MEMMOVE (a1const ಶೂನ್ಯ *a1, a2const ಶೂನ್ಯ *a2, size_t len)
{
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ dstp = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) dest;
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  ಆದರೆ (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#ಆದರೆ MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = ಸ್ಮರಣೆ_ನಕಲು (dest, src, len);
#ಇಲ್ಲದಿದ್ದರೆ
      /* If there not too few bytes to copy, use word copy.  */
      ಆದರೆ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  ಪುಟ_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  ಶಬ್ದ_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#ಆದರೆ_ಅಂತ್ಯ /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      ಆದರೆ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= dstp % OPSIZ;
	  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  ಶಬ್ದ_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ memmove
libc_hidden_builtin_def (memmove)
#ಆದರೆ_ಅಂತ್ಯ
