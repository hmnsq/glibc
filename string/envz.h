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

#ಅನ್ತರ್ಭಾವ <features.h>

#ಅನ್ತರ್ಭಾವ <errno.h>

/* Envz's are argz's too, and should be created etc., using the same
   routines.  */
#ಅನ್ತರ್ಭಾವ <argz.h>

__BEGIN_DECLS

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.  */
ಬಾಹ್ಯ ವರ್ಣ *envz_entry (ಧ್ರುವ ವರ್ಣ *__restrict __envz, size_t __envz_len,
			 ಧ್ರುವ ವರ್ಣ *__restrict __name)
     __THROW __attribute_pure__;

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
ಬಾಹ್ಯ ವರ್ಣ *envz_get (ಧ್ರುವ ವರ್ಣ *__restrict __envz, size_t __envz_len,
		       ಧ್ರುವ ವರ್ಣ *__restrict __name)
     __THROW __attribute_pure__;

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
ಬಾಹ್ಯ error_t envz_add (ವರ್ಣ **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ಧ್ರುವ ವರ್ಣ *__restrict __name,
			 ಧ್ರುವ ವರ್ಣ *__restrict __value) __THROW;

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
ಬಾಹ್ಯ error_t envz_merge (ವರ್ಣ **__restrict __envz,
			   size_t *__restrict __envz_len,
			   ಧ್ರುವ ವರ್ಣ *__restrict __envz2,
			   size_t __envz2_len, ಪೂರ್ಣಾಙ್ಕ __override) __THROW;

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
ಬಾಹ್ಯ ಶೂನ್ಯ envz_remove (ವರ್ಣ **__restrict __envz,
			 size_t *__restrict __envz_len,
			 ಧ್ರುವ ವರ್ಣ *__restrict __name) __THROW;

/* Remove null entries.  */
ಬಾಹ್ಯ ಶೂನ್ಯ envz_strip (ವರ್ಣ **__restrict __envz,
			size_t *__restrict __envz_len) __THROW;

__END_DECLS

#endif /* envz.h */
