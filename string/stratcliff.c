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

#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR ଅକ୍ଷର
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


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / ଆକାର (CHAR);
  CHAR *adr;
  CHAR *dest;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;

  adr = (CHAR *) mmap (ଖାଲି, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ଖାଲି, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  ଯଦି (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      ଯଦି (errno == ENOSYS)
	puts ("No test, mmap not available.");
      ଅନ୍ୟଥା
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  ଅନ୍ୟଥା
    {
      size_t inner, ମଧ୍ୟ, outer, nchars64, max128;

      ଯଦି (nchars > 64)
	nchars64 = nchars - 64;
      ଅନ୍ୟଥା
	nchars64 = 0;

      ଯଦି (nchars > 128)
	max128 = nchars - 128;
      ଅନ୍ୟଥା
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ଯଦି (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* strnlen/wcsnlen test */
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ଯଦି (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      ଯଦି (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* strchr/wcschr test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      ପାଇଁ (inner = ମଧ୍ୟ; inner < nchars; ++inner)
		{
		  adr[ମଧ୍ୟ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  ଯଦି ((inner == ମଧ୍ୟ && cp != ଖାଲି)
		      || (inner != ମଧ୍ୟ
			  && (cp - &adr[outer]) != ମଧ୍ୟ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, ମଧ୍ୟ, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ମଧ୍ୟ] = L('T');
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      ଯଦି (STRCHR (&adr[nchars - 1], L('\n')) != ଖାଲି)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      ପାଇଁ (inner = ମଧ୍ୟ; inner < nchars; ++inner)
		{
		  adr[ମଧ୍ୟ] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  ଯଦି ((inner == ମଧ୍ୟ && cp != ଖାଲି)
		      || (inner != ମଧ୍ୟ
			  && (cp - &adr[outer]) != ମଧ୍ୟ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, ମଧ୍ୟ, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ମଧ୍ୟ] = L('T');
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* memchr test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      adr[ମଧ୍ୟ] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      ଯଦି (cp - &adr[outer] != ମଧ୍ୟ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, ମଧ୍ୟ);
		  result = 1;
		}

	      adr[ମଧ୍ୟ] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  ଯଦି (cp != ଖାଲି)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      adr[ମଧ୍ୟ] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      ଯଦି (cp - &adr[outer] != ମଧ୍ୟ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, ମଧ୍ୟ);
		  result = 1;
		}

	      adr[ମଧ୍ୟ] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* memrchr test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      adr[ମଧ୍ୟ] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      ଯଦି (cp - &adr[outer] != ମଧ୍ୟ - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, ମଧ୍ୟ);
		  result = 1;
		}

	      adr[ମଧ୍ୟ] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  ଯଦି (cp != ଖାଲି)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
#endif

      /* strcpy/wcscpy test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ଯଦି (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* strcmp/wcscmp tests */
      ପାଇଁ (outer = 1; outer < 32; ++outer)
	ପାଇଁ (ମଧ୍ୟ = 0; ମଧ୍ୟ < 16; ++ମଧ୍ୟ)
	  {
	    MEMSET (adr + ମଧ୍ୟ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    ଯଦି (STRCMP (adr + ମଧ୍ୟ, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ମଧ୍ୟ);
		result = 1;
	      }

	    ଯଦି (STRCMP (dest + nchars - outer, adr + ମଧ୍ୟ) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ମଧ୍ୟ);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      ପାଇଁ (outer = 1; outer < 32; ++outer)
	ପାଇଁ (ମଧ୍ୟ = 0; ମଧ୍ୟ < 16; ++ମଧ୍ୟ)
	  {
	    MEMSET (adr + ମଧ୍ୟ, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    ପାଇଁ (inner = 0; inner < outer; ++inner)
	      {
		ଯଦି (STRNCMP (adr + ମଧ୍ୟ, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ମଧ୍ୟ, inner);
		    result = 1;
		  }

		ଯଦି (STRNCMP (dest + nchars - outer, adr + ମଧ୍ୟ, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ମଧ୍ୟ, inner);
		    result = 1;
		  }
	      }

	    ଯଦି (STRNCMP (adr + ମଧ୍ୟ, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ମଧ୍ୟ);
		result = 1;
	      }

	    ଯଦି (STRNCMP (dest + nchars - outer, adr + ମଧ୍ୟ, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ମଧ୍ୟ);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ପାଇଁ (len = 0; len < nchars - outer; ++len)
	    {
	      ଯଦି (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      adr[nchars - 1] = L('\0');

      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      ପାଇଁ (len = 0; len < nchars - outer + 64; ++len)
		{
		  ଯଦି (STRNCPY (dest, &adr[outer], len) != dest
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
		  ଯଦି (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* stpcpy/wcpcpy test */
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ଯଦି ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  ପାଇଁ (len = 0; len < nchars - outer; ++len)
	    {
	      ଯଦି (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      adr[nchars - 1] = L('\0');

      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = MAX (outer, nchars64); ମଧ୍ୟ < nchars; ++ମଧ୍ୟ)
	    {
	      adr[ମଧ୍ୟ] = L('\0');

	      ପାଇଁ (inner = 0; inner < nchars - outer; ++ inner)
		{
		  ଯଦି ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, ମଧ୍ୟ - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, ମଧ୍ୟ, inner);
		      result = 1;
		    }
		}

	      adr[ମଧ୍ୟ] = L('T');
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* memcpy/wmemcpy test */
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = 0; inner < nchars - outer; ++inner)
	    ଯଦି (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* mempcpy/wmempcpy test */
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = 0; inner < nchars - outer; ++inner)
	    ଯଦି (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      ପାଇଁ (outer = nchars; outer >= max128; --outer)
	{
	  ପାଇଁ (inner = 0; inner < nchars - outer; ++inner)
	    ଯଦି (memccpy (dest, &adr[outer], L('\1'), inner) != ଖାଲି)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
      ପାଇଁ (outer = nchars - 1; outer >= max128; --outer)
	{
	  ପାଇଁ (ମଧ୍ୟ = 0; ମଧ୍ୟ < nchars - outer; ++ମଧ୍ୟ)
	    {
	      memset (dest, L('\2'), ମଧ୍ୟ + 1);
	      ପାଇଁ (inner = 0; inner < ମଧ୍ୟ; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  ଯଦି (memccpy (dest, &adr[outer], '\1', ମଧ୍ୟ + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy ପାଇଁ outer = %zu, ମଧ୍ୟ = %zu, inner = %zu\n",
			      outer, ମଧ୍ୟ, inner);
		      result = 1;
		    }
		  ଅନ୍ୟଥା ଯଦି (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much ପାଇଁ outer = %zu, ମଧ୍ୟ = %zu, inner = %zu\n",
			      outer, ମଧ୍ୟ, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  ଯଦି (outer == 0)
	    ଭାଙ୍ଗ;
	}
#endif
    }

  ଫେରନ୍ତୁ result;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
