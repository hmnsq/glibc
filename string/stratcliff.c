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

#ضمن <errno.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <unistd.h>
#ضمن <sys/mman.h>
#ضمن <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR حرف
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


صحيح
do_test (فراغ)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / حجم (CHAR);
  CHAR *adr;
  CHAR *dest;
  صحيح result = 0;

  adr = (CHAR *) mmap (عدم, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (عدم, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  إذا (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      إذا (errno == ENOSYS)
	puts ("No test, mmap not available.");
      وإلا
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  وإلا
    {
      size_t inner, ناوەڕاست, outer, nchars64, max128;

      إذا (nchars > 64)
	nchars64 = nchars - 64;
      وإلا
	nchars64 = 0;

      إذا (nchars > 128)
	max128 = nchars - 128;
      وإلا
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      إذا (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* strnlen/wcsnlen test */
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      إذا (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      إذا (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* strchr/wcschr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      لكل (inner = ناوەڕاست; inner < nchars; ++inner)
		{
		  adr[ناوەڕاست] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  إذا ((inner == ناوەڕاست && cp != عدم)
		      || (inner != ناوەڕاست
			  && (cp - &adr[outer]) != ناوەڕاست - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, ناوەڕاست, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ناوەڕاست] = L('T');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      إذا (STRCHR (&adr[nchars - 1], L('\n')) != عدم)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      لكل (inner = ناوەڕاست; inner < nchars; ++inner)
		{
		  adr[ناوەڕاست] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  إذا ((inner == ناوەڕاست && cp != عدم)
		      || (inner != ناوەڕاست
			  && (cp - &adr[outer]) != ناوەڕاست - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, ناوەڕاست, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[ناوەڕاست] = L('T');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* memchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      adr[ناوەڕاست] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      إذا (cp - &adr[outer] != ناوەڕاست - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, ناوەڕاست);
		  result = 1;
		}

	      adr[ناوەڕاست] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  إذا (cp != عدم)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      adr[ناوەڕاست] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      إذا (cp - &adr[outer] != ناوەڕاست - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, ناوەڕاست);
		  result = 1;
		}

	      adr[ناوەڕاست] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* memrchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      adr[ناوەڕاست] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      إذا (cp - &adr[outer] != ناوەڕاست - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, ناوەڕاست);
		  result = 1;
		}

	      adr[ناوەڕاست] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  إذا (cp != عدم)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  إذا (outer == 0)
	    اكسر;
	}
#endif

      /* strcpy/wcscpy test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      إذا (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* strcmp/wcscmp tests */
      لكل (outer = 1; outer < 32; ++outer)
	لكل (ناوەڕاست = 0; ناوەڕاست < 16; ++ناوەڕاست)
	  {
	    MEMSET (adr + ناوەڕاست, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    إذا (STRCMP (adr + ناوەڕاست, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ناوەڕاست);
		result = 1;
	      }

	    إذا (STRCMP (dest + nchars - outer, adr + ناوەڕاست) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, ناوەڕاست);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      لكل (outer = 1; outer < 32; ++outer)
	لكل (ناوەڕاست = 0; ناوەڕاست < 16; ++ناوەڕاست)
	  {
	    MEMSET (adr + ناوەڕاست, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    لكل (inner = 0; inner < outer; ++inner)
	      {
		إذا (STRNCMP (adr + ناوەڕاست, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ناوەڕاست, inner);
		    result = 1;
		  }

		إذا (STRNCMP (dest + nchars - outer, adr + ناوەڕاست, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, ناوەڕاست, inner);
		    result = 1;
		  }
	      }

	    إذا (STRNCMP (adr + ناوەڕاست, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ناوەڕاست);
		result = 1;
	      }

	    إذا (STRNCMP (dest + nchars - outer, adr + ناوەڕاست, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, ناوەڕاست);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  لكل (len = 0; len < nchars - outer; ++len)
	    {
	      إذا (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      adr[nchars - 1] = L('\0');

      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      لكل (len = 0; len < nchars - outer + 64; ++len)
		{
		  إذا (STRNCPY (dest, &adr[outer], len) != dest
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
		  إذا (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  إذا (outer == 0)
	    اكسر;
	}

      /* stpcpy/wcpcpy test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      إذا ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  لكل (len = 0; len < nchars - outer; ++len)
	    {
	      إذا (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      adr[nchars - 1] = L('\0');

      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = MAX (outer, nchars64); ناوەڕاست < nchars; ++ناوەڕاست)
	    {
	      adr[ناوەڕاست] = L('\0');

	      لكل (inner = 0; inner < nchars - outer; ++ inner)
		{
		  إذا ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, ناوەڕاست - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, ناوەڕاست, inner);
		      result = 1;
		    }
		}

	      adr[ناوەڕاست] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* memcpy/wmemcpy test */
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = 0; inner < nchars - outer; ++inner)
	    إذا (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  إذا (outer == 0)
	    اكسر;
	}

      /* mempcpy/wmempcpy test */
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = 0; inner < nchars - outer; ++inner)
	    إذا (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  إذا (outer == 0)
	    اكسر;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = 0; inner < nchars - outer; ++inner)
	    إذا (memccpy (dest, &adr[outer], L('\1'), inner) != عدم)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (ناوەڕاست = 0; ناوەڕاست < nchars - outer; ++ناوەڕاست)
	    {
	      memset (dest, L('\2'), ناوەڕاست + 1);
	      لكل (inner = 0; inner < ناوەڕاست; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  إذا (memccpy (dest, &adr[outer], '\1', ناوەڕاست + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy لكل outer = %zu, ناوەڕاست = %zu, inner = %zu\n",
			      outer, ناوەڕاست, inner);
		      result = 1;
		    }
		  وإلا إذا (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much لكل outer = %zu, ناوەڕاست = %zu, inner = %zu\n",
			      outer, ناوەڕاست, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}
#endif
    }

  أرجع result;
}

#ضمن <support/test-driver.c>
