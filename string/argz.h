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

#ifndef _ARGZ_H
#define _ARGZ_H	1

#ಅನ್ತರ್ಭಾವ <features.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#ifndef __error_t_defined
# define __error_t_defined 1
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ error_t;
#endif

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
ಬಾಹ್ಯ error_t __argz_create (ವರ್ಣ *ಧ್ರುವ __argv[], ವರ್ಣ **__restrict __argz,
			      size_t *__restrict __len) __THROW;
ಬಾಹ್ಯ error_t argz_create (ವರ್ಣ *ಧ್ರುವ __argv[], ವರ್ಣ **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
ಬಾಹ್ಯ error_t argz_create_sep (ಧ್ರುವ ವರ್ಣ *__restrict __string,
				ಪೂರ್ಣಾಙ್ಕ __sep, ವರ್ಣ **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
ಬಾಹ್ಯ size_t __argz_count (ಧ್ರುವ ವರ್ಣ *__argz, size_t __len)
     __THROW __attribute_pure__;
ಬಾಹ್ಯ size_t argz_ಎಣಿಕೆ (ಧ್ರುವ ವರ್ಣ *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
ಬಾಹ್ಯ ಶೂನ್ಯ __argz_extract (ಧ್ರುವ ವರ್ಣ *__restrict __argz, size_t __len,
			    ವರ್ಣ **__restrict __argv) __THROW;
ಬಾಹ್ಯ ಶೂನ್ಯ argz_extract (ಧ್ರುವ ವರ್ಣ *__restrict __argz, size_t __len,
			  ವರ್ಣ **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
ಬಾಹ್ಯ ಶೂನ್ಯ __argz_stringify (ವರ್ಣ *__argz, size_t __len, ಪೂರ್ಣಾಙ್ಕ __sep) __THROW;
ಬಾಹ್ಯ ಶೂನ್ಯ argz_stringify (ವರ್ಣ *__argz, size_t __len, ಪೂರ್ಣಾಙ್ಕ __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_append (ವರ್ಣ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ಧ್ರುವ ವರ್ಣ *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_add (ವರ್ಣ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ಧ್ರುವ ವರ್ಣ *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_add_sep (ವರ್ಣ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ಧ್ರುವ ವರ್ಣ *__restrict __string, ಪೂರ್ಣಾಙ್ಕ __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
ಬಾಹ್ಯ ಶೂನ್ಯ argz_delete (ವರ್ಣ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ವರ್ಣ *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
ಬಾಹ್ಯ error_t argz_ಸೇರಿಸು (ವರ್ಣ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ವರ್ಣ *__restrict __before,
			    ಧ್ರುವ ವರ್ಣ *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
ಬಾಹ್ಯ error_t argz_replace (ವರ್ಣ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ಧ್ರುವ ವರ್ಣ *__restrict __str,
			     ಧ್ರುವ ವರ್ಣ *__restrict __with,
			     unsigned ಪೂರ್ಣಾಙ್ಕ *__restrict __replace_count);

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
ಬಾಹ್ಯ ವರ್ಣ *__argz_next (ಧ್ರುವ ವರ್ಣ *__restrict __argz, size_t __argz_len,
			  ಧ್ರುವ ವರ್ಣ *__restrict __entry) __THROW;
ಬಾಹ್ಯ ವರ್ಣ *argz_next (ಧ್ರುವ ವರ್ಣ *__restrict __argz, size_t __argz_len,
			ಧ್ರುವ ವರ್ಣ *__restrict __entry) __THROW;

#ifdef __USE_EXTERN_INLINES
__extern_inline ವರ್ಣ *
__NTH (__argz_next (ಧ್ರುವ ವರ್ಣ *__argz, size_t __argz_len,
		    ಧ್ರುವ ವರ್ಣ *__entry))
{
  ಯದಿ (__entry)
    {
      ಯದಿ (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      ಪ್ರತ್ಯಾಗಮ __entry >= __argz + __argz_len ? (ವರ್ಣ *) ರಿಕ್ತ : (ವರ್ಣ *) __entry;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ __argz_len > 0 ? (ವರ್ಣ *) __argz : ರಿಕ್ತ;
}
__extern_inline ವರ್ಣ *
__NTH (argz_next (ಧ್ರುವ ವರ್ಣ *__argz, size_t __argz_len,
		  ಧ್ರುವ ವರ್ಣ *__entry))
{
  ಪ್ರತ್ಯಾಗಮ __argz_next (__argz, __argz_len, __entry);
}
#endif /* Use extern inlines.  */

__END_DECLS

#endif /* argz.h */
