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

#अगर_घोषित HAVE_CONFIG_H
#समावेश <config.h>
#पूर्ण_अगर

#अगर defined _LIBC || defined  STDC_HEADERS
# include <stdlib.h>
# include <string.h>
#अन्यथा
अक्षर *दो_स्मृति ();
अक्षर *स_नकल ();
#पूर्ण_अगर

#अघोषित __strdup
#अघोषित strdup

#अगर_अघोषित weak_alias
# define __strdup strdup
#पूर्ण_अगर

/* Duplicate S, returning an identical malloc'd string.  */
अक्षर *
__strdup (स्थिर अक्षर *s)
{
  माप_प्रकार len = म_माप (s) + 1;
  व्योम *new = दो_स्मृति (len);

  अगर (new == शून्य)
    वापस शून्य;

  वापस (अक्षर *) स_नकल (new, s, len);
}
#अगर_घोषित libc_hidden_def
libc_hidden_def (__strdup)
#पूर्ण_अगर
#अगर_घोषित weak_alias
weak_alias (__strdup, strdup)
#पूर्ण_अगर
