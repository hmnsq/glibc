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

#ضمن <malloc.h>
#ضمن <string.h>

#ضمن <envz.h>

/* The character separating names from values in an envz.  */
#وصف_ڪريو SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
حرف *
envz_داخلا (ثابت حرف *envz, size_t envz_len, ثابت حرف *name)
{
  طالما (envz_len)
    {
      ثابت حرف *p = name;
      ثابت حرف *داخلا = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      طالما (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      إذا ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	أرجع (حرف *) داخلا;

      /* No match, skip to the next entry.  */
      طالما (envz_len && *envz)
	envz++, envz_len--;
      إذا (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  أرجع عدم;
}
libc_hidden_def (envz_داخلا)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
حرف *
envz_get (ثابت حرف *envz, size_t envz_len, ثابت حرف *name)
{
  حرف *داخلا = envz_داخلا (envz, envz_len, name);
  إذا (داخلا)
    {
      طالما (*داخلا && *داخلا != SEP)
	داخلا++;
      إذا (*داخلا)
	داخلا++;
      وإلا
	داخلا = عدم;		/* A null entry.  */
    }
  أرجع داخلا;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
فراغ
envz_remove (حرف **envz, size_t *envz_len, ثابت حرف *name)
{
  حرف *داخلا = envz_داخلا (*envz, *envz_len, name);
  إذا (داخلا)
    argz_delete (envz, envz_len, داخلا);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_جوڙيو (حرف **envz, size_t *envz_len, ثابت حرف *name, ثابت حرف *قدر)
{
  envz_remove (envz, envz_len, name);

  إذا (قدر)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = لڙي_ڊيگهه (name);
      size_t قدر_len = لڙي_ڊيگهه (قدر);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + قدر_len + 1;
      حرف *new_envz = realloc (*envz, new_envz_len);

      إذا (new_envz)
	{
	  يادگيري_نقل (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  يادگيري_نقل (new_envz + old_envz_len + name_len + 1, قدر, قدر_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  أرجع 0;
	}
      وإلا
	أرجع ENOMEM;
    }
  وإلا
    /* Add a null entry.  */
    أرجع __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_ملايو (حرف **envz, size_t *envz_len, ثابت حرف *envz2,
	    size_t envz2_len, صحيح override)
{
  error_t err = 0;

  طالما (envz2_len && ! err)
    {
      حرف *old = envz_داخلا (*envz, *envz_len, envz2);
      size_t new_len = لڙي_ڊيگهه (envz2) + 1;

      إذا (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      وإلا إذا (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  أرجع err;
}

/* Remove null entries.  */
فراغ
envz_strip (حرف **envz, size_t *envz_len)
{
  حرف *داخلا = *envz;
  size_t کاٻو = *envz_len;
  طالما (کاٻو)
    {
      size_t داخلا_len = لڙي_ڊيگهه (داخلا) + 1;
      کاٻو -= داخلا_len;
      إذا (! strchr (داخلا, SEP))
	/* Null entry. */
	memmove (داخلا, داخلا + داخلا_len, کاٻو);
      وإلا
	داخلا += داخلا_len;
    }
  *envz_len = داخلا - *envz;
}
