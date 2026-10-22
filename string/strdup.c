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

#यदि_परिभाषितम् HAVE_CONFIG_H
#अन्तर्भाव <config.h>
#यदि_अन्तः

#यदि defined _LIBC || defined  STDC_शीर्षकाणि
# include <stdlib.h>
# include <string.h>
#अन्यथा
वर्ण *स्मृतिं_देहि ();
वर्ण *स्मृतिं_प्रतिलिख ();
#यदि_अन्तः

#अपरिभाषय __strdup
#अपरिभाषय strdup

#यदि_अपरिभाषितम् weak_alias
# define __strdup strdup
#यदि_अन्तः

/* Duplicate S, returning an identical malloc'd string.  */
वर्ण *
__strdup (ध्रुव वर्ण *s)
{
  size_t len = वाक्यदैर्घ्यम् (s) + 1;
  शून्य *new = स्मृतिं_देहि (len);

  यदि (new == रिक्त)
    प्रत्यागम रिक्त;

  प्रत्यागम (वर्ण *) स्मृतिं_प्रतिलिख (new, s, len);
}
#यदि_परिभाषितम् libc_hidden_def
libc_hidden_def (__strdup)
#यदि_अन्तः
#यदि_परिभाषितम् weak_alias
weak_alias (__strdup, strdup)
#यदि_अन्तः
