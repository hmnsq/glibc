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

#ਅਨ੍ਤਰ੍ਭਾਵ <malloc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <envz.h>

/* The character separating names from values in an envz.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
ਅੱਖਰ *
envz_ਇੰਦਰਾਜ (ਅਚਲ ਅੱਖਰ *envz, size_t envz_len, ਅਚਲ ਅੱਖਰ *name)
{
  ਜਦੋਂ (envz_len)
    {
      ਅਚਲ ਅੱਖਰ *p = name;
      ਅਚਲ ਅੱਖਰ *ਇੰਦਰਾਜ = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      ਜਦੋਂ (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      ਜੇ ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	ਵਾਪਸ (ਅੱਖਰ *) ਇੰਦਰਾਜ;

      /* No match, skip to the next entry.  */
      ਜਦੋਂ (envz_len && *envz)
	envz++, envz_len--;
      ਜੇ (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  ਵਾਪਸ ਨਿਰਾ;
}
libc_hidden_def (envz_ਇੰਦਰਾਜ)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
ਅੱਖਰ *
envz_get (ਅਚਲ ਅੱਖਰ *envz, size_t envz_len, ਅਚਲ ਅੱਖਰ *name)
{
  ਅੱਖਰ *ਇੰਦਰਾਜ = envz_ਇੰਦਰਾਜ (envz, envz_len, name);
  ਜੇ (ਇੰਦਰਾਜ)
    {
      ਜਦੋਂ (*ਇੰਦਰਾਜ && *ਇੰਦਰਾਜ != SEP)
	ਇੰਦਰਾਜ++;
      ਜੇ (*ਇੰਦਰਾਜ)
	ਇੰਦਰਾਜ++;
      ਨਹੀਂਤਾਂ
	ਇੰਦਰਾਜ = ਨਿਰਾ;		/* A null entry.  */
    }
  ਵਾਪਸ ਇੰਦਰਾਜ;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
ਖਾਲੀ
envz_remove (ਅੱਖਰ **envz, size_t *envz_len, ਅਚਲ ਅੱਖਰ *name)
{
  ਅੱਖਰ *ਇੰਦਰਾਜ = envz_ਇੰਦਰਾਜ (*envz, *envz_len, name);
  ਜੇ (ਇੰਦਰਾਜ)
    argz_delete (envz, envz_len, ਇੰਦਰਾਜ);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_ਜੋੜੋ (ਅੱਖਰ **envz, size_t *envz_len, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *ਮੁੱਲ)
{
  envz_remove (envz, envz_len, name);

  ਜੇ (ਮੁੱਲ)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = ਲੜੀ_ਲੰਬਾਈ (name);
      size_t ਮੁੱਲ_len = ਲੜੀ_ਲੰਬਾਈ (ਮੁੱਲ);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + ਮੁੱਲ_len + 1;
      ਅੱਖਰ *new_envz = realloc (*envz, new_envz_len);

      ਜੇ (new_envz)
	{
	  ਸਮ੍ਰਿਤੀ_ਨਕਲ (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  ਸਮ੍ਰਿਤੀ_ਨਕਲ (new_envz + old_envz_len + name_len + 1, ਮੁੱਲ, ਮੁੱਲ_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  ਵਾਪਸ 0;
	}
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ ENOMEM;
    }
  ਨਹੀਂਤਾਂ
    /* Add a null entry.  */
    ਵਾਪਸ __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_ਮਿਲਾਓ (ਅੱਖਰ **envz, size_t *envz_len, ਅਚਲ ਅੱਖਰ *envz2,
	    size_t envz2_len, ਪੂਰਨ override)
{
  error_t err = 0;

  ਜਦੋਂ (envz2_len && ! err)
    {
      ਅੱਖਰ *old = envz_ਇੰਦਰਾਜ (*envz, *envz_len, envz2);
      size_t new_len = ਲੜੀ_ਲੰਬਾਈ (envz2) + 1;

      ਜੇ (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      ਨਹੀਂਤਾਂ ਜੇ (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  ਵਾਪਸ err;
}

/* Remove null entries.  */
ਖਾਲੀ
envz_strip (ਅੱਖਰ **envz, size_t *envz_len)
{
  ਅੱਖਰ *ਇੰਦਰਾਜ = *envz;
  size_t ਖੱਬਾ = *envz_len;
  ਜਦੋਂ (ਖੱਬਾ)
    {
      size_t ਇੰਦਰਾਜ_len = ਲੜੀ_ਲੰਬਾਈ (ਇੰਦਰਾਜ) + 1;
      ਖੱਬਾ -= ਇੰਦਰਾਜ_len;
      ਜੇ (! strchr (ਇੰਦਰਾਜ, SEP))
	/* Null entry. */
	memmove (ਇੰਦਰਾਜ, ਇੰਦਰਾਜ + ਇੰਦਰਾਜ_len, ਖੱਬਾ);
      ਨਹੀਂਤਾਂ
	ਇੰਦਰਾਜ += ਇੰਦਰਾਜ_len;
    }
  *envz_len = ਇੰਦਰਾਜ - *envz;
}
