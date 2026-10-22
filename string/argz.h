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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _ARGZ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _ARGZ_H	1

#ਅਨ੍ਤਰ੍ਭਾਵ <features.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __error_t_defined
# define __error_t_defined 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ error_t;
#ਜੇ_ਅੰਤ

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
ਬਾਹਰੀ error_t __argz_create (ਅੱਖਰ *ਅਚਲ __argv[], ਅੱਖਰ **__restrict __argz,
			      size_t *__restrict __len) __THROW;
ਬਾਹਰੀ error_t argz_create (ਅੱਖਰ *ਅਚਲ __argv[], ਅੱਖਰ **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
ਬਾਹਰੀ error_t argz_create_sep (ਅਚਲ ਅੱਖਰ *__restrict __string,
				ਪੂਰਨ __sep, ਅੱਖਰ **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
ਬਾਹਰੀ size_t __argz_count (ਅਚਲ ਅੱਖਰ *__argz, size_t __len)
     __THROW __attribute_pure__;
ਬਾਹਰੀ size_t argz_ਗਿਣਤੀ (ਅਚਲ ਅੱਖਰ *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
ਬਾਹਰੀ ਖਾਲੀ __argz_extract (ਅਚਲ ਅੱਖਰ *__restrict __argz, size_t __len,
			    ਅੱਖਰ **__restrict __argv) __THROW;
ਬਾਹਰੀ ਖਾਲੀ argz_ਕੱਢੋ (ਅਚਲ ਅੱਖਰ *__restrict __argz, size_t __len,
			  ਅੱਖਰ **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
ਬਾਹਰੀ ਖਾਲੀ __argz_stringify (ਅੱਖਰ *__argz, size_t __len, ਪੂਰਨ __sep) __THROW;
ਬਾਹਰੀ ਖਾਲੀ argz_stringify (ਅੱਖਰ *__argz, size_t __len, ਪੂਰਨ __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
ਬਾਹਰੀ error_t argz_append (ਅੱਖਰ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ਅਚਲ ਅੱਖਰ *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
ਬਾਹਰੀ error_t argz_ਜੋੜੋ (ਅੱਖਰ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ਅਚਲ ਅੱਖਰ *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
ਬਾਹਰੀ error_t argz_ਜੋੜੋ_sep (ਅੱਖਰ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ਅਚਲ ਅੱਖਰ *__restrict __string, ਪੂਰਨ __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
ਬਾਹਰੀ ਖਾਲੀ argz_delete (ਅੱਖਰ **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ਅੱਖਰ *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
ਬਾਹਰੀ error_t argz_ਪਾਓ (ਅੱਖਰ **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ਅੱਖਰ *__restrict __before,
			    ਅਚਲ ਅੱਖਰ *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
ਬਾਹਰੀ error_t argz_replace (ਅੱਖਰ **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ਅਚਲ ਅੱਖਰ *__restrict __str,
			     ਅਚਲ ਅੱਖਰ *__restrict __with,
			     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *__restrict __replace_count);

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
ਬਾਹਰੀ ਅੱਖਰ *__argz_next (ਅਚਲ ਅੱਖਰ *__restrict __argz, size_t __argz_len,
			  ਅਚਲ ਅੱਖਰ *__restrict __entry) __THROW;
ਬਾਹਰੀ ਅੱਖਰ *argz_ਅਗਲਾ (ਅਚਲ ਅੱਖਰ *__restrict __argz, size_t __argz_len,
			ਅਚਲ ਅੱਖਰ *__restrict __entry) __THROW;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_EXTERN_INLINES
__extern_inline ਅੱਖਰ *
__NTH (__argz_next (ਅਚਲ ਅੱਖਰ *__argz, size_t __argz_len,
		    ਅਚਲ ਅੱਖਰ *__entry))
{
  ਜੇ (__entry)
    {
      ਜੇ (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      ਵਾਪਸ __entry >= __argz + __argz_len ? (ਅੱਖਰ *) ਨਿਰਾ : (ਅੱਖਰ *) __entry;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ __argz_len > 0 ? (ਅੱਖਰ *) __argz : ਨਿਰਾ;
}
__extern_inline ਅੱਖਰ *
__NTH (argz_ਅਗਲਾ (ਅਚਲ ਅੱਖਰ *__argz, size_t __argz_len,
		  ਅਚਲ ਅੱਖਰ *__entry))
{
  ਵਾਪਸ __argz_next (__argz, __argz_len, __entry);
}
#ਜੇ_ਅੰਤ /* Use extern inlines.  */

__END_DECLS

#ਜੇ_ਅੰਤ /* argz.h */
