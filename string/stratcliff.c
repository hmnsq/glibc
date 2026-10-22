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

#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <sys/mman.h>
#অন্তর্ভাব <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR অক্ষর
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


পূর্ণসংখ্যা
do_test (শূন্য)
{
  size_t আকার_2 = sysconf (_SC_PAGESIZE);
  size_t nchars = আকার_2 / আকার (CHAR);
  CHAR *adr;
  CHAR *dest;
  পূর্ণসংখ্যা ফলাফল = 0;

  adr = (CHAR *) mmap (ফাঁকা, 3 * আকার_2, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ফাঁকা, 3 * আকার_2, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  যদি (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      যদি (errno == ENOSYS)
	puts ("No test, mmap not available.");
      অন্যথা
	{
	  printf ("mmap failed: %m");
	  ফলাফল = 1;
	}
    }
  অন্যথা
    {
      size_t inner, মধ্য, outer, nchars64, max128;

      যদি (nchars > 64)
	nchars64 = nchars - 64;
      অন্যথা
	nchars64 = 0;

      যদি (nchars > 128)
	max128 = nchars - 128;
      অন্যথা
	max128 = 0;

      mprotect (adr, আকার_2, PROT_NONE);
      mprotect (adr + 2 * nchars, আকার_2, PROT_NONE);
      adr += nchars;

      mprotect (dest, আকার_2, PROT_NONE);
      mprotect (dest + 2 * nchars, আকার_2, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  ফলাফল = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* strnlen/wcsnlen test */
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ফলাফল = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      যদি (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ফলাফল = 1;
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* strchr/wcschr test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      জন্য (inner = মধ্য; inner < nchars; ++inner)
		{
		  adr[মধ্য] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  যদি ((inner == মধ্য && cp != ফাঁকা)
		      || (inner != মধ্য
			  && (cp - &adr[outer]) != মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, মধ্য, inner);
		      ফলাফল = 1;
		    }

		  adr[inner] = L('T');
		  adr[মধ্য] = L('T');
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      যদি (STRCHR (&adr[nchars - 1], L('\n')) != ফাঁকা)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  ফলাফল = 1;
	}

      /* strrchr/wcsrchr test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      জন্য (inner = মধ্য; inner < nchars; ++inner)
		{
		  adr[মধ্য] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  যদি ((inner == মধ্য && cp != ফাঁকা)
		      || (inner != মধ্য
			  && (cp - &adr[outer]) != মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, মধ্য, inner);
		      ফলাফল = 1;
		    }

		  adr[inner] = L('T');
		  adr[মধ্য] = L('T');
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* memchr test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * আকার_2);

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, মধ্য);
		  ফলাফল = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  যদি (cp != ফাঁকা)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      ফলাফল = 1;
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, মধ্য);
		  ফলাফল = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* memrchr test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, মধ্য);
		  ফলাফল = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  যদি (cp != ফাঁকা)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      ফলাফল = 1;
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
#endif

      /* strcpy/wcscpy test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  ফলাফল = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* strcmp/wcscmp tests */
      জন্য (outer = 1; outer < 32; ++outer)
	জন্য (মধ্য = 0; মধ্য < 16; ++মধ্য)
	  {
	    MEMSET (adr + মধ্য, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    যদি (STRCMP (adr + মধ্য, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, মধ্য);
		ফলাফল = 1;
	      }

	    যদি (STRCMP (dest + nchars - outer, adr + মধ্য) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, মধ্য);
		ফলাফল = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      জন্য (outer = 1; outer < 32; ++outer)
	জন্য (মধ্য = 0; মধ্য < 16; ++মধ্য)
	  {
	    MEMSET (adr + মধ্য, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    জন্য (inner = 0; inner < outer; ++inner)
	      {
		যদি (STRNCMP (adr + মধ্য, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, মধ্য, inner);
		    ফলাফল = 1;
		  }

		যদি (STRNCMP (dest + nchars - outer, adr + মধ্য, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, মধ্য, inner);
		    ফলাফল = 1;
		  }
	      }

	    যদি (STRNCMP (adr + মধ্য, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, মধ্য);
		ফলাফল = 1;
	      }

	    যদি (STRNCMP (dest + nchars - outer, adr + মধ্য, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, মধ্য);
		ফলাফল = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  জন্য (len = 0; len < nchars - outer; ++len)
	    {
	      যদি (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  ফলাফল = 1;
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
      adr[nchars - 1] = L('\0');

      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      জন্য (len = 0; len < nchars - outer + 64; ++len)
		{
		  যদি (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      printf ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ফলাফল = 1;
		    }
		  যদি (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      printf ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ফলাফল = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* stpcpy/wcpcpy test */
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  ফলাফল = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  জন্য (len = 0; len < nchars - outer; ++len)
	    {
	      যদি (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  ফলাফল = 1;
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
      adr[nchars - 1] = L('\0');

      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('\0');

	      জন্য (inner = 0; inner < nchars - outer; ++ inner)
		{
		  যদি ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, মধ্য, inner);
		      ফলাফল = 1;
		    }
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* memcpy/wmemcpy test */
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  জন্য (inner = 0; inner < nchars - outer; ++inner)
	    যদি (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		ফলাফল = 1;
	      }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* mempcpy/wmempcpy test */
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  জন্য (inner = 0; inner < nchars - outer; ++inner)
	    যদি (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		ফলাফল = 1;
	      }
	  যদি (outer == 0)
	    বিরতি;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      জন্য (outer = nchars; outer >= max128; --outer)
	{
	  জন্য (inner = 0; inner < nchars - outer; ++inner)
	    যদি (memccpy (dest, &adr[outer], L('\1'), inner) != ফাঁকা)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		ফলাফল = 1;
	      }
	  যদি (outer == 0)
	    বিরতি;
	}
      জন্য (outer = nchars - 1; outer >= max128; --outer)
	{
	  জন্য (মধ্য = 0; মধ্য < nchars - outer; ++মধ্য)
	    {
	      memset (dest, L('\2'), মধ্য + 1);
	      জন্য (inner = 0; inner < মধ্য; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  যদি (memccpy (dest, &adr[outer], '\1', মধ্য + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy জন্য outer = %zu, মধ্য = %zu, inner = %zu\n",
			      outer, মধ্য, inner);
		      ফলাফল = 1;
		    }
		  অন্যথা যদি (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much জন্য outer = %zu, মধ্য = %zu, inner = %zu\n",
			      outer, মধ্য, inner);
		      ফলাফল = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  যদি (outer == 0)
	    বিরতি;
	}
#endif
    }

  ফেরত ফলাফল;
}

#অন্তর্ভাব <support/test-driver.c>
