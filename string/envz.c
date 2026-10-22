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

#include <malloc.h>
#include <string.h>

#include <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
var_na *
envz_entry (const var_na *envz, size_t envz_len, const var_na *name)
{
  ขณะ (envz_len)
    {
      const var_na *p = name;
      const var_na *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      ขณะ (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      ถ้า ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	คืน (var_na *) entry;

      /* No match, skip to the next entry.  */
      ขณะ (envz_len && *envz)
	envz++, envz_len--;
      ถ้า (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  คืน NULL;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
var_na *
envz_get (const var_na *envz, size_t envz_len, const var_na *name)
{
  var_na *entry = envz_entry (envz, envz_len, name);
  ถ้า (entry)
    {
      ขณะ (*entry && *entry != SEP)
	entry++;
      ถ้า (*entry)
	entry++;
      มิฉะนั้น
	entry = NULL;		/* A null entry.  */
    }
  คืน entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
void
envz_remove (var_na **envz, size_t *envz_len, const var_na *name)
{
  var_na *entry = envz_entry (*envz, *envz_len, name);
  ถ้า (entry)
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
envz_add (var_na **envz, size_t *envz_len, const var_na *name, const var_na *value)
{
  envz_remove (envz, envz_len, name);

  ถ้า (value)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t value_len = strlen (value);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + value_len + 1;
      var_na *new_envz = realloc (*envz, new_envz_len);

      ถ้า (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, value, value_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  คืน 0;
	}
      มิฉะนั้น
	คืน ENOMEM;
    }
  มิฉะนั้น
    /* Add a null entry.  */
    คืน __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (var_na **envz, size_t *envz_len, const var_na *envz2,
	    size_t envz2_len, จำนวนเต็ม override)
{
  error_t err = 0;

  ขณะ (envz2_len && ! err)
    {
      var_na *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      ถ้า (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      มิฉะนั้น ถ้า (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  คืน err;
}

/* Remove null entries.  */
void
envz_strip (var_na **envz, size_t *envz_len)
{
  var_na *entry = *envz;
  size_t left = *envz_len;
  ขณะ (left)
    {
      size_t entry_len = strlen (entry) + 1;
      left -= entry_len;
      ถ้า (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, left);
      มิฉะนั้น
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
