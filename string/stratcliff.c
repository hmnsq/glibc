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

#अन्तर्भाव <errno.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR वर्ण
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


पूर्णाङ्क
do_test (शून्य)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / परिमाण (CHAR);
  CHAR *adr;
  CHAR *dest;
  पूर्णाङ्क result = 0;

  adr = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  सचे (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      सचे (errno == ENOSYS)
	puts ("No test, mmap not available.");
      अञ्ञथा
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  अञ्ञथा
    {
      size_t inner, मध्यः, outer, nchars64, max128;

      सचे (nchars > 64)
	nchars64 = nchars - 64;
      अञ्ञथा
	nchars64 = 0;

      सचे (nchars > 128)
	max128 = nchars - 128;
      अञ्ञथा
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      सचे (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* strnlen/wcsnlen test */
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      सचे (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      सचे (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* strchr/wcschr test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      अत्थाय (inner = मध्यः; inner < nchars; ++inner)
		{
		  adr[मध्यः] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  सचे ((inner == मध्यः && cp != रिक्त)
		      || (inner != मध्यः
			  && (cp - &adr[outer]) != मध्यः - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, मध्यः, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[मध्यः] = L('T');
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      सचे (STRCHR (&adr[nchars - 1], L('\n')) != रिक्त)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      अत्थाय (inner = मध्यः; inner < nchars; ++inner)
		{
		  adr[मध्यः] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  सचे ((inner == मध्यः && cp != रिक्त)
		      || (inner != मध्यः
			  && (cp - &adr[outer]) != मध्यः - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, मध्यः, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[मध्यः] = L('T');
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* memchr test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      adr[मध्यः] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      सचे (cp - &adr[outer] != मध्यः - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, मध्यः);
		  result = 1;
		}

	      adr[मध्यः] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  सचे (cp != रिक्त)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      adr[मध्यः] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      सचे (cp - &adr[outer] != मध्यः - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, मध्यः);
		  result = 1;
		}

	      adr[मध्यः] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* memrchr test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      adr[मध्यः] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      सचे (cp - &adr[outer] != मध्यः - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, मध्यः);
		  result = 1;
		}

	      adr[मध्यः] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  सचे (cp != रिक्त)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
#endif

      /* strcpy/wcscpy test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      सचे (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* strcmp/wcscmp tests */
      अत्थाय (outer = 1; outer < 32; ++outer)
	अत्थाय (मध्यः = 0; मध्यः < 16; ++मध्यः)
	  {
	    MEMSET (adr + मध्यः, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    सचे (STRCMP (adr + मध्यः, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मध्यः);
		result = 1;
	      }

	    सचे (STRCMP (dest + nchars - outer, adr + मध्यः) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मध्यः);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      अत्थाय (outer = 1; outer < 32; ++outer)
	अत्थाय (मध्यः = 0; मध्यः < 16; ++मध्यः)
	  {
	    MEMSET (adr + मध्यः, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    अत्थाय (inner = 0; inner < outer; ++inner)
	      {
		सचे (STRNCMP (adr + मध्यः, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मध्यः, inner);
		    result = 1;
		  }

		सचे (STRNCMP (dest + nchars - outer, adr + मध्यः, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मध्यः, inner);
		    result = 1;
		  }
	      }

	    सचे (STRNCMP (adr + मध्यः, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मध्यः);
		result = 1;
	      }

	    सचे (STRNCMP (dest + nchars - outer, adr + मध्यः, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मध्यः);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  अत्थाय (len = 0; len < nchars - outer; ++len)
	    {
	      सचे (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
      adr[nchars - 1] = L('\0');

      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      अत्थाय (len = 0; len < nchars - outer + 64; ++len)
		{
		  सचे (STRNCPY (dest, &adr[outer], len) != dest
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
		  सचे (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* stpcpy/wcpcpy test */
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      सचे ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  अत्थाय (len = 0; len < nchars - outer; ++len)
	    {
	      सचे (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
      adr[nchars - 1] = L('\0');

      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = MAX (outer, nchars64); मध्यः < nchars; ++मध्यः)
	    {
	      adr[मध्यः] = L('\0');

	      अत्थाय (inner = 0; inner < nchars - outer; ++ inner)
		{
		  सचे ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, मध्यः - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, मध्यः, inner);
		      result = 1;
		    }
		}

	      adr[मध्यः] = L('T');
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* memcpy/wmemcpy test */
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  अत्थाय (inner = 0; inner < nchars - outer; ++inner)
	    सचे (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* mempcpy/wmempcpy test */
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  अत्थाय (inner = 0; inner < nchars - outer; ++inner)
	    सचे (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  सचे (outer == 0)
	    भङ्ग;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      अत्थाय (outer = nchars; outer >= max128; --outer)
	{
	  अत्थाय (inner = 0; inner < nchars - outer; ++inner)
	    सचे (memccpy (dest, &adr[outer], L('\1'), inner) != रिक्त)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  सचे (outer == 0)
	    भङ्ग;
	}
      अत्थाय (outer = nchars - 1; outer >= max128; --outer)
	{
	  अत्थाय (मध्यः = 0; मध्यः < nchars - outer; ++मध्यः)
	    {
	      memset (dest, L('\2'), मध्यः + 1);
	      अत्थाय (inner = 0; inner < मध्यः; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  सचे (memccpy (dest, &adr[outer], '\1', मध्यः + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy अत्थाय outer = %zu, मध्यः = %zu, inner = %zu\n",
			      outer, मध्यः, inner);
		      result = 1;
		    }
		  अञ्ञथा सचे (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much अत्थाय outer = %zu, मध्यः = %zu, inner = %zu\n",
			      outer, मध्यः, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  सचे (outer == 0)
	    भङ्ग;
	}
#endif
    }

  पटिनिवत्त result;
}

#अन्तर्भाव <support/test-driver.c>
