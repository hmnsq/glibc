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

#ifndef _ENVZ_H
#define _ENVZ_H	1

#ଅନ୍ତର୍ଭାଵ <features.h>

#ଅନ୍ତର୍ଭାଵ <errno.h>

/* Envz's are argz's too, and should be created etc., using the same
   routines.  */
#ଅନ୍ତର୍ଭାଵ <argz.h>

__BEGIN_DECLS

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.  */
ବାହ୍ୟ ଅକ୍ଷର *envz_entry (ଅଚଳ ଅକ୍ଷର *__restrict __envz, size_t __envz_len,
			 ଅଚଳ ଅକ୍ଷର *__restrict __name)
     __THROW __attribute_pure__;

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
ବାହ୍ୟ ଅକ୍ଷର *envz_get (ଅଚଳ ଅକ୍ଷର *__restrict __envz, size_t __envz_len,
		       ଅଚଳ ଅକ୍ଷର *__restrict __name)
     __THROW __attribute_pure__;

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
ବାହ୍ୟ error_t envz_add (ଅକ୍ଷର **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ଅଚଳ ଅକ୍ଷର *__restrict __name,
			 ଅଚଳ ଅକ୍ଷର *__restrict __value) __THROW;

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
ବାହ୍ୟ error_t envz_merge (ଅକ୍ଷର **__restrict __envz,
			   size_t *__restrict __envz_len,
			   ଅଚଳ ଅକ୍ଷର *__restrict __envz2,
			   size_t __envz2_len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __override) __THROW;

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
ବାହ୍ୟ ଶୂନ୍ୟ envz_remove (ଅକ୍ଷର **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ଅଚଳ ଅକ୍ଷର *__restrict __name) __THROW;

/* Remove null entries.  */
ବାହ୍ୟ ଶୂନ୍ୟ envz_strip (ଅକ୍ଷର **__restrict __envz,
			size_t *__restrict __envz_len) __THROW;

__END_DECLS

#endif /* envz.h */
