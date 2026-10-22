/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#ಅನ್ತರ್ಭಾವ <argz.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
ಶೂನ್ಯ
argz_delete (ಅಕ್ಷರ **argz, size_t *argz_len, ಅಕ್ಷರ *ನಮೂದು)
{
  ಆದರೆ (ನಮೂದು)
    /* Get rid of the old value for NAME.  */
    {
      size_t ನಮೂದು_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ನಮೂದು) + 1;
      *argz_len -= ನಮೂದು_len;
      memmove (ನಮೂದು, ನಮೂದು + ನಮೂದು_len, *argz_len - (ನಮೂದು - *argz));
      ಆದರೆ (*argz_len == 0)
	{
	  ಬಿಡುಗಡೆ (*argz);
	  *argz = ಖಾಲಿ;
	}
    }
}
libc_hidden_def (argz_delete)
