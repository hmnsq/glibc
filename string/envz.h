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

#که_نه_تعریف_شوی _ENVZ_H
#تعریف_کړه _ENVZ_H	1

#ضمن <features.h>

#ضمن <errno.h>

/* Envz's are argz's too, and should be created etc., using the same
   routines.  */
#ضمن <argz.h>

__BEGIN_DECLS

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.  */
خارجي حرف *envz_ثبت (ثابت حرف *__restrict __envz, size_t __envz_len,
			 ثابت حرف *__restrict __name)
     __THROW __attribute_pure__;

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
خارجي حرف *envz_get (ثابت حرف *__restrict __envz, size_t __envz_len,
		       ثابت حرف *__restrict __name)
     __THROW __attribute_pure__;

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
خارجي error_t envz_جمع_کړه (حرف **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ثابت حرف *__restrict __name,
			 ثابت حرف *__restrict __value) __THROW;

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
خارجي error_t envz_یوځای (حرف **__restrict __envz,
			   size_t *__restrict __envz_len,
			   ثابت حرف *__restrict __envz2,
			   size_t __envz2_len, صحيح __override) __THROW;

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
خارجي فراغ envz_remove (حرف **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ثابت حرف *__restrict __name) __THROW;

/* Remove null entries.  */
خارجي فراغ envz_strip (حرف **__restrict __envz,
			size_t *__restrict __envz_len) __THROW;

__END_DECLS

#د_که_پای /* envz.h */
