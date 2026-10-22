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
#تعریف_کرو SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
حرف *
envz_اندراج (ثابت حرف *envz, size_t envz_len, ثابت حرف *name)
{
  جب (envz_len)
    {
      ثابت حرف *p = name;
      ثابت حرف *اندراج_2 = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      جب (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      اگر ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	واپس (حرف *) اندراج_2;

      /* No match, skip to the next entry.  */
      جب (envz_len && *envz)
	envz++, envz_len--;
      اگر (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  واپس تہی;
}
libc_hidden_def (envz_اندراج)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
حرف *
envz_get (ثابت حرف *envz, size_t envz_len, ثابت حرف *name)
{
  حرف *اندراج_2 = envz_اندراج (envz, envz_len, name);
  اگر (اندراج_2)
    {
      جب (*اندراج_2 && *اندراج_2 != SEP)
	اندراج_2++;
      اگر (*اندراج_2)
	اندراج_2++;
      ورنہ
	اندراج_2 = تہی;		/* A null entry.  */
    }
  واپس اندراج_2;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
خالی
envz_remove (حرف **envz, size_t *envz_len, ثابت حرف *name)
{
  حرف *اندراج_2 = envz_اندراج (*envz, *envz_len, name);
  اگر (اندراج_2)
    argz_delete (envz, envz_len, اندراج_2);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_جوڑو (حرف **envz, size_t *envz_len, ثابت حرف *name, ثابت حرف *قدر)
{
  envz_remove (envz, envz_len, name);

  اگر (قدر)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = لڑی_لمبائی (name);
      size_t قدر_len = لڑی_لمبائی (قدر);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + قدر_len + 1;
      حرف *new_envz = realloc (*envz, new_envz_len);

      اگر (new_envz)
	{
	  حافظہ_نقل (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  حافظہ_نقل (new_envz + old_envz_len + name_len + 1, قدر, قدر_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  واپس 0;
	}
      ورنہ
	واپس ENOMEM;
    }
  ورنہ
    /* Add a null entry.  */
    واپس __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_ملاؤ (حرف **envz, size_t *envz_len, ثابت حرف *envz2,
	    size_t envz2_len, صحیح override)
{
  error_t err = 0;

  جب (envz2_len && ! err)
    {
      حرف *old = envz_اندراج (*envz, *envz_len, envz2);
      size_t new_len = لڑی_لمبائی (envz2) + 1;

      اگر (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      ورنہ اگر (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  واپس err;
}

/* Remove null entries.  */
خالی
envz_strip (حرف **envz, size_t *envz_len)
{
  حرف *اندراج_2 = *envz;
  size_t بایاں = *envz_len;
  جب (بایاں)
    {
      size_t اندراج_len = لڑی_لمبائی (اندراج_2) + 1;
      بایاں -= اندراج_len;
      اگر (! strchr (اندراج_2, SEP))
	/* Null entry. */
	memmove (اندراج_2, اندراج_2 + اندراج_len, بایاں);
      ورنہ
	اندراج_2 += اندراج_len;
    }
  *envz_len = اندراج_2 - *envz;
}
