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

#अगर_अघोषित _ARGZ_H
#घोषणा _ARGZ_H	1

#समावेश <features.h>
#समावेश <errno.h>
#समावेश <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#अगर_अघोषित __error_t_defined
# define __error_t_defined 1
प्रकार पूर्णांक error_t;
#पूर्ण_अगर

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
बाह्य error_t __argz_create (अक्षर *स्थिर __argv[], अक्षर **__restrict __argz,
			      माप_प्रकार *__restrict __len) __THROW;
बाह्य error_t argz_create (अक्षर *स्थिर __argv[], अक्षर **__restrict __argz,
			    माप_प्रकार *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
बाह्य error_t argz_create_sep (स्थिर अक्षर *__restrict __string,
				पूर्णांक __sep, अक्षर **__restrict __argz,
				माप_प्रकार *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
बाह्य माप_प्रकार __argz_count (स्थिर अक्षर *__argz, माप_प्रकार __len)
     __THROW __attribute_pure__;
बाह्य माप_प्रकार argz_गिनती (स्थिर अक्षर *__argz, माप_प्रकार __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
बाह्य व्योम __argz_extract (स्थिर अक्षर *__restrict __argz, माप_प्रकार __len,
			    अक्षर **__restrict __argv) __THROW;
बाह्य व्योम argz_extract (स्थिर अक्षर *__restrict __argz, माप_प्रकार __len,
			  अक्षर **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
बाह्य व्योम __argz_stringify (अक्षर *__argz, माप_प्रकार __len, पूर्णांक __sep) __THROW;
बाह्य व्योम argz_stringify (अक्षर *__argz, माप_प्रकार __len, पूर्णांक __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
बाह्य error_t argz_append (अक्षर **__restrict __argz,
			    माप_प्रकार *__restrict __argz_len,
			    स्थिर अक्षर *__restrict __buf, माप_प्रकार __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
बाह्य error_t argz_add (अक्षर **__restrict __argz,
			 माप_प्रकार *__restrict __argz_len,
			 स्थिर अक्षर *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
बाह्य error_t argz_add_sep (अक्षर **__restrict __argz,
			     माप_प्रकार *__restrict __argz_len,
			     स्थिर अक्षर *__restrict __string, पूर्णांक __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
बाह्य व्योम argz_delete (अक्षर **__restrict __argz,
			 माप_प्रकार *__restrict __argz_len,
			 अक्षर *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
बाह्य error_t argz_जोड़ो (अक्षर **__restrict __argz,
			    माप_प्रकार *__restrict __argz_len,
			    अक्षर *__restrict __before,
			    स्थिर अक्षर *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
बाह्य error_t argz_replace (अक्षर **__restrict __argz,
			     माप_प्रकार *__restrict __argz_len,
			     स्थिर अक्षर *__restrict __str,
			     स्थिर अक्षर *__restrict __with,
			     अचिन्हित पूर्णांक *__restrict __replace_count);

/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
   are no more.  If entry is NULL, then the first entry is returned.  This
   behavior allows two convenient iteration styles:

    char *entry = 0;
    while ((entry = argz_next (argz, argz_len, entry)))
      ...;

   or

    char *entry;
    for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
      ...;
*/
बाह्य अक्षर *__argz_next (स्थिर अक्षर *__restrict __argz, माप_प्रकार __argz_len,
			  स्थिर अक्षर *__restrict __entry) __THROW;
बाह्य अक्षर *argz_अग्र (स्थिर अक्षर *__restrict __argz, माप_प्रकार __argz_len,
			स्थिर अक्षर *__restrict __entry) __THROW;

#अगर_घोषित __USE_EXTERN_INLINES
__extern_inline अक्षर *
__NTH (__argz_next (स्थिर अक्षर *__argz, माप_प्रकार __argz_len,
		    स्थिर अक्षर *__entry))
{
  अगर (__entry)
    {
      अगर (__entry < __argz + __argz_len)
	__entry = म_अक्षर (__entry, '\0') + 1;

      वापस __entry >= __argz + __argz_len ? (अक्षर *) शून्य : (अक्षर *) __entry;
    }
  अन्यथा
    वापस __argz_len > 0 ? (अक्षर *) __argz : शून्य;
}
__extern_inline अक्षर *
__NTH (argz_अग्र (स्थिर अक्षर *__argz, माप_प्रकार __argz_len,
		  स्थिर अक्षर *__entry))
{
  वापस __argz_next (__argz, __argz_len, __entry);
}
#पूर्ण_अगर /* Use extern inlines.  */

__END_DECLS

#पूर्ण_अगर /* argz.h */
