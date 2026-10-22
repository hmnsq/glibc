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

#جيڪڏهن_وصف_نه_ٿيل _ARGZ_H
#وصف_ڪريو _ARGZ_H	1

#ضمن <features.h>
#ضمن <errno.h>
#ضمن <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#جيڪڏهن_وصف_نه_ٿيل __error_t_defined
# define __error_t_defined 1
تعريفنوع صحيح error_t;
#جيڪڏهن_پورو

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
خارجي error_t __argz_create (حرف *ثابت __argv[], حرف **__restrict __argz,
			      size_t *__restrict __len) __THROW;
خارجي error_t argz_create (حرف *ثابت __argv[], حرف **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
خارجي error_t argz_create_sep (ثابت حرف *__restrict __string,
				صحيح __sep, حرف **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
خارجي size_t __argz_count (ثابت حرف *__argz, size_t __len)
     __THROW __attribute_pure__;
خارجي size_t argz_ڳڻپ (ثابت حرف *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
خارجي فراغ __argz_extract (ثابت حرف *__restrict __argz, size_t __len,
			    حرف **__restrict __argv) __THROW;
خارجي فراغ argz_ڪڍو (ثابت حرف *__restrict __argz, size_t __len,
			  حرف **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
خارجي فراغ __argz_stringify (حرف *__argz, size_t __len, صحيح __sep) __THROW;
خارجي فراغ argz_stringify (حرف *__argz, size_t __len, صحيح __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
خارجي error_t argz_append (حرف **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ثابت حرف *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
خارجي error_t argz_جوڙيو (حرف **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ثابت حرف *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
خارجي error_t argz_جوڙيو_sep (حرف **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ثابت حرف *__restrict __string, صحيح __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
خارجي فراغ argz_delete (حرف **__restrict __argz,
			 size_t *__restrict __argz_len,
			 حرف *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
خارجي error_t argz_وجهو (حرف **__restrict __argz,
			    size_t *__restrict __argz_len,
			    حرف *__restrict __before,
			    ثابت حرف *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
خارجي error_t argz_replace (حرف **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ثابت حرف *__restrict __str,
			     ثابت حرف *__restrict __with,
			     بنانشان صحيح *__restrict __replace_count);

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
خارجي حرف *__argz_next (ثابت حرف *__restrict __argz, size_t __argz_len,
			  ثابت حرف *__restrict __entry) __THROW;
خارجي حرف *argz_ايندڙ (ثابت حرف *__restrict __argz, size_t __argz_len,
			ثابت حرف *__restrict __entry) __THROW;

#جيڪڏهن_وصف_ٿيل __USE_EXTERN_INLINES
__extern_inline حرف *
__NTH (__argz_next (ثابت حرف *__argz, size_t __argz_len,
		    ثابت حرف *__entry))
{
  إذا (__entry)
    {
      إذا (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      أرجع __entry >= __argz + __argz_len ? (حرف *) عدم : (حرف *) __entry;
    }
  وإلا
    أرجع __argz_len > 0 ? (حرف *) __argz : عدم;
}
__extern_inline حرف *
__NTH (argz_ايندڙ (ثابت حرف *__argz, size_t __argz_len,
		  ثابت حرف *__entry))
{
  أرجع __argz_next (__argz, __argz_len, __entry);
}
#جيڪڏهن_پورو /* Use extern inlines.  */

__END_DECLS

#جيڪڏهن_پورو /* argz.h */
