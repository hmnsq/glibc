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

#اگر_غیر_تعریف_شدہ _ARGZ_H
#تعریف_کرو _ARGZ_H	1

#شامل <features.h>
#شامل <errno.h>
#شامل <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#اگر_غیر_تعریف_شدہ __error_t_defined
# define __error_t_defined 1
قسمتعریف صحیح error_t;
#اگر_ختم

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
خارجی error_t __argz_create (حرف *ثابت __argv[], حرف **__restrict __argz,
			      size_t *__restrict __len) __THROW;
خارجی error_t argz_create (حرف *ثابت __argv[], حرف **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
خارجی error_t argz_create_sep (ثابت حرف *__restrict __string,
				صحیح __sep, حرف **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
خارجی size_t __argz_count (ثابت حرف *__argz, size_t __len)
     __THROW __attribute_pure__;
خارجی size_t argz_گنتی (ثابت حرف *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
خارجی خالی __argz_extract (ثابت حرف *__restrict __argz, size_t __len,
			    حرف **__restrict __argv) __THROW;
خارجی خالی argz_نکالو (ثابت حرف *__restrict __argz, size_t __len,
			  حرف **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
خارجی خالی __argz_stringify (حرف *__argz, size_t __len, صحیح __sep) __THROW;
خارجی خالی argz_stringify (حرف *__argz, size_t __len, صحیح __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
خارجی error_t argz_append (حرف **__restrict __argz,
			    size_t *__restrict __argz_len,
			    ثابت حرف *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
خارجی error_t argz_جوڑو (حرف **__restrict __argz,
			 size_t *__restrict __argz_len,
			 ثابت حرف *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
خارجی error_t argz_جوڑو_sep (حرف **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ثابت حرف *__restrict __string, صحیح __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
خارجی خالی argz_delete (حرف **__restrict __argz,
			 size_t *__restrict __argz_len,
			 حرف *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
خارجی error_t argz_داخل_کرو (حرف **__restrict __argz,
			    size_t *__restrict __argz_len,
			    حرف *__restrict __before,
			    ثابت حرف *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
خارجی error_t argz_replace (حرف **__restrict __argz,
			     size_t *__restrict __argz_len,
			     ثابت حرف *__restrict __str,
			     ثابت حرف *__restrict __with,
			     غیرعلامتی صحیح *__restrict __replace_count);

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
خارجی حرف *__argz_next (ثابت حرف *__restrict __argz, size_t __argz_len,
			  ثابت حرف *__restrict __entry) __THROW;
خارجی حرف *argz_اگلا (ثابت حرف *__restrict __argz, size_t __argz_len,
			ثابت حرف *__restrict __entry) __THROW;

#اگر_تعریف_شدہ __USE_EXTERN_INLINES
__extern_inline حرف *
__NTH (__argz_next (ثابت حرف *__argz, size_t __argz_len,
		    ثابت حرف *__entry))
{
  اگر (__entry)
    {
      اگر (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      واپس __entry >= __argz + __argz_len ? (حرف *) تہی : (حرف *) __entry;
    }
  ورنہ
    واپس __argz_len > 0 ? (حرف *) __argz : تہی;
}
__extern_inline حرف *
__NTH (argz_اگلا (ثابت حرف *__argz, size_t __argz_len,
		  ثابت حرف *__entry))
{
  واپس __argz_next (__argz, __argz_len, __entry);
}
#اگر_ختم /* Use extern inlines.  */

__END_DECLS

#اگر_ختم /* argz.h */
