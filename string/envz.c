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
अक्षर *
envz_entry (स्थिरांक अक्षर *envz, माप_प्रकार envz_len, स्थिरांक अक्षर *name)
{
  पर्यंत (envz_len)
    {
      स्थिरांक अक्षर *p = name;
      स्थिरांक अक्षर *entry = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      पर्यंत (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      जर ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	परत (अक्षर *) entry;

      /* No match, skip to the next entry.  */
      पर्यंत (envz_len && *envz)
	envz++, envz_len--;
      जर (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  परत रिक्त;
}
libc_hidden_def (envz_entry)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
अक्षर *
envz_get (स्थिरांक अक्षर *envz, माप_प्रकार envz_len, स्थिरांक अक्षर *name)
{
  अक्षर *entry = envz_entry (envz, envz_len, name);
  जर (entry)
    {
      पर्यंत (*entry && *entry != SEP)
	entry++;
      जर (*entry)
	entry++;
      अन्यथा
	entry = रिक्त;		/* A null entry.  */
    }
  परत entry;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
शून्य
envz_remove (अक्षर **envz, माप_प्रकार *envz_len, स्थिरांक अक्षर *name)
{
  अक्षर *entry = envz_entry (*envz, *envz_len, name);
  जर (entry)
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
envz_add (अक्षर **envz, माप_प्रकार *envz_len, स्थिरांक अक्षर *name, स्थिरांक अक्षर *मूल्य)
{
  envz_remove (envz, envz_len, name);

  जर (मूल्य)
    /* Add the new value, if there is one.  */
    {
      माप_प्रकार name_len = म_माप (name);
      माप_प्रकार मूल्य_len = म_माप (मूल्य);
      माप_प्रकार old_envz_len = *envz_len;
      माप_प्रकार new_envz_len = old_envz_len + name_len + 1 + मूल्य_len + 1;
      अक्षर *new_envz = पुनः_स्मृति (*envz, new_envz_len);

      जर (new_envz)
	{
	  स_नकल (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  स_नकल (new_envz + old_envz_len + name_len + 1, मूल्य, मूल्य_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  परत 0;
	}
      अन्यथा
	परत ENOMEM;
    }
  अन्यथा
    /* Add a null entry.  */
    परत __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_merge (अक्षर **envz, माप_प्रकार *envz_len, स्थिरांक अक्षर *envz2,
	    माप_प्रकार envz2_len, पूर्णांक override)
{
  error_t err = 0;

  पर्यंत (envz2_len && ! err)
    {
      अक्षर *old = envz_entry (*envz, *envz_len, envz2);
      माप_प्रकार new_len = म_माप (envz2) + 1;

      जर (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      अन्यथा जर (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  परत err;
}

/* Remove null entries.  */
शून्य
envz_strip (अक्षर **envz, माप_प्रकार *envz_len)
{
  अक्षर *entry = *envz;
  माप_प्रकार डावा = *envz_len;
  पर्यंत (डावा)
    {
      माप_प्रकार entry_len = म_माप (entry) + 1;
      डावा -= entry_len;
      जर (! म_अक्षर (entry, SEP))
	/* Null entry. */
	स_हटाओ (entry, entry + entry_len, डावा);
      अन्यथा
	entry += entry_len;
    }
  *envz_len = entry - *envz;
}
