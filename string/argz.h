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

#અન્તર્ભાવ <features.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#ifndef __error_t_defined
# define __error_t_defined 1
પ્રકારવ્યાખ્યા પૂર્ણાંક error_t;
#endif

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
બાહ્ય error_t __argz_create (અક્ષર *અચલ __argv[], અક્ષર **__restrict __argz,
			      size_t *__restrict __len) __THROW;
બાહ્ય error_t argz_create (અક્ષર *અચલ __argv[], અક્ષર **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
બાહ્ય error_t argz_create_sep (અચલ અક્ષર *__restrict __string,
				પૂર્ણાંક __sep, અક્ષર **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
બાહ્ય size_t __argz_count (અચલ અક્ષર *__argz, size_t __len)
     __THROW __attribute_pure__;
બાહ્ય size_t argz_ગણતરી (અચલ અક્ષર *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
બાહ્ય શૂન્ય __argz_extract (અચલ અક્ષર *__restrict __argz, size_t __len,
			    અક્ષર **__restrict __argv) __THROW;
બાહ્ય શૂન્ય argz_extract (અચલ અક્ષર *__restrict __argz, size_t __len,
			  અક્ષર **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
બાહ્ય શૂન્ય __argz_stringify (અક્ષર *__argz, size_t __len, પૂર્ણાંક __sep) __THROW;
બાહ્ય શૂન્ય argz_stringify (અક્ષર *__argz, size_t __len, પૂર્ણાંક __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
બાહ્ય error_t argz_append (અક્ષર **__restrict __argz,
			    size_t *__restrict __argz_len,
			    અચલ અક્ષર *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
બાહ્ય error_t argz_add (અક્ષર **__restrict __argz,
			 size_t *__restrict __argz_len,
			 અચલ અક્ષર *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
બાહ્ય error_t argz_add_sep (અક્ષર **__restrict __argz,
			     size_t *__restrict __argz_len,
			     અચલ અક્ષર *__restrict __string, પૂર્ણાંક __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
બાહ્ય શૂન્ય argz_delete (અક્ષર **__restrict __argz,
			 size_t *__restrict __argz_len,
			 અક્ષર *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
બાહ્ય error_t argz_ઉમેરો (અક્ષર **__restrict __argz,
			    size_t *__restrict __argz_len,
			    અક્ષર *__restrict __before,
			    અચલ અક્ષર *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
બાહ્ય error_t argz_replace (અક્ષર **__restrict __argz,
			     size_t *__restrict __argz_len,
			     અચલ અક્ષર *__restrict __str,
			     અચલ અક્ષર *__restrict __with,
			     unsigned પૂર્ણાંક *__restrict __replace_count);

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
બાહ્ય અક્ષર *__argz_next (અચલ અક્ષર *__restrict __argz, size_t __argz_len,
			  અચલ અક્ષર *__restrict __entry) __THROW;
બાહ્ય અક્ષર *argz_next (અચલ અક્ષર *__restrict __argz, size_t __argz_len,
			અચલ અક્ષર *__restrict __entry) __THROW;

#ifdef __USE_EXTERN_INLINES
__extern_inline અક્ષર *
__NTH (__argz_next (અચલ અક્ષર *__argz, size_t __argz_len,
		    અચલ અક્ષર *__entry))
{
  જો (__entry)
    {
      જો (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      પાછા __entry >= __argz + __argz_len ? (અક્ષર *) ખાલી : (અક્ષર *) __entry;
    }
  નહીંતર
    પાછા __argz_len > 0 ? (અક્ષર *) __argz : ખાલી;
}
__extern_inline અક્ષર *
__NTH (argz_next (અચલ અક્ષર *__argz, size_t __argz_len,
		  અચલ અક્ષર *__entry))
{
  પાછા __argz_next (__argz, __argz_len, __entry);
}
#endif /* Use extern inlines.  */

__END_DECLS

#endif /* argz.h */
