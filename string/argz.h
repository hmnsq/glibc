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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _ARGZ_H
#ವ್ಯಾಖ್ಯಾನಿಸು _ARGZ_H	1

#ಅನ್ತರ್ಭಾವ <features.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __error_t_defined
# define __error_t_defined 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ error_t;
#ಆದರೆ_ಅಂತ್ಯ

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
ಬಾಹ್ಯ error_t __argz_create (ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ __argv[], ಅಕ್ಷರ **__restrict __argz,
			      size_t *__restrict __len) __THROW;
ಬಾಹ್ಯ error_t argz_create (ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ __argv[], ಅಕ್ಷರ **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
ಬಾಹ್ಯ error_t argz_create_sep (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __string,
				ಪೂರ್ಣಾಂಕ __sep, ಅಕ್ಷರ **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
ಬಾಹ್ಯ size_t __argz_count (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__argz, size_t __len)
     __THROW __attribute_pure__;
ಬಾಹ್ಯ size_t argz_ಎಣಿಕೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
ಬಾಹ್ಯ ಶೂನ್ಯ __argz_extract (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __argz, size_t __len,
			    ಅಕ್ಷರ **__restrict __argv) __THROW;
ಬಾಹ್ಯ ಶೂನ್ಯ argz_ಹೊರತೆಗೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __argz, size_t __len,
			  ಅಕ್ಷರ **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
ಬಾಹ್ಯ ಶೂನ್ಯ __argz_stringify (ಅಕ್ಷರ *__argz, size_t __len, ಪೂರ್ಣಾಂಕ __sep) __THROW;
ಬಾಹ್ಯ ಶೂನ್ಯ argz_stringify (ಅಕ್ಷರ *__argz, size_t __len, ಪೂರ್ಣಾಂಕ __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_append (ಅಕ್ಷರ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_ಕೂಡಿಸು (ಅಕ್ಷರ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
ಬಾಹ್ಯ error_t argz_ಕೂಡಿಸು_sep (ಅಕ್ಷರ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __string, ಪೂರ್ಣಾಂಕ __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
ಬಾಹ್ಯ ಶೂನ್ಯ argz_delete (ಅಕ್ಷರ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ಅಕ್ಷರ *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
ಬಾಹ್ಯ error_t argz_ಸೇರಿಸು (ಅಕ್ಷರ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ಅಕ್ಷರ *__restrict __before,
			    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
ಬಾಹ್ಯ error_t argz_replace (ಅಕ್ಷರ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __str,
			     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __with,
			     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *__restrict __replace_count);

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
ಬಾಹ್ಯ ಅಕ್ಷರ *__argz_next (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __argz, size_t __argz_len,
			  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __entry) __THROW;
ಬಾಹ್ಯ ಅಕ್ಷರ *argz_ಮುಂದಿನ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __argz, size_t __argz_len,
			ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __entry) __THROW;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_EXTERN_INLINES
__extern_inline ಅಕ್ಷರ *
__NTH (__argz_next (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__argz, size_t __argz_len,
		    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__entry))
{
  ಆದರೆ (__entry)
    {
      ಆದರೆ (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      ಹಿಂತಿರುಗಿ __entry >= __argz + __argz_len ? (ಅಕ್ಷರ *) ಖಾಲಿ : (ಅಕ್ಷರ *) __entry;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ __argz_len > 0 ? (ಅಕ್ಷರ *) __argz : ಖಾಲಿ;
}
__extern_inline ಅಕ್ಷರ *
__NTH (argz_ಮುಂದಿನ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__argz, size_t __argz_len,
		  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__entry))
{
  ಹಿಂತಿರುಗಿ __argz_next (__argz, __argz_len, __entry);
}
#ಆದರೆ_ಅಂತ್ಯ /* Use extern inlines.  */

__END_DECLS

#ಆದರೆ_ಅಂತ್ಯ /* argz.h */
