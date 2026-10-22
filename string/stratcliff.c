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

#شامل <errno.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <unistd.h>
#شامل <sys/mman.h>
#شامل <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR نویسه
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


صحیح
do_test (تهی)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / اندازه (CHAR);
  CHAR *adr;
  CHAR *dest;
  صحیح result = 0;

  adr = (CHAR *) mmap (پوچ, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (پوچ, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  اگر (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      اگر (errno == ENOSYS)
	puts ("No test, mmap not available.");
      وگرنه
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  وگرنه
    {
      size_t inner, میانه, outer, nchars64, max128;

      اگر (nchars > 64)
	nchars64 = nchars - 64;
      وگرنه
	nchars64 = 0;

      اگر (nchars > 128)
	max128 = nchars - 128;
      وگرنه
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* strnlen/wcsnlen test */
      برای (outer = nchars; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}
      برای (outer = nchars; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      اگر (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* strchr/wcschr test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      برای (inner = میانه; inner < nchars; ++inner)
		{
		  adr[میانه] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  اگر ((inner == میانه && cp != پوچ)
		      || (inner != میانه
			  && (cp - &adr[outer]) != میانه - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, میانه, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[میانه] = L('T');
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      اگر (STRCHR (&adr[nchars - 1], L('\n')) != پوچ)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      برای (inner = میانه; inner < nchars; ++inner)
		{
		  adr[میانه] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  اگر ((inner == میانه && cp != پوچ)
		      || (inner != میانه
			  && (cp - &adr[outer]) != میانه - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, میانه, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[میانه] = L('T');
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* memchr test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      اگر (cp - &adr[outer] != میانه - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, میانه);
		  result = 1;
		}

	      adr[میانه] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}
      برای (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  اگر (cp != پوچ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      اگر (cp - &adr[outer] != میانه - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, میانه);
		  result = 1;
		}

	      adr[میانه] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* memrchr test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      اگر (cp - &adr[outer] != میانه - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, میانه);
		  result = 1;
		}

	      adr[میانه] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}
      برای (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  اگر (cp != پوچ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  اگر (outer == 0)
	    بشکن;
	}
#endif

      /* strcpy/wcscpy test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* strcmp/wcscmp tests */
      برای (outer = 1; outer < 32; ++outer)
	برای (میانه = 0; میانه < 16; ++میانه)
	  {
	    MEMSET (adr + میانه, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    اگر (STRCMP (adr + میانه, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, میانه);
		result = 1;
	      }

	    اگر (STRCMP (dest + nchars - outer, adr + میانه) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, میانه);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      برای (outer = 1; outer < 32; ++outer)
	برای (میانه = 0; میانه < 16; ++میانه)
	  {
	    MEMSET (adr + میانه, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    برای (inner = 0; inner < outer; ++inner)
	      {
		اگر (STRNCMP (adr + میانه, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, میانه, inner);
		    result = 1;
		  }

		اگر (STRNCMP (dest + nchars - outer, adr + میانه, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, میانه, inner);
		    result = 1;
		  }
	      }

	    اگر (STRNCMP (adr + میانه, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, میانه);
		result = 1;
	      }

	    اگر (STRNCMP (dest + nchars - outer, adr + میانه, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, میانه);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      برای (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  برای (len = 0; len < nchars - outer; ++len)
	    {
	      اگر (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}
      adr[nchars - 1] = L('\0');

      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      برای (len = 0; len < nchars - outer + 64; ++len)
		{
		  اگر (STRNCPY (dest, &adr[outer], len) != dest
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
		  اگر (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  اگر (outer == 0)
	    بشکن;
	}

      /* stpcpy/wcpcpy test */
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      برای (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  برای (len = 0; len < nchars - outer; ++len)
	    {
	      اگر (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}
      adr[nchars - 1] = L('\0');

      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('\0');

	      برای (inner = 0; inner < nchars - outer; ++ inner)
		{
		  اگر ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, میانه - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, میانه, inner);
		      result = 1;
		    }
		}

	      adr[میانه] = L('T');
	    }
	  اگر (outer == 0)
	    بشکن;
	}

      /* memcpy/wmemcpy test */
      برای (outer = nchars; outer >= max128; --outer)
	{
	  برای (inner = 0; inner < nchars - outer; ++inner)
	    اگر (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  اگر (outer == 0)
	    بشکن;
	}

      /* mempcpy/wmempcpy test */
      برای (outer = nchars; outer >= max128; --outer)
	{
	  برای (inner = 0; inner < nchars - outer; ++inner)
	    اگر (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  اگر (outer == 0)
	    بشکن;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      برای (outer = nchars; outer >= max128; --outer)
	{
	  برای (inner = 0; inner < nchars - outer; ++inner)
	    اگر (memccpy (dest, &adr[outer], L('\1'), inner) != پوچ)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  اگر (outer == 0)
	    بشکن;
	}
      برای (outer = nchars - 1; outer >= max128; --outer)
	{
	  برای (میانه = 0; میانه < nchars - outer; ++میانه)
	    {
	      memset (dest, L('\2'), میانه + 1);
	      برای (inner = 0; inner < میانه; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  اگر (memccpy (dest, &adr[outer], '\1', میانه + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy برای outer = %zu, میانه = %zu, inner = %zu\n",
			      outer, میانه, inner);
		      result = 1;
		    }
		  وگرنه اگر (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much برای outer = %zu, میانه = %zu, inner = %zu\n",
			      outer, میانه, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  اگر (outer == 0)
	    بشکن;
	}
#endif
    }

  بازگشت result;
}

#شامل <support/test-driver.c>
