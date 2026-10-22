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

#ಅನ್ತರ್ಭಾವ <malloc.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <envz.h>

/* The character separating names from values in an envz.  */
#ವ್ಯಾಖ್ಯಾನಿಸು SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
ಅಕ್ಷರ *
envz_ನಮೂದು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *envz, size_t envz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
  ಆಗ (envz_len)
    {
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = name;
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ನಮೂದು = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      ಆಗ (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      ಆದರೆ ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) ನಮೂದು;

      /* No match, skip to the next entry.  */
      ಆಗ (envz_len && *envz)
	envz++, envz_len--;
      ಆದರೆ (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
libc_hidden_def (envz_ನಮೂದು)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
ಅಕ್ಷರ *
envz_get (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *envz, size_t envz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
  ಅಕ್ಷರ *ನಮೂದು = envz_ನಮೂದು (envz, envz_len, name);
  ಆದರೆ (ನಮೂದು)
    {
      ಆಗ (*ನಮೂದು && *ನಮೂದು != SEP)
	ನಮೂದು++;
      ಆದರೆ (*ನಮೂದು)
	ನಮೂದು++;
      ಇಲ್ಲದಿದ್ದರೆ
	ನಮೂದು = ಖಾಲಿ;		/* A null entry.  */
    }
  ಹಿಂತಿರುಗಿ ನಮೂದು;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
ಶೂನ್ಯ
envz_remove (ಅಕ್ಷರ **envz, size_t *envz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
  ಅಕ್ಷರ *ನಮೂದು = envz_ನಮೂದು (*envz, *envz_len, name);
  ಆದರೆ (ನಮೂದು)
    argz_delete (envz, envz_len, ನಮೂದು);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_ಕೂಡಿಸು (ಅಕ್ಷರ **envz, size_t *envz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮೌಲ್ಯ)
{
  envz_remove (envz, envz_len, name);

  ಆದರೆ (ಮೌಲ್ಯ)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (name);
      size_t ಮೌಲ್ಯ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಮೌಲ್ಯ);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + ಮೌಲ್ಯ_len + 1;
      ಅಕ್ಷರ *new_envz = realloc (*envz, new_envz_len);

      ಆದರೆ (new_envz)
	{
	  ಸ್ಮರಣೆ_ನಕಲು (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  ಸ್ಮರಣೆ_ನಕಲು (new_envz + old_envz_len + name_len + 1, ಮೌಲ್ಯ, ಮೌಲ್ಯ_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  ಹಿಂತಿರುಗಿ 0;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ಹಿಂತಿರುಗಿ ENOMEM;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    /* Add a null entry.  */
    ಹಿಂತಿರುಗಿ __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_ವಿಲೀನ (ಅಕ್ಷರ **envz, size_t *envz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *envz2,
	    size_t envz2_len, ಪೂರ್ಣಾಂಕ override)
{
  error_t err = 0;

  ಆಗ (envz2_len && ! err)
    {
      ಅಕ್ಷರ *old = envz_ನಮೂದು (*envz, *envz_len, envz2);
      size_t new_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (envz2) + 1;

      ಆದರೆ (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  ಹಿಂತಿರುಗಿ err;
}

/* Remove null entries.  */
ಶೂನ್ಯ
envz_strip (ಅಕ್ಷರ **envz, size_t *envz_len)
{
  ಅಕ್ಷರ *ನಮೂದು = *envz;
  size_t ಎಡ = *envz_len;
  ಆಗ (ಎಡ)
    {
      size_t ನಮೂದು_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ನಮೂದು) + 1;
      ಎಡ -= ನಮೂದು_len;
      ಆದರೆ (! strchr (ನಮೂದು, SEP))
	/* Null entry. */
	memmove (ನಮೂದು, ನಮೂದು + ನಮೂದು_len, ಎಡ);
      ಇಲ್ಲದಿದ್ದರೆ
	ನಮೂದು += ನಮೂದು_len;
    }
  *envz_len = ನಮೂದು - *envz;
}
