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

#अन्तर्भाव <malloc.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
वर्ण *
envz_entry (ध्रुव वर्ण *envz, size_t envz_len, ध्रुव वर्ण *name)
{
  यावत् (envz_len)
    {
      ध्रुव वर्ण *p = name;
      ध्रुव वर्ण *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      यावत् (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      यदि ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	प्रत्यागम (वर्ण *) entry;

      /* No match, skip to the next entry.  */
      यावत् (envz_len && *envz)
	envz++, envz_len--;
      यदि (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  प्रत्यागम रिक्त;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
वर्ण *
envz_get (ध्रुव वर्ण *envz, size_t envz_len, ध्रुव वर्ण *name)
{
  वर्ण *entry = envz_entry (envz, envz_len, name);
  यदि (entry)
    {
      यावत् (*entry && *entry != SEP)
	entry++;
      यदि (*entry)
	entry++;
      अन्यथा
	entry = रिक्त;		/* A null entry.  */
    }
  प्रत्यागम entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
शून्य
envz_remove (वर्ण **envz, size_t *envz_len, ध्रुव वर्ण *name)
{
  वर्ण *entry = envz_entry (*envz, *envz_len, name);
  यदि (entry)
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
envz_add (वर्ण **envz, size_t *envz_len, ध्रुव वर्ण *name, ध्रुव वर्ण *मूल्य)
{
  envz_remove (envz, envz_len, name);

  यदि (मूल्य)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t मूल्य_len = strlen (मूल्य);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + मूल्य_len + 1;
      वर्ण *new_envz = realloc (*envz, new_envz_len);

      यदि (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, मूल्य, मूल्य_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  प्रत्यागम 0;
	}
      अन्यथा
	प्रत्यागम ENOMEM;
    }
  अन्यथा
    /* Add a null entry.  */
    प्रत्यागम __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (वर्ण **envz, size_t *envz_len, ध्रुव वर्ण *envz2,
	    size_t envz2_len, पूर्णाङ्क override)
{
  error_t err = 0;

  यावत् (envz2_len && ! err)
    {
      वर्ण *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      यदि (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      अन्यथा यदि (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  प्रत्यागम err;
}

/* Remove null entries.  */
शून्य
envz_strip (वर्ण **envz, size_t *envz_len)
{
  वर्ण *entry = *envz;
  size_t बायाँ = *envz_len;
  यावत् (बायाँ)
    {
      size_t entry_len = strlen (entry) + 1;
      बायाँ -= entry_len;
      यदि (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, बायाँ);
      अन्यथा
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
