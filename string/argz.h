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

#నిర్వచితం_కాకపోతే _ARGZ_H
#నిర్వచించు _ARGZ_H	1

#అన్తర్భావ <features.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <string.h>		/* Need size_t, and strchr is called below.  */

__BEGIN_DECLS

/* error_t may or may not be available from errno.h, depending on the
   operating system.  */
#నిర్వచితం_కాకపోతే __error_t_defined
# define __error_t_defined 1
రకనిర్వచనం పూర్ణాంకం error_t;
#అయితే_ముగింపు

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN.  If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0.  The result can be destroyed using free. */
బాహ్య error_t __argz_create (అక్షరం *స్థిరరాశి __argv[], అక్షరం **__restrict __argz,
			      size_t *__restrict __len) __THROW;
బాహ్య error_t argz_create (అక్షరం *స్థిరరాశి __argv[], అక్షరం **__restrict __argz,
			    size_t *__restrict __len) __THROW;

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN.  If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free.  */
బాహ్య error_t argz_create_sep (స్థిరరాశి అక్షరం *__restrict __string,
				పూర్ణాంకం __sep, అక్షరం **__restrict __argz,
				size_t *__restrict __len) __THROW;

/* Returns the number of strings in ARGZ.  */
బాహ్య size_t __argz_count (స్థిరరాశి అక్షరం *__argz, size_t __len)
     __THROW __attribute_pure__;
బాహ్య size_t argz_లెక్క (స్థిరరాశి అక్షరం *__argz, size_t __len)
     __THROW __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all.  */
బాహ్య శూన్య __argz_extract (స్థిరరాశి అక్షరం *__restrict __argz, size_t __len,
			    అక్షరం **__restrict __argv) __THROW;
బాహ్య శూన్య argz_వెలికితీయి (స్థిరరాశి అక్షరం *__restrict __argz, size_t __len,
			  అక్షరం **__restrict __argv) __THROW;

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
బాహ్య శూన్య __argz_stringify (అక్షరం *__argz, size_t __len, పూర్ణాంకం __sep) __THROW;
బాహ్య శూన్య argz_stringify (అక్షరం *__argz, size_t __len, పూర్ణాంకం __sep) __THROW;

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
బాహ్య error_t argz_append (అక్షరం **__restrict __argz,
			    size_t *__restrict __argz_len,
			    స్థిరరాశి అక్షరం *__restrict __buf, size_t __buf_len)
     __THROW;

/* Append STR to the argz vector in ARGZ & ARGZ_LEN.  */
బాహ్య error_t argz_కూడు (అక్షరం **__restrict __argz,
			 size_t *__restrict __argz_len,
			 స్థిరరాశి అక్షరం *__restrict __str) __THROW;

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN.  */
బాహ్య error_t argz_కూడు_sep (అక్షరం **__restrict __argz,
			     size_t *__restrict __argz_len,
			     స్థిరరాశి అక్షరం *__restrict __string, పూర్ణాంకం __delim)
     __THROW;

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there.  */
బాహ్య శూన్య argz_delete (అక్షరం **__restrict __argz,
			 size_t *__restrict __argz_len,
			 అక్షరం *__restrict __entry) __THROW;

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
బాహ్య error_t argz_చొప్పించు (అక్షరం **__restrict __argz,
			    size_t *__restrict __argz_len,
			    అక్షరం *__restrict __before,
			    స్థిరరాశి అక్షరం *__restrict __entry) __THROW;

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
బాహ్య error_t argz_replace (అక్షరం **__restrict __argz,
			     size_t *__restrict __argz_len,
			     స్థిరరాశి అక్షరం *__restrict __str,
			     స్థిరరాశి అక్షరం *__restrict __with,
			     గుర్తులేని పూర్ణాంకం *__restrict __replace_count);

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
బాహ్య అక్షరం *__argz_next (స్థిరరాశి అక్షరం *__restrict __argz, size_t __argz_len,
			  స్థిరరాశి అక్షరం *__restrict __entry) __THROW;
బాహ్య అక్షరం *argz_తదుపరి (స్థిరరాశి అక్షరం *__restrict __argz, size_t __argz_len,
			స్థిరరాశి అక్షరం *__restrict __entry) __THROW;

#నిర్వచితమైతే __USE_EXTERN_INLINES
__extern_inline అక్షరం *
__NTH (__argz_next (స్థిరరాశి అక్షరం *__argz, size_t __argz_len,
		    స్థిరరాశి అక్షరం *__entry))
{
  ఒకవేళ (__entry)
    {
      ఒకవేళ (__entry < __argz + __argz_len)
	__entry = strchr (__entry, '\0') + 1;

      తిరిగి __entry >= __argz + __argz_len ? (అక్షరం *) ఖాళీ : (అక్షరం *) __entry;
    }
  లేకపోతే
    తిరిగి __argz_len > 0 ? (అక్షరం *) __argz : ఖాళీ;
}
__extern_inline అక్షరం *
__NTH (argz_తదుపరి (స్థిరరాశి అక్షరం *__argz, size_t __argz_len,
		  స్థిరరాశి అక్షరం *__entry))
{
  తిరిగి __argz_next (__argz, __argz_len, __entry);
}
#అయితే_ముగింపు /* Use extern inlines.  */

__END_DECLS

#అయితే_ముగింపు /* argz.h */
