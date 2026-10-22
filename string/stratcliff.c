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

#ವ್ಯಾಖ್ಯಾನಿಸು GNU_ಮೂಲ 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ CHAR
# define L(c) c
# define CHAR ಅಕ್ಷರ
# define MEMSET memset
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY ಸ್ಮರಣೆ_ನಕಲು
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿಸು STRINGIFY(s) STRINGIFY2 (s)
#ವ್ಯಾಖ್ಯಾನಿಸು STRINGIFY2(s) #s


ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  size_t ಗಾತ್ರ_2 = sysconf (_SC_PAGESIZE);
  size_t nchars = ಗಾತ್ರ_2 / ಗಾತ್ರ (CHAR);
  CHAR *adr;
  CHAR *dest;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  adr = (CHAR *) mmap (ಖಾಲಿ, 3 * ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
		       MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ಖಾಲಿ, 3 * ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
			MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  ಆದರೆ (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      ಆದರೆ (errno == ENOSYS)
	puts ("No test, mmap not available.");
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಬರೆ ("mmap failed: %m");
	  ಫಲಿತಾಂಶ = 1;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      size_t inner, ಮಧ್ಯ, outer, nchars64, max128;

      ಆದರೆ (nchars > 64)
	nchars64 = nchars - 64;
      ಇಲ್ಲದಿದ್ದರೆ
	nchars64 = 0;

      ಆದರೆ (nchars > 128)
	max128 = nchars - 128;
      ಇಲ್ಲದಿದ್ದರೆ
	max128 = 0;

      mprotect (adr, ಗಾತ್ರ_2, PROT_NONE);
      mprotect (adr + 2 * nchars, ಗಾತ್ರ_2, PROT_NONE);
      adr += nchars;

      mprotect (dest, ಗಾತ್ರ_2, PROT_NONE);
      mprotect (dest + 2 * nchars, ಗಾತ್ರ_2, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಆದರೆ (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* strnlen/wcsnlen test */
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಆದರೆ (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      ಆದರೆ (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  ಬರೆ ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ಫಲಿತಾಂಶ = 1;
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* strchr/wcschr test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      ಗಾಗಿ (inner = ಮಧ್ಯ; inner < nchars; ++inner)
		{
		  adr[ಮಧ್ಯ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  ಆದರೆ ((inner == ಮಧ್ಯ && cp != ಖಾಲಿ)
		      || (inner != ಮಧ್ಯ
			  && (cp - &adr[outer]) != ಮಧ್ಯ - outer))
		    {
		      ಬರೆ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, ಮಧ್ಯ, inner);
		      ಫಲಿತಾಂಶ = 1;
		    }

		  adr[inner] = L('T');
		  adr[ಮಧ್ಯ] = L('T');
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      ಆದರೆ (STRCHR (&adr[nchars - 1], L('\n')) != ಖಾಲಿ)
	{
	  ಬರೆ ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  ಫಲಿತಾಂಶ = 1;
	}

      /* strrchr/wcsrchr test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      ಗಾಗಿ (inner = ಮಧ್ಯ; inner < nchars; ++inner)
		{
		  adr[ಮಧ್ಯ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  ಆದರೆ ((inner == ಮಧ್ಯ && cp != ಖಾಲಿ)
		      || (inner != ಮಧ್ಯ
			  && (cp - &adr[outer]) != ಮಧ್ಯ - outer))
		    {
		      ಬರೆ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, ಮಧ್ಯ, inner);
		      ಫಲಿತಾಂಶ = 1;
		    }

		  adr[inner] = L('T');
		  adr[ಮಧ್ಯ] = L('T');
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* memchr test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * ಗಾತ್ರ_2);

	      ಆದರೆ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  ಬರೆ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, ಮಧ್ಯ);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  ಆದರೆ (cp != ಖಾಲಿ)
	    {
	      ಬರೆ ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* These functions only exist for single-byte characters.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WCSTEST
      /* rawmemchr test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      ಆದರೆ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  ಬರೆ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, ಮಧ್ಯ);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* memrchr test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      ಆದರೆ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  ಬರೆ ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, ಮಧ್ಯ);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  ಆದರೆ (cp != ಖಾಲಿ)
	    {
	      ಬರೆ ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
#ಆದರೆ_ಅಂತ್ಯ

      /* strcpy/wcscpy test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಆದರೆ (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* strcmp/wcscmp tests */
      ಗಾಗಿ (outer = 1; outer < 32; ++outer)
	ಗಾಗಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < 16; ++ಮಧ್ಯ)
	  {
	    MEMSET (adr + ಮಧ್ಯ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    ಆದರೆ (STRCMP (adr + ಮಧ್ಯ, dest + nchars - outer) <= 0)
	      {
		ಬರೆ ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ಮಧ್ಯ);
		ಫಲಿತಾಂಶ = 1;
	      }

	    ಆದರೆ (STRCMP (dest + nchars - outer, adr + ಮಧ್ಯ) >= 0)
	      {
		ಬರೆ ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ಮಧ್ಯ);
		ಫಲಿತಾಂಶ = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      ಗಾಗಿ (outer = 1; outer < 32; ++outer)
	ಗಾಗಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < 16; ++ಮಧ್ಯ)
	  {
	    MEMSET (adr + ಮಧ್ಯ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    ಗಾಗಿ (inner = 0; inner < outer; ++inner)
	      {
		ಆದರೆ (STRNCMP (adr + ಮಧ್ಯ, dest + nchars - outer, inner) != 0)
		  {
		    ಬರೆ ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ಮಧ್ಯ, inner);
		    ಫಲಿತಾಂಶ = 1;
		  }

		ಆದರೆ (STRNCMP (dest + nchars - outer, adr + ಮಧ್ಯ, inner) != 0)
		  {
		    ಬರೆ ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ಮಧ್ಯ, inner);
		    ಫಲಿತಾಂಶ = 1;
		  }
	      }

	    ಆದರೆ (STRNCMP (adr + ಮಧ್ಯ, dest + nchars - outer, outer) >= 0)
	      {
		ಬರೆ ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ಮಧ್ಯ);
		ಫಲಿತಾಂಶ = 1;
	      }

	    ಆದರೆ (STRNCMP (dest + nchars - outer, adr + ಮಧ್ಯ, outer) <= 0)
	      {
		ಬರೆ ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ಮಧ್ಯ);
		ಫಲಿತಾಂಶ = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ಗಾಗಿ (len = 0; len < nchars - outer; ++len)
	    {
	      ಆದರೆ (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  ಬರೆ ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  ಫಲಿತಾಂಶ = 1;
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      adr[nchars - 1] = L('\0');

      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      ಗಾಗಿ (len = 0; len < nchars - outer + 64; ++len)
		{
		  ಆದರೆ (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      ಬರೆ ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ಫಲಿತಾಂಶ = 1;
		    }
		  ಆದರೆ (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      ಬರೆ ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ಫಲಿತಾಂಶ = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* stpcpy/wcpcpy test */
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಆದರೆ ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  ಫಲಿತಾಂಶ = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ಗಾಗಿ (len = 0; len < nchars - outer; ++len)
	    {
	      ಆದರೆ (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  ಬರೆ ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  ಫಲಿತಾಂಶ = 1;
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      adr[nchars - 1] = L('\0');

      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('\0');

	      ಗಾಗಿ (inner = 0; inner < nchars - outer; ++ inner)
		{
		  ಆದರೆ ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, ಮಧ್ಯ - outer))
		    {
		      ಬರೆ ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, ಮಧ್ಯ, inner);
		      ಫಲಿತಾಂಶ = 1;
		    }
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* memcpy/wmemcpy test */
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಆದರೆ (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		ಫಲಿತಾಂಶ = 1;
	      }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* mempcpy/wmempcpy test */
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಆದರೆ (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		ಬರೆ ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		ಫಲಿತಾಂಶ = 1;
	      }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}

      /* This function only exists for single-byte characters.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      ಗಾಗಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಗಾಗಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಆದರೆ (memccpy (dest, &adr[outer], L('\1'), inner) != ಖಾಲಿ)
	      {
		ಬರೆ ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		ಫಲಿತಾಂಶ = 1;
	      }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
      ಗಾಗಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಗಾಗಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < nchars - outer; ++ಮಧ್ಯ)
	    {
	      memset (dest, L('\2'), ಮಧ್ಯ + 1);
	      ಗಾಗಿ (inner = 0; inner < ಮಧ್ಯ; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  ಆದರೆ (memccpy (dest, &adr[outer], '\1', ಮಧ್ಯ + 128)
		      !=  dest + inner + 1)
		    {
		      ಬರೆ ("\
			      memccpy flunked partial copy ಗಾಗಿ outer = %zu, ಮಧ್ಯ = %zu, inner = %zu\n",
			      outer, ಮಧ್ಯ, inner);
		      ಫಲಿತಾಂಶ = 1;
		    }
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dest[inner + 1] != L('\2'))
		    {
		      ಬರೆ ("\
			      memccpy copied too much ಗಾಗಿ outer = %zu, ಮಧ್ಯ = %zu, inner = %zu\n",
			      outer, ಮಧ್ಯ, inner);
		      ಫಲಿತಾಂಶ = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  ಆದರೆ (outer == 0)
	    ನಿಲ್ಲಿಸು;
	}
#ಆದರೆ_ಅಂತ್ಯ
    }

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
