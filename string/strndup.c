/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#यदि_परिभाषितम् HAVE_CONFIG_H
# include "config.h"
#यदि_अन्तः

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <sys/types.h>

#यदि defined _LIBC || defined STDC_शीर्षकाणि
# include <stdlib.h>
# include <string.h>
#अन्यथा
वर्ण *स्मृतिं_देहि ();
#यदि_अन्तः

#अपरिभाषय __strndup
#अपरिभाषय strndup

#यदि_अपरिभाषितम् weak_alias
# define __strndup strndup
#यदि_अन्तः

वर्ण *
__strndup (ध्रुव वर्ण *s, size_t n)
{
  size_t len = __strnlen (s, n);
  वर्ण *new = (वर्ण *) स्मृतिं_देहि (len + 1);

  यदि (new == रिक्त)
    प्रत्यागम रिक्त;

  new[len] = '\0';
  प्रत्यागम (वर्ण *) स्मृतिं_प्रतिलिख (new, s, len);
}
#यदि_परिभाषितम् libc_hidden_def
libc_hidden_def (__strndup)
#यदि_अन्तः
#यदि_परिभाषितम् weak_alias
weak_alias (__strndup, strndup)
#यदि_अन्तः
