/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMSET
# define MEMSET memset
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ *
inhibit_loop_ಗಮ್ಯ_libcall
MEMSET (ಶೂನ್ಯ *dstpp, ಪೂರ್ಣಾಂಕ c, size_t len)
{
  ದೀರ್ಘ ಪೂರ್ಣಾಂಕ dstp = (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ) dstpp;

  ಆದರೆ (len >= 8)
    {
      size_t xlen;
      op_t cccc;

      cccc = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) c;
      cccc |= cccc << 8;
      cccc |= cccc << 16;
      ಆದರೆ (OPSIZ > 4)
	/* Do the shift in two steps to avoid warning if long has 32 bits.  */
	cccc |= (cccc << 16) << 16;

      /* There are at least some bytes to set.
	 No need to test for LEN == 0 in this alignment loop.  */
      ಆಗ (dstp % OPSIZ != 0)
	{
	  ((byte *) dstp)[0] = c;
	  dstp += 1;
	  len -= 1;
	}

      /* Write 8 `op_t' per iteration until less than 8 `op_t' remain.  */
      xlen = len / (OPSIZ * 8);
      ಆಗ (xlen > 0)
	{
	  ((op_t *) dstp)[0] = cccc;
	  ((op_t *) dstp)[1] = cccc;
	  ((op_t *) dstp)[2] = cccc;
	  ((op_t *) dstp)[3] = cccc;
	  ((op_t *) dstp)[4] = cccc;
	  ((op_t *) dstp)[5] = cccc;
	  ((op_t *) dstp)[6] = cccc;
	  ((op_t *) dstp)[7] = cccc;
	  dstp += 8 * OPSIZ;
	  xlen -= 1;
	}
      len %= OPSIZ * 8;

      /* Write 1 `op_t' per iteration until less than OPSIZ bytes remain.  */
      xlen = len / OPSIZ;
      ಆಗ (xlen > 0)
	{
	  ((op_t *) dstp)[0] = cccc;
	  dstp += OPSIZ;
	  xlen -= 1;
	}
      len %= OPSIZ;
    }

  /* Write the last few bytes.  */
  ಆಗ (len > 0)
    {
      ((byte *) dstp)[0] = c;
      dstp += 1;
      len -= 1;
    }

  ಹಿಂತಿರುಗಿ dstpp;
}
libc_hidden_builtin_def (MEMSET)
