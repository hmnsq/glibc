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

#అన్తర్భావ <malloc.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <envz.h>

/* The character separating names from values in an envz.  */
#నిర్వచించు SEP '='

/* Returns a pointer to the entry in ENVZ for NAME, or 0 if there is none.
   If NAME contains the separator character, only the portion before it is
   used in the comparison.  */
అక్షరం *
envz_నమోదు (స్థిరరాశి అక్షరం *envz, size_t envz_len, స్థిరరాశి అక్షరం *name)
{
  అయితే (envz_len)
    {
      స్థిరరాశి అక్షరం *p = name;
      స్థిరరాశి అక్షరం *నమోదు_2 = envz;	/* Start of this entry. */

      /* See how far NAME and ENTRY match.  */
      అయితే (envz_len && *p == *envz && *p && *p != SEP)
	p++, envz++, envz_len--;

      ఒకవేళ ((*envz == '\0' || *envz == SEP) && (*p == '\0' || *p == SEP))
	/* Bingo! */
	తిరిగి (అక్షరం *) నమోదు_2;

      /* No match, skip to the next entry.  */
      అయితే (envz_len && *envz)
	envz++, envz_len--;
      ఒకవేళ (envz_len)
	envz++, envz_len--;	/* skip '\0' */
    }

  తిరిగి ఖాళీ;
}
libc_hidden_def (envz_నమోదు)

/* Returns a pointer to the value portion of the entry in ENVZ for NAME, or 0
   if there is none.  */
అక్షరం *
envz_get (స్థిరరాశి అక్షరం *envz, size_t envz_len, స్థిరరాశి అక్షరం *name)
{
  అక్షరం *నమోదు_2 = envz_నమోదు (envz, envz_len, name);
  ఒకవేళ (నమోదు_2)
    {
      అయితే (*నమోదు_2 && *నమోదు_2 != SEP)
	నమోదు_2++;
      ఒకవేళ (*నమోదు_2)
	నమోదు_2++;
      లేకపోతే
	నమోదు_2 = ఖాళీ;		/* A null entry.  */
    }
  తిరిగి నమోదు_2;
}

/* Remove the entry for NAME from ENVZ & ENVZ_LEN, if any.  */
శూన్య
envz_remove (అక్షరం **envz, size_t *envz_len, స్థిరరాశి అక్షరం *name)
{
  అక్షరం *నమోదు_2 = envz_నమోదు (*envz, *envz_len, name);
  ఒకవేళ (నమోదు_2)
    argz_delete (envz, envz_len, నమోదు_2);
}
libc_hidden_def (envz_remove)

/* Adds an entry for NAME with value VALUE to ENVZ & ENVZ_LEN.  If an entry
   with the same name already exists in ENVZ, it is removed.  If VALUE is
   NULL, then the new entry will a special null one, for which envz_get will
   return NULL, although envz_entry will still return an entry; this is handy
   because when merging with another envz, the null entry can override an
   entry in the other one.  Null entries can be removed with envz_strip ().  */
error_t
envz_కూడు (అక్షరం **envz, size_t *envz_len, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *విలువ)
{
  envz_remove (envz, envz_len, name);

  ఒకవేళ (విలువ)
    /* Add the new value, if there is one.  */
    {
      size_t name_len = అక్షరశ్రేణి_పొడవు (name);
      size_t విలువ_len = అక్షరశ్రేణి_పొడవు (విలువ);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + విలువ_len + 1;
      అక్షరం *new_envz = realloc (*envz, new_envz_len);

      ఒకవేళ (new_envz)
	{
	  జ్ఞాపకం_నకలు (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  జ్ఞాపకం_నకలు (new_envz + old_envz_len + name_len + 1, విలువ, విలువ_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  తిరిగి 0;
	}
      లేకపోతే
	తిరిగి ENOMEM;
    }
  లేకపోతే
    /* Add a null entry.  */
    తిరిగి __argz_add (envz, envz_len, name);
}

/* Adds each entry in ENVZ2 to ENVZ & ENVZ_LEN, as if with envz_add().  If
   OVERRIDE is true, then values in ENVZ2 will supersede those with the same
   name in ENV, otherwise not.  */
error_t
envz_విలీనం (అక్షరం **envz, size_t *envz_len, స్థిరరాశి అక్షరం *envz2,
	    size_t envz2_len, పూర్ణాంకం override)
{
  error_t err = 0;

  అయితే (envz2_len && ! err)
    {
      అక్షరం *old = envz_నమోదు (*envz, *envz_len, envz2);
      size_t new_len = అక్షరశ్రేణి_పొడవు (envz2) + 1;

      ఒకవేళ (! old)
	err = __argz_append (envz, envz_len, envz2, new_len);
      లేకపోతే ఒకవేళ (override)
	{
	  argz_delete (envz, envz_len, old);
	  err = __argz_append (envz, envz_len, envz2, new_len);
	}

      envz2 += new_len;
      envz2_len -= new_len;
    }

  తిరిగి err;
}

/* Remove null entries.  */
శూన్య
envz_strip (అక్షరం **envz, size_t *envz_len)
{
  అక్షరం *నమోదు_2 = *envz;
  size_t ఎడమ = *envz_len;
  అయితే (ఎడమ)
    {
      size_t నమోదు_len = అక్షరశ్రేణి_పొడవు (నమోదు_2) + 1;
      ఎడమ -= నమోదు_len;
      ఒకవేళ (! strchr (నమోదు_2, SEP))
	/* Null entry. */
	memmove (నమోదు_2, నమోదు_2 + నమోదు_len, ఎడమ);
      లేకపోతే
	నమోదు_2 += నమోదు_len;
    }
  *envz_len = నమోదు_2 - *envz;
}
