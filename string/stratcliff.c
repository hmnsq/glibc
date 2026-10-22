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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR var_na
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


ཧྲིལ
do_test (void)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / parimaa_na (CHAR);
  CHAR *adr;
  CHAR *dest;
  ཧྲིལ result = 0;

  adr = (CHAR *) mmap (NULL, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (NULL, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  གལ་སྲིད (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      གལ་སྲིད (errno == ENOSYS)
	puts ("No test, mmap not available.");
      དེ་མིན
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  དེ་མིན
    {
      size_t inner, middle, outer, nchars64, max128;

      གལ་སྲིད (nchars > 64)
	nchars64 = nchars - 64;
      དེ་མིན
	nchars64 = 0;

      གལ་སྲིད (nchars > 128)
	max128 = nchars - 128;
      དེ་མིན
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      གལ་སྲིད (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* strnlen/wcsnlen test */
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      གལ་སྲིད (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      གལ་སྲིད (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* strchr/wcschr test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      དོན་ལུ (inner = middle; inner < nchars; ++inner)
		{
		  adr[middle] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  གལ་སྲིད ((inner == middle && cp != NULL)
		      || (inner != middle
			  && (cp - &adr[outer]) != middle - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, middle, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[middle] = L('T');
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      གལ་སྲིད (STRCHR (&adr[nchars - 1], L('\n')) != NULL)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      དོན་ལུ (inner = middle; inner < nchars; ++inner)
		{
		  adr[middle] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  གལ་སྲིད ((inner == middle && cp != NULL)
		      || (inner != middle
			  && (cp - &adr[outer]) != middle - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, middle, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[middle] = L('T');
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* memchr test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      གལ་སྲིད (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  གལ་སྲིད (cp != NULL)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      གལ་སྲིད (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* memrchr test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      གལ་སྲིད (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  གལ་སྲིད (cp != NULL)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
#endif

      /* strcpy/wcscpy test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      གལ་སྲིད (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* strcmp/wcscmp tests */
      དོན་ལུ (outer = 1; outer < 32; ++outer)
	དོན་ལུ (middle = 0; middle < 16; ++middle)
	  {
	    MEMSET (adr + middle, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    གལ་སྲིད (STRCMP (adr + middle, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, middle);
		result = 1;
	      }

	    གལ་སྲིད (STRCMP (dest + nchars - outer, adr + middle) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, middle);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      དོན་ལུ (outer = 1; outer < 32; ++outer)
	དོན་ལུ (middle = 0; middle < 16; ++middle)
	  {
	    MEMSET (adr + middle, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    དོན་ལུ (inner = 0; inner < outer; ++inner)
	      {
		གལ་སྲིད (STRNCMP (adr + middle, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, middle, inner);
		    result = 1;
		  }

		གལ་སྲིད (STRNCMP (dest + nchars - outer, adr + middle, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, middle, inner);
		    result = 1;
		  }
	      }

	    གལ་སྲིད (STRNCMP (adr + middle, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, middle);
		result = 1;
	      }

	    གལ་སྲིད (STRNCMP (dest + nchars - outer, adr + middle, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, middle);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  དོན་ལུ (len = 0; len < nchars - outer; ++len)
	    {
	      གལ་སྲིད (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      adr[nchars - 1] = L('\0');

      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      དོན་ལུ (len = 0; len < nchars - outer + 64; ++len)
		{
		  གལ་སྲིད (STRNCPY (dest, &adr[outer], len) != dest
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
		  གལ་སྲིད (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* stpcpy/wcpcpy test */
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      གལ་སྲིད ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  དོན་ལུ (len = 0; len < nchars - outer; ++len)
	    {
	      གལ་སྲིད (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      adr[nchars - 1] = L('\0');

      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = MAX (outer, nchars64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('\0');

	      དོན་ལུ (inner = 0; inner < nchars - outer; ++ inner)
		{
		  གལ་སྲིད ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, middle - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, middle, inner);
		      result = 1;
		    }
		}

	      adr[middle] = L('T');
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* memcpy/wmemcpy test */
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = 0; inner < nchars - outer; ++inner)
	    གལ་སྲིད (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* mempcpy/wmempcpy test */
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = 0; inner < nchars - outer; ++inner)
	    གལ་སྲིད (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      དོན་ལུ (outer = nchars; outer >= max128; --outer)
	{
	  དོན་ལུ (inner = 0; inner < nchars - outer; ++inner)
	    གལ་སྲིད (memccpy (dest, &adr[outer], L('\1'), inner) != NULL)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
      དོན་ལུ (outer = nchars - 1; outer >= max128; --outer)
	{
	  དོན་ལུ (middle = 0; middle < nchars - outer; ++middle)
	    {
	      memset (dest, L('\2'), middle + 1);
	      དོན་ལུ (inner = 0; inner < middle; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  གལ་སྲིད (memccpy (dest, &adr[outer], '\1', middle + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy དོན་ལུ outer = %zu, middle = %zu, inner = %zu\n",
			      outer, middle, inner);
		      result = 1;
		    }
		  དེ་མིན གལ་སྲིད (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much དོན་ལུ outer = %zu, middle = %zu, inner = %zu\n",
			      outer, middle, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  གལ་སྲིད (outer == 0)
	    bha_nga;
	}
#endif
    }

  ལོག result;
}

#include <support/test-driver.c>
