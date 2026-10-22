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

#define _GNU_SOURCE 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR ವರ್ಣ
# define MEMSET memset
# define STRLEN strlen
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY memcpy
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP strncmp
#endif


#define STRINGIFY(s) STRINGIFY2 (s)
#define STRINGIFY2(s) #s


ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / ಪರಿಮಾಣ (CHAR);
  CHAR *adr;
  CHAR *dest;
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  adr = (CHAR *) mmap (ರಿಕ್ತ, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ರಿಕ್ತ, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  ಯದಿ (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      ಯದಿ (errno == ENOSYS)
	puts ("No test, mmap not available.");
      ಅನ್ಯಥಾ
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  ಅನ್ಯಥಾ
    {
      size_t inner, ಮಧ್ಯ, outer, nchars64, max128;

      ಯದಿ (nchars > 64)
	nchars64 = nchars - 64;
      ಅನ್ಯಥಾ
	nchars64 = 0;

      ಯದಿ (nchars > 128)
	max128 = nchars - 128;
      ಅನ್ಯಥಾ
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಯದಿ (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* strnlen/wcsnlen test */
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಯದಿ (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      ಯದಿ (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* strchr/wcschr test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      ಪ್ರತಿ (inner = ಮಧ್ಯ; inner < nchars; ++inner)
		{
		  adr[ಮಧ್ಯ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  ಯದಿ ((inner == ಮಧ್ಯ && cp != ರಿಕ್ತ)
		      || (inner != ಮಧ್ಯ
			  && (cp - &adr[outer]) != ಮಧ್ಯ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, ಮಧ್ಯ, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ಮಧ್ಯ] = L('T');
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      ಯದಿ (STRCHR (&adr[nchars - 1], L('\n')) != ರಿಕ್ತ)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      ಪ್ರತಿ (inner = ಮಧ್ಯ; inner < nchars; ++inner)
		{
		  adr[ಮಧ್ಯ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  ಯದಿ ((inner == ಮಧ್ಯ && cp != ರಿಕ್ತ)
		      || (inner != ಮಧ್ಯ
			  && (cp - &adr[outer]) != ಮಧ್ಯ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, ಮಧ್ಯ, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ಮಧ್ಯ] = L('T');
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* memchr test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      ಯದಿ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, ಮಧ್ಯ);
		  result = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  ಯದಿ (cp != ರಿಕ್ತ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      ಯದಿ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, ಮಧ್ಯ);
		  result = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* memrchr test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      ಯದಿ (cp - &adr[outer] != ಮಧ್ಯ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, ಮಧ್ಯ);
		  result = 1;
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  ಯದಿ (cp != ರಿಕ್ತ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
#endif

      /* strcpy/wcscpy test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಯದಿ (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* strcmp/wcscmp tests */
      ಪ್ರತಿ (outer = 1; outer < 32; ++outer)
	ಪ್ರತಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < 16; ++ಮಧ್ಯ)
	  {
	    MEMSET (adr + ಮಧ್ಯ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    ಯದಿ (STRCMP (adr + ಮಧ್ಯ, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ಮಧ್ಯ);
		result = 1;
	      }

	    ಯದಿ (STRCMP (dest + nchars - outer, adr + ಮಧ್ಯ) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ಮಧ್ಯ);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      ಪ್ರತಿ (outer = 1; outer < 32; ++outer)
	ಪ್ರತಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < 16; ++ಮಧ್ಯ)
	  {
	    MEMSET (adr + ಮಧ್ಯ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    ಪ್ರತಿ (inner = 0; inner < outer; ++inner)
	      {
		ಯದಿ (STRNCMP (adr + ಮಧ್ಯ, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ಮಧ್ಯ, inner);
		    result = 1;
		  }

		ಯದಿ (STRNCMP (dest + nchars - outer, adr + ಮಧ್ಯ, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ಮಧ್ಯ, inner);
		    result = 1;
		  }
	      }

	    ಯದಿ (STRNCMP (adr + ಮಧ್ಯ, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ಮಧ್ಯ);
		result = 1;
	      }

	    ಯದಿ (STRNCMP (dest + nchars - outer, adr + ಮಧ್ಯ, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ಮಧ್ಯ);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ಪ್ರತಿ (len = 0; len < nchars - outer; ++len)
	    {
	      ಯದಿ (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      adr[nchars - 1] = L('\0');

      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      ಪ್ರತಿ (len = 0; len < nchars - outer + 64; ++len)
		{
		  ಯದಿ (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      printf ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		  ಯದಿ (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      printf ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* stpcpy/wcpcpy test */
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ಯದಿ ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ಪ್ರತಿ (len = 0; len < nchars - outer; ++len)
	    {
	      ಯದಿ (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      adr[nchars - 1] = L('\0');

      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = MAX (outer, nchars64); ಮಧ್ಯ < nchars; ++ಮಧ್ಯ)
	    {
	      adr[ಮಧ್ಯ] = L('\0');

	      ಪ್ರತಿ (inner = 0; inner < nchars - outer; ++ inner)
		{
		  ಯದಿ ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, ಮಧ್ಯ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, ಮಧ್ಯ, inner);
		      result = 1;
		    }
		}

	      adr[ಮಧ್ಯ] = L('T');
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* memcpy/wmemcpy test */
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಯದಿ (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* mempcpy/wmempcpy test */
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಯದಿ (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      ಪ್ರತಿ (outer = nchars; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (inner = 0; inner < nchars - outer; ++inner)
	    ಯದಿ (memccpy (dest, &adr[outer], L('\1'), inner) != ರಿಕ್ತ)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
      ಪ್ರತಿ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ಪ್ರತಿ (ಮಧ್ಯ = 0; ಮಧ್ಯ < nchars - outer; ++ಮಧ್ಯ)
	    {
	      memset (dest, L('\2'), ಮಧ್ಯ + 1);
	      ಪ್ರತಿ (inner = 0; inner < ಮಧ್ಯ; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  ಯದಿ (memccpy (dest, &adr[outer], '\1', ಮಧ್ಯ + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy ಪ್ರತಿ outer = %zu, ಮಧ್ಯ = %zu, inner = %zu\n",
			      outer, ಮಧ್ಯ, inner);
		      result = 1;
		    }
		  ಅನ್ಯಥಾ ಯದಿ (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much ಪ್ರತಿ outer = %zu, ಮಧ್ಯ = %zu, inner = %zu\n",
			      outer, ಮಧ್ಯ, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  ಯದಿ (outer == 0)
	    ಭಙ್ಗ;
	}
#endif
    }

  ಪ್ರತ್ಯಾಗಮ result;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
