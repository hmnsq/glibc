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

#অন্তর্ভাব <malloc.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
অক্ষর *
envz_entry (ধ্রুবক অক্ষর *envz, size_t envz_len, ধ্রুবক অক্ষর *name)
{
  যখন (envz_len)
    {
      ধ্রুবক অক্ষর *p = name;
      ধ্রুবক অক্ষর *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      যখন (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      যদি ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	ফেরত (অক্ষর *) entry;

      /* No match, skip to the next entry.  */
      যখন (envz_len && *envz)
	envz++, envz_len--;
      যদি (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  ফেরত ফাঁকা;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
অক্ষর *
envz_get (ধ্রুবক অক্ষর *envz, size_t envz_len, ধ্রুবক অক্ষর *name)
{
  অক্ষর *entry = envz_entry (envz, envz_len, name);
  যদি (entry)
    {
      যখন (*entry && *entry != SEP)
	entry++;
      যদি (*entry)
	entry++;
      অন্যথা
	entry = ফাঁকা;		/* A null entry.  */
    }
  ফেরত entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
শূন্য
envz_remove (অক্ষর **envz, size_t *envz_len, ধ্রুবক অক্ষর *name)
{
  অক্ষর *entry = envz_entry (*envz, *envz_len, name);
  যদি (entry)
    argz_delete (envz, envz_len, entry);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_add (অক্ষর **envz, size_t *envz_len, ধ্রুবক অক্ষর *name, ধ্রুবক অক্ষর *মান)
{
  envz_remove (envz, envz_len, name);

  যদি (মান)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t মান_len = strlen (মান);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + মান_len + 1;
      অক্ষর *new_envz = realloc (*envz, new_envz_len);

      যদি (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, মান, মান_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  ফেরত 0;
	}
      অন্যথা
	ফেরত ENOMEM;
    }
  অন্যথা
    /* Add a null entry.  */
    ফেরত __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (অক্ষর **envz, size_t *envz_len, ধ্রুবক অক্ষর *envz2,
	    size_t envz2_len, পূর্ণসংখ্যা override)
{
  error_t err = 0;

  যখন (envz2_len && ! err)
    {
      অক্ষর *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      যদি (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      অন্যথা যদি (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  ফেরত err;
}

/* Remove null entries.  */
শূন্য
envz_strip (অক্ষর **envz, size_t *envz_len)
{
  অক্ষর *entry = *envz;
  size_t বাম = *envz_len;
  যখন (বাম)
    {
      size_t entry_len = strlen (entry) + 1;
      বাম -= entry_len;
      যদি (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, বাম);
      অন্যথা
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
