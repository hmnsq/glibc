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

#અન્તર્ભાવ <malloc.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
અક્ષર *
envz_entry (અચલ અક્ષર *envz, size_t envz_len, અચલ અક્ષર *name)
{
  જ્યારે (envz_len)
    {
      અચલ અક્ષર *p = name;
      અચલ અક્ષર *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      જ્યારે (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      જો ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	પાછા (અક્ષર *) entry;

      /* No match, skip to the next entry.  */
      જ્યારે (envz_len && *envz)
	envz++, envz_len--;
      જો (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  પાછા ખાલી;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
અક્ષર *
envz_get (અચલ અક્ષર *envz, size_t envz_len, અચલ અક્ષર *name)
{
  અક્ષર *entry = envz_entry (envz, envz_len, name);
  જો (entry)
    {
      જ્યારે (*entry && *entry != SEP)
	entry++;
      જો (*entry)
	entry++;
      નહીંતર
	entry = ખાલી;		/* A null entry.  */
    }
  પાછા entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
શૂન્ય
envz_remove (અક્ષર **envz, size_t *envz_len, અચલ અક્ષર *name)
{
  અક્ષર *entry = envz_entry (*envz, *envz_len, name);
  જો (entry)
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
envz_add (અક્ષર **envz, size_t *envz_len, અચલ અક્ષર *name, અચલ અક્ષર *કિંમત)
{
  envz_remove (envz, envz_len, name);

  જો (કિંમત)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t કિંમત_len = strlen (કિંમત);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + કિંમત_len + 1;
      અક્ષર *new_envz = realloc (*envz, new_envz_len);

      જો (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, કિંમત, કિંમત_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  પાછા 0;
	}
      નહીંતર
	પાછા ENOMEM;
    }
  નહીંતર
    /* Add a null entry.  */
    પાછા __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (અક્ષર **envz, size_t *envz_len, અચલ અક્ષર *envz2,
	    size_t envz2_len, પૂર્ણાંક override)
{
  error_t err = 0;

  જ્યારે (envz2_len && ! err)
    {
      અક્ષર *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      જો (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      નહીંતર જો (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  પાછા err;
}

/* Remove null entries.  */
શૂન્ય
envz_strip (અક્ષર **envz, size_t *envz_len)
{
  અક્ષર *entry = *envz;
  size_t ડાબું = *envz_len;
  જ્યારે (ડાબું)
    {
      size_t entry_len = strlen (entry) + 1;
      ડાબું -= entry_len;
      જો (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, ડાબું);
      નહીંતર
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
