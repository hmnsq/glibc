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

#அந்தர்பாவ <malloc.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
எழுத்து *
envz_entry (மாறிலி எழுத்து *envz, size_t envz_len, மாறிலி எழுத்து *name)
{
  போது (envz_len)
    {
      மாறிலி எழுத்து *p = name;
      மாறிலி எழுத்து *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      போது (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      எனில் ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	திரும்பு (எழுத்து *) entry;

      /* No match, skip to the next entry.  */
      போது (envz_len && *envz)
	envz++, envz_len--;
      எனில் (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  திரும்பு வெற்று;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
எழுத்து *
envz_get (மாறிலி எழுத்து *envz, size_t envz_len, மாறிலி எழுத்து *name)
{
  எழுத்து *entry = envz_entry (envz, envz_len, name);
  எனில் (entry)
    {
      போது (*entry && *entry != SEP)
	entry++;
      எனில் (*entry)
	entry++;
      இல்லையெனில்
	entry = வெற்று;		/* A null entry.  */
    }
  திரும்பு entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
வெறுமை
envz_remove (எழுத்து **envz, size_t *envz_len, மாறிலி எழுத்து *name)
{
  எழுத்து *entry = envz_entry (*envz, *envz_len, name);
  எனில் (entry)
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
envz_add (எழுத்து **envz, size_t *envz_len, மாறிலி எழுத்து *name, மாறிலி எழுத்து *மதிப்பு)
{
  envz_remove (envz, envz_len, name);

  எனில் (மதிப்பு)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t மதிப்பு_len = strlen (மதிப்பு);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + மதிப்பு_len + 1;
      எழுத்து *new_envz = realloc (*envz, new_envz_len);

      எனில் (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, மதிப்பு, மதிப்பு_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  திரும்பு 0;
	}
      இல்லையெனில்
	திரும்பு ENOMEM;
    }
  இல்லையெனில்
    /* Add a null entry.  */
    திரும்பு __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (எழுத்து **envz, size_t *envz_len, மாறிலி எழுத்து *envz2,
	    size_t envz2_len, முழு override)
{
  error_t err = 0;

  போது (envz2_len && ! err)
    {
      எழுத்து *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      எனில் (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      இல்லையெனில் எனில் (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  திரும்பு err;
}

/* Remove null entries.  */
வெறுமை
envz_strip (எழுத்து **envz, size_t *envz_len)
{
  எழுத்து *entry = *envz;
  size_t இடது = *envz_len;
  போது (இடது)
    {
      size_t entry_len = strlen (entry) + 1;
      இடது -= entry_len;
      எனில் (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, இடது);
      இல்லையெனில்
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
