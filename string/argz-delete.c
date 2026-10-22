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

#అన్తర్భావ <argz.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <stdlib.h>

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
శూన్య
argz_delete (అక్షరం **argz, size_t *argz_len, అక్షరం *నమోదు_2)
{
  ఒకవేళ (నమోదు_2)
    /* Get rid of the old value for NAME.  */
    {
      size_t నమోదు_len = అక్షరశ్రేణి_పొడవు (నమోదు_2) + 1;
      *argz_len -= నమోదు_len;
      memmove (నమోదు_2, నమోదు_2 + నమోదు_len, *argz_len - (నమోదు_2 - *argz));
      ఒకవేళ (*argz_len == 0)
	{
	  విడుదల (*argz);
	  *argz = ఖాళీ;
	}
    }
}
libc_hidden_def (argz_delete)
