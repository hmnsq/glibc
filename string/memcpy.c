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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <memcopy.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMCPY
# define MEMCPY ಸ್ಮರಣೆ_ನಕಲು
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ *
MEMCPY (ಶೂನ್ಯ *dstpp, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *srcpp, size_t len)
{
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ dstp = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) dstpp;
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ srcp = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) srcpp;

  /* Copy from the beginning to the end.  */

  /* If there not too few bytes to copy, use word copy.  */
  ಆದರೆ (len >= OP_T_THRES)
    {
      /* Copy just a few bytes to make DSTP aligned.  */
      len -= (-dstp) % OPSIZ;
      BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

      /* Copy whole pages from SRCP to DSTP by virtual address manipulation,
	 as much as possible.  */

      ಪುಟ_COPY_FWD_MAYBE (dstp, srcp, len, len);

      /* Copy from SRCP to DSTP taking advantage of the known alignment of
	 DSTP.  Number of bytes remaining is put in the third argument,
	 i.e. in LEN.  This number may vary from machine to machine.  */

      ಶಬ್ದ_COPY_FWD (dstp, srcp, len, len);

      /* Fall out and copy the tail.  */
    }

  /* There are just a few bytes to copy.  Use byte memory operations.  */
  BYTE_COPY_FWD (dstp, srcp, len);

  ಹಿಂತಿರುಗಿ dstpp;
}
libc_hidden_builtin_def (MEMCPY)
