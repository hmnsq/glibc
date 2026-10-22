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

#شامل <malloc.h>
#شامل <string.h>

#شامل <envz.h>

/* The character separating names from values in an envz.  */
#define SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
نویسه *
envz_entry (ثابت نویسه *envz, size_t envz_len, ثابت نویسه *name)
{
  وقتی (envz_len)
    {
      ثابت نویسه *p = name;
      ثابت نویسه *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      وقتی (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      اگر ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	بازگشت (نویسه *) entry;

      /* No match, skip to the next entry.  */
      وقتی (envz_len && *envz)
	envz++, envz_len--;
      اگر (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  بازگشت پوچ;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
نویسه *
envz_get (ثابت نویسه *envz, size_t envz_len, ثابت نویسه *name)
{
  نویسه *entry = envz_entry (envz, envz_len, name);
  اگر (entry)
    {
      وقتی (*entry && *entry != SEP)
	entry++;
      اگر (*entry)
	entry++;
      وگرنه
	entry = پوچ;		/* A null entry.  */
    }
  بازگشت entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
تهی
envz_remove (نویسه **envz, size_t *envz_len, ثابت نویسه *name)
{
  نویسه *entry = envz_entry (*envz, *envz_len, name);
  اگر (entry)
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
envz_add (نویسه **envz, size_t *envz_len, ثابت نویسه *name, ثابت نویسه *مقدار)
{
  envz_remove (envz, envz_len, name);

  اگر (مقدار)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = strlen (name);
      size_t مقدار_len = strlen (مقدار);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + مقدار_len + 1;
      نویسه *new_envz = realloc (*envz, new_envz_len);

      اگر (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, مقدار, مقدار_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  بازگشت 0;
	}
      وگرنه
	بازگشت ENOMEM;
    }
  وگرنه
    /* Add a null entry.  */
    بازگشت __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (نویسه **envz, size_t *envz_len, ثابت نویسه *envz2,
	    size_t envz2_len, صحیح override)
{
  error_t err = 0;

  وقتی (envz2_len && ! err)
    {
      نویسه *old = envz_entry (*envz, *envz_len, envz2);
      size_t new_len = strlen (envz2) + 1;

      اگر (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      وگرنه اگر (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  بازگشت err;
}

/* Remove null entries.  */
تهی
envz_strip (نویسه **envz, size_t *envz_len)
{
  نویسه *entry = *envz;
  size_t چپ = *envz_len;
  وقتی (چپ)
    {
      size_t entry_len = strlen (entry) + 1;
      چپ -= entry_len;
      اگر (! strchr (entry, SEP))
	/* Null entry. */
	memmove (entry, entry + entry_len, چپ);
      وگرنه
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
