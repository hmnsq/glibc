/* Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRING_TYPE
# define STRING_TYPE ಅಕ್ಷರ
# define STRCOLL strcoll
# define STRCOLL_L __strcoll_l
# define USE_HIDDEN_DEF
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../locale/localeinfo.h"


ಪೂರ್ಣಾಂಕ
STRCOLL (ಸ್ಥಿರಾಂಕ STRING_TYPE *s1, ಸ್ಥಿರಾಂಕ STRING_TYPE *s2)
{
  ಹಿಂತಿರುಗಿ STRCOLL_L (s1, s2, _NL_CURRENT_LOCALE);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_HIDDEN_DEF
libc_hidden_def (STRCOLL)
#ಆದರೆ_ಅಂತ್ಯ
