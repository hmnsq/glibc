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

#அந்தர்பாவ <features.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#ifndef __error_t_defined
# define __error_t_defined 1
வகைவரை முழு error_t;
#endif

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
வெளி error_t __argz_create (எழுத்து *மாறிலி __argv[], எழுத்து **__restrict __argz,
			      size_t *__restrict __len) __THROW;
வெளி error_t argz_create (எழுத்து *மாறிலி __argv[], எழுத்து **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
வெளி error_t argz_create_sep (மாறிலி எழுத்து *__restrict __string,
				முழு __sep, எழுத்து **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
வெளி size_t __argz_count (மாறிலி எழுத்து *__argz, size_t __len)
     __THROW __attribute_pure__;
வெளி size_t argz_மொத்தம் (மாறிலி எழுத்து *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
வெளி வெறுமை __argz_extract (மாறிலி எழுத்து *__restrict __argz, size_t __len,
			    எழுத்து **__restrict __argv) __THROW;
வெளி வெறுமை argz_extract (மாறிலி எழுத்து *__restrict __argz, size_t __len,
			  எழுத்து **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
வெளி வெறுமை __argz_stringify (எழுத்து *__argz, size_t __len, முழு __sep) __THROW;
வெளி வெறுமை argz_stringify (எழுத்து *__argz, size_t __len, முழு __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
வெளி error_t argz_append (எழுத்து **__restrict __argz,
			    size_t *__restrict __argz_len,
			    மாறிலி எழுத்து *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
வெளி error_t argz_add (எழுத்து **__restrict __argz,
			 size_t *__restrict __argz_len,
			 மாறிலி எழுத்து *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
வெளி error_t argz_add_sep (எழுத்து **__restrict __argz,
			     size_t *__restrict __argz_len,
			     மாறிலி எழுத்து *__restrict __string, முழு __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
வெளி வெறுமை argz_delete (எழுத்து **__restrict __argz,
			 size_t *__restrict __argz_len,
			 எழுத்து *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
வெளி error_t argz_செருகு (எழுத்து **__restrict __argz,
			    size_t *__restrict __argz_len,
			    எழுத்து *__restrict __before,
			    மாறிலி எழுத்து *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
வெளி error_t argz_replace (எழுத்து **__restrict __argz,
			     size_t *__restrict __argz_len,
			     மாறிலி எழுத்து *__restrict __str,
			     மாறிலி எழுத்து *__restrict __with,
			     unsigned முழு *__restrict __replace_count);

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
வெளி எழுத்து *__argz_next (மாறிலி எழுத்து *__restrict __argz, size_t __argz_len,
			  மாறிலி எழுத்து *__restrict __entry) __THROW;
வெளி எழுத்து *argz_next (மாறிலி எழுத்து *__restrict __argz, size_t __argz_len,
			மாறிலி எழுத்து *__restrict __entry) __THROW;

#ifdef __USE_EXTERN_INLINES
__extern_inline எழுத்து *
__NTH (__argz_next (மாறிலி எழுத்து *__argz, size_t __argz_len,
		    மாறிலி எழுத்து *__entry))
{
  எனில் (__entry)
    {
      எனில் (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      திரும்பு __entry >= __argz + __argz_len ? (எழுத்து *) வெற்று : (எழுத்து *) __entry;
    }
  இல்லையெனில்
    திரும்பு __argz_len > 0 ? (எழுத்து *) __argz : வெற்று;
}
__extern_inline எழுத்து *
__NTH (argz_next (மாறிலி எழுத்து *__argz, size_t __argz_len,
		  மாறிலி எழுத்து *__entry))
{
  திரும்பு __argz_next (__argz, __argz_len, __entry);
}
#endif /* Use extern inlines.  */

__END_DECLS

#endif /* argz.h */
