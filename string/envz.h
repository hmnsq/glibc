/* Routines for dealing with '\0' separated environment vectors
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

#अगर_अघोषित _ENVZ_H
#घोषणा _ENVZ_H	1

#समावेश <features.h>

#समावेश <errno.h>

/* Envz's are argz's too, and should be created etc., using the same
   routines.  */
#समावेश <argz.h>

__BEGIN_DECLS

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.  */
बाह्य अक्षर *envz_entry (स्थिर अक्षर *__restrict __envz, माप_प्रकार __envz_len,
			 स्थिर अक्षर *__restrict __name)
     __THROW __attribute_pure__;

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
बाह्य अक्षर *envz_get (स्थिर अक्षर *__restrict __envz, माप_प्रकार __envz_len,
		       स्थिर अक्षर *__restrict __name)
     __THROW __attribute_pure__;

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
बाह्य error_t envz_add (अक्षर **__restrict __envz,
			 माप_प्रकार *__restrict __envz_len,
			 स्थिर अक्षर *__restrict __name,
			 स्थिर अक्षर *__restrict __value) __THROW;

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
बाह्य error_t envz_merge (अक्षर **__restrict __envz,
			   माप_प्रकार *__restrict __envz_len,
			   स्थिर अक्षर *__restrict __envz2,
			   माप_प्रकार __envz2_len, पूर्णांक __override) __THROW;

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
बाह्य व्योम envz_remove (अक्षर **__restrict __envz,
			 माप_प्रकार *__restrict __envz_len,
			 स्थिर अक्षर *__restrict __name) __THROW;

/* Remove null entries.  */
बाह्य व्योम envz_strip (अक्षर **__restrict __envz,
			माप_प्रकार *__restrict __envz_len) __THROW;

__END_DECLS

#पूर्ण_अगर /* envz.h */
