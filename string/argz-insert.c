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

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
error_t
__argz_insert (ಅಕ್ಷರ **argz, size_t *argz_len, ಅಕ್ಷರ *before, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ನಮೂದು)
{
  ಆದರೆ (! before)
    ಹಿಂತಿರುಗಿ __argz_add (argz, argz_len, ನಮೂದು);

  ಆದರೆ (before < *argz || before >= *argz + *argz_len)
    ಹಿಂತಿರುಗಿ EINVAL;

  ಆದರೆ (before > *argz)
    /* Make sure before is actually the beginning of an entry.  */
    ಆಗ (before[-1])
      before--;

  {
    size_t after_before = *argz_len - (before - *argz);
    size_t ನಮೂದು_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ  (ನಮೂದು) + 1;
    size_t new_argz_len = *argz_len + ನಮೂದು_len;
    ಅಕ್ಷರ *new_argz = realloc (*argz, new_argz_len);

    ಆದರೆ (new_argz)
      {
	before = new_argz + (before - *argz);
	memmove (before + ನಮೂದು_len, before, after_before);
	memmove (before, ನಮೂದು, ನಮೂದು_len);
	*argz = new_argz;
	*argz_len = new_argz_len;
	ಹಿಂತಿರುಗಿ 0;
      }
    ಇಲ್ಲದಿದ್ದರೆ
      ಹಿಂತಿರುಗಿ ENOMEM;
  }
}
weak_alias (__argz_insert, argz_ಸೇರಿಸು)
