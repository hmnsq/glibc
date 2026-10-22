/* Test for string function add boundaries of usable memory.
   Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GNU_ਸਰੋਤ 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __USE_STRING_INLINES

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ CHAR
# define L(c) c
# define CHAR ਅੱਖਰ
# define MEMSET memset
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY ਸਮ੍ਰਿਤੀ_ਨਕਲ
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP ਲੜੀ_ਤੁਲਨਾ
#ਜੇ_ਅੰਤ


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRINGIFY(s) STRINGIFY2 (s)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRINGIFY2(s) #s


ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  size_t ਮਾਪ = sysconf (_SC_PAGESIZE);
  size_t nchars = ਮਾਪ / ਆਕਾਰ (CHAR);
  CHAR *adr;
  CHAR *dest;
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  adr = (CHAR *) mmap (ਨਿਰਾ, 3 * ਮਾਪ, PROT_READ | PROT_WRITE,
		       MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ਨਿਰਾ, 3 * ਮਾਪ, PROT_READ | PROT_WRITE,
			MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);
  ਜੇ (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      ਜੇ (errno == ENOSYS)
	puts ("No test, mmap not available.");
      ਨਹੀਂਤਾਂ
	{
	  ਲਿਖੋ ("mmap failed: %m");
	  ਨਤੀਜਾ = 1;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      size_t inner, ਵਿਚਕਾਰ, outer, nchars64, max128;

      ਜੇ (nchars > 64)
	nchars64 = nchars - 64;
      ਨਹੀਂਤਾਂ
	nchars64 = 0;

      ਜੇ (nchars > 128)
	max128 = nchars - 128;
      ਨਹੀਂਤਾਂ
	max128 = 0;

      mprotect (adr, ਮਾਪ, PROT_NONE);
      mprotect (adr + 2 * nchars, ਮਾਪ, PROT_NONE);
      adr += nchars;

      mprotect (dest, ਮਾਪ, PROT_NONE);
      mprotect (dest + 2 * nchars, ਮਾਪ, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ਜੇ (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  ਨਤੀਜਾ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* strnlen/wcsnlen test */
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ਜੇ (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ਨਤੀਜਾ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      ਜੇ (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  ਲਿਖੋ ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ਨਤੀਜਾ = 1;
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* strchr/wcschr test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      ਲਈ (inner = ਵਿਚਕਾਰ; inner < nchars; ++inner)
		{
		  adr[ਵਿਚਕਾਰ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  ਜੇ ((inner == ਵਿਚਕਾਰ && cp != ਨਿਰਾ)
		      || (inner != ਵਿਚਕਾਰ
			  && (cp - &adr[outer]) != ਵਿਚਕਾਰ - outer))
		    {
		      ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, ਵਿਚਕਾਰ, inner);
		      ਨਤੀਜਾ = 1;
		    }

		  adr[inner] = L('T');
		  adr[ਵਿਚਕਾਰ] = L('T');
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      ਜੇ (STRCHR (&adr[nchars - 1], L('\n')) != ਨਿਰਾ)
	{
	  ਲਿਖੋ ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  ਨਤੀਜਾ = 1;
	}

      /* strrchr/wcsrchr test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      ਲਈ (inner = ਵਿਚਕਾਰ; inner < nchars; ++inner)
		{
		  adr[ਵਿਚਕਾਰ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  ਜੇ ((inner == ਵਿਚਕਾਰ && cp != ਨਿਰਾ)
		      || (inner != ਵਿਚਕਾਰ
			  && (cp - &adr[outer]) != ਵਿਚਕਾਰ - outer))
		    {
		      ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, ਵਿਚਕਾਰ, inner);
		      ਨਤੀਜਾ = 1;
		    }

		  adr[inner] = L('T');
		  adr[ਵਿਚਕਾਰ] = L('T');
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* memchr test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      adr[ਵਿਚਕਾਰ] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * ਮਾਪ);

	      ਜੇ (cp - &adr[outer] != ਵਿਚਕਾਰ - outer)
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, ਵਿਚਕਾਰ);
		  ਨਤੀਜਾ = 1;
		}

	      adr[ਵਿਚਕਾਰ] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  ਜੇ (cp != ਨਿਰਾ)
	    {
	      ਲਿਖੋ ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* These functions only exist for single-byte characters.  */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WCSTEST
      /* rawmemchr test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      adr[ਵਿਚਕਾਰ] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      ਜੇ (cp - &adr[outer] != ਵਿਚਕਾਰ - outer)
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, ਵਿਚਕਾਰ);
		  ਨਤੀਜਾ = 1;
		}

	      adr[ਵਿਚਕਾਰ] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* memrchr test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      adr[ਵਿਚਕਾਰ] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      ਜੇ (cp - &adr[outer] != ਵਿਚਕਾਰ - outer)
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, ਵਿਚਕਾਰ);
		  ਨਤੀਜਾ = 1;
		}

	      adr[ਵਿਚਕਾਰ] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  ਜੇ (cp != ਨਿਰਾ)
	    {
	      ਲਿਖੋ ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
#ਜੇ_ਅੰਤ

      /* strcpy/wcscpy test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ਜੇ (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  ਨਤੀਜਾ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* strcmp/wcscmp tests */
      ਲਈ (outer = 1; outer < 32; ++outer)
	ਲਈ (ਵਿਚਕਾਰ = 0; ਵਿਚਕਾਰ < 16; ++ਵਿਚਕਾਰ)
	  {
	    MEMSET (adr + ਵਿਚਕਾਰ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    ਜੇ (STRCMP (adr + ਵਿਚਕਾਰ, dest + nchars - outer) <= 0)
	      {
		ਲਿਖੋ ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ਵਿਚਕਾਰ);
		ਨਤੀਜਾ = 1;
	      }

	    ਜੇ (STRCMP (dest + nchars - outer, adr + ਵਿਚਕਾਰ) >= 0)
	      {
		ਲਿਖੋ ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ਵਿਚਕਾਰ);
		ਨਤੀਜਾ = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      ਲਈ (outer = 1; outer < 32; ++outer)
	ਲਈ (ਵਿਚਕਾਰ = 0; ਵਿਚਕਾਰ < 16; ++ਵਿਚਕਾਰ)
	  {
	    MEMSET (adr + ਵਿਚਕਾਰ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    ਲਈ (inner = 0; inner < outer; ++inner)
	      {
		ਜੇ (STRNCMP (adr + ਵਿਚਕਾਰ, dest + nchars - outer, inner) != 0)
		  {
		    ਲਿਖੋ ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ਵਿਚਕਾਰ, inner);
		    ਨਤੀਜਾ = 1;
		  }

		ਜੇ (STRNCMP (dest + nchars - outer, adr + ਵਿਚਕਾਰ, inner) != 0)
		  {
		    ਲਿਖੋ ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ਵਿਚਕਾਰ, inner);
		    ਨਤੀਜਾ = 1;
		  }
	      }

	    ਜੇ (STRNCMP (adr + ਵਿਚਕਾਰ, dest + nchars - outer, outer) >= 0)
	      {
		ਲਿਖੋ ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ਵਿਚਕਾਰ);
		ਨਤੀਜਾ = 1;
	      }

	    ਜੇ (STRNCMP (dest + nchars - outer, adr + ਵਿਚਕਾਰ, outer) <= 0)
	      {
		ਲਿਖੋ ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ਵਿਚਕਾਰ);
		ਨਤੀਜਾ = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ਲਈ (len = 0; len < nchars - outer; ++len)
	    {
	      ਜੇ (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  ਲਿਖੋ ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  ਨਤੀਜਾ = 1;
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      adr[nchars - 1] = L('\0');

      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      ਲਈ (len = 0; len < nchars - outer + 64; ++len)
		{
		  ਜੇ (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ਨਤੀਜਾ = 1;
		    }
		  ਜੇ (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      ਲਿਖੋ ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ਨਤੀਜਾ = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* stpcpy/wcpcpy test */
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ਜੇ ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  ਨਤੀਜਾ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ਲਈ (len = 0; len < nchars - outer; ++len)
	    {
	      ਜੇ (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  ਲਿਖੋ ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  ਨਤੀਜਾ = 1;
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      adr[nchars - 1] = L('\0');

      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = MAX (outer, nchars64); ਵਿਚਕਾਰ < nchars; ++ਵਿਚਕਾਰ)
	    {
	      adr[ਵਿਚਕਾਰ] = L('\0');

	      ਲਈ (inner = 0; inner < nchars - outer; ++ inner)
		{
		  ਜੇ ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, ਵਿਚਕਾਰ - outer))
		    {
		      ਲਿਖੋ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, ਵਿਚਕਾਰ, inner);
		      ਨਤੀਜਾ = 1;
		    }
		}

	      adr[ਵਿਚਕਾਰ] = L('T');
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* memcpy/wmemcpy test */
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  ਲਈ (inner = 0; inner < nchars - outer; ++inner)
	    ਜੇ (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		ਨਤੀਜਾ = 1;
	      }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* mempcpy/wmempcpy test */
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  ਲਈ (inner = 0; inner < nchars - outer; ++inner)
	    ਜੇ (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		ਲਿਖੋ ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		ਨਤੀਜਾ = 1;
	      }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}

      /* This function only exists for single-byte characters.  */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      ਲਈ (outer = nchars; outer >= max128; --outer)
	{
	  ਲਈ (inner = 0; inner < nchars - outer; ++inner)
	    ਜੇ (memccpy (dest, &adr[outer], L('\1'), inner) != ਨਿਰਾ)
	      {
		ਲਿਖੋ ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		ਨਤੀਜਾ = 1;
	      }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
      ਲਈ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ਲਈ (ਵਿਚਕਾਰ = 0; ਵਿਚਕਾਰ < nchars - outer; ++ਵਿਚਕਾਰ)
	    {
	      memset (dest, L('\2'), ਵਿਚਕਾਰ + 1);
	      ਲਈ (inner = 0; inner < ਵਿਚਕਾਰ; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  ਜੇ (memccpy (dest, &adr[outer], '\1', ਵਿਚਕਾਰ + 128)
		      !=  dest + inner + 1)
		    {
		      ਲਿਖੋ ("\
			      memccpy flunked partial copy ਲਈ outer = %zu, ਵਿਚਕਾਰ = %zu, inner = %zu\n",
			      outer, ਵਿਚਕਾਰ, inner);
		      ਨਤੀਜਾ = 1;
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (dest[inner + 1] != L('\2'))
		    {
		      ਲਿਖੋ ("\
			      memccpy copied too much ਲਈ outer = %zu, ਵਿਚਕਾਰ = %zu, inner = %zu\n",
			      outer, ਵਿਚਕਾਰ, inner);
		      ਨਤੀਜਾ = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  ਜੇ (outer == 0)
	    ਰੋਕੋ;
	}
#ਜੇ_ਅੰਤ
    }

  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
