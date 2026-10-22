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

#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <sys/mman.h>
#অন্তর্ভাৱ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR ৱর্ণ
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


পূর্ণাঙ্ক
do_test (শূন্য)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / পরিমাণ (CHAR);
  CHAR *adr;
  CHAR *dest;
  পূর্ণাঙ্ক result = 0;

  adr = (CHAR *) mmap (রিক্ত, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (রিক্ত, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  যদি (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      যদি (errno == ENOSYS)
	puts ("No test, mmap not available.");
      অন্যথা
	{
	  printf ("mmap failed: %m");
	  result = 1;
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

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* strnlen/wcsnlen test */
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      যদি (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* strchr/wcschr test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      বাবে (inner = মধ্য; inner < nchars; ++inner)
		{
		  adr[মধ্য] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  যদি ((inner == মধ্য && cp != রিক্ত)
		      || (inner != মধ্য
			  && (cp - &adr[outer]) != মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, মধ্য, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[মধ্য] = L('T');
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      যদি (STRCHR (&adr[nchars - 1], L('\n')) != রিক্ত)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      বাবে (inner = মধ্য; inner < nchars; ++inner)
		{
		  adr[মধ্য] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  যদি ((inner == মধ্য && cp != রিক্ত)
		      || (inner != মধ্য
			  && (cp - &adr[outer]) != মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, মধ্য, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[মধ্য] = L('T');
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* memchr test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, মধ্য);
		  result = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  যদি (cp != রিক্ত)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, মধ্য);
		  result = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* memrchr test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      যদি (cp - &adr[outer] != মধ্য - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, মধ্য);
		  result = 1;
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  যদি (cp != রিক্ত)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
#endif

      /* strcpy/wcscpy test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* strcmp/wcscmp tests */
      বাবে (outer = 1; outer < 32; ++outer)
	বাবে (মধ্য = 0; মধ্য < 16; ++মধ্য)
	  {
	    MEMSET (adr + মধ্য, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    যদি (STRCMP (adr + মধ্য, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, মধ্য);
		result = 1;
	      }

	    যদি (STRCMP (dest + nchars - outer, adr + মধ্য) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, মধ্য);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      বাবে (outer = 1; outer < 32; ++outer)
	বাবে (মধ্য = 0; মধ্য < 16; ++মধ্য)
	  {
	    MEMSET (adr + মধ্য, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    বাবে (inner = 0; inner < outer; ++inner)
	      {
		যদি (STRNCMP (adr + মধ্য, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, মধ্য, inner);
		    result = 1;
		  }

		যদি (STRNCMP (dest + nchars - outer, adr + মধ্য, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, মধ্য, inner);
		    result = 1;
		  }
	      }

	    যদি (STRNCMP (adr + মধ্য, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, মধ্য);
		result = 1;
	      }

	    যদি (STRNCMP (dest + nchars - outer, adr + মধ্য, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, মধ্য);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  বাবে (len = 0; len < nchars - outer; ++len)
	    {
	      যদি (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      adr[nchars - 1] = L('\0');

      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      বাবে (len = 0; len < nchars - outer + 64; ++len)
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
		      result = 1;
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
		      result = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* stpcpy/wcpcpy test */
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      যদি ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  বাবে (len = 0; len < nchars - outer; ++len)
	    {
	      যদি (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      adr[nchars - 1] = L('\0');

      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = MAX (outer, nchars64); মধ্য < nchars; ++মধ্য)
	    {
	      adr[মধ্য] = L('\0');

	      বাবে (inner = 0; inner < nchars - outer; ++ inner)
		{
		  যদি ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, মধ্য - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, মধ্য, inner);
		      result = 1;
		    }
		}

	      adr[মধ্য] = L('T');
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* memcpy/wmemcpy test */
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  বাবে (inner = 0; inner < nchars - outer; ++inner)
	    যদি (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* mempcpy/wmempcpy test */
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  বাবে (inner = 0; inner < nchars - outer; ++inner)
	    যদি (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  যদি (outer == 0)
	    ভঙ্গ;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      বাবে (outer = nchars; outer >= max128; --outer)
	{
	  বাবে (inner = 0; inner < nchars - outer; ++inner)
	    যদি (memccpy (dest, &adr[outer], L('\1'), inner) != রিক্ত)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
      বাবে (outer = nchars - 1; outer >= max128; --outer)
	{
	  বাবে (মধ্য = 0; মধ্য < nchars - outer; ++মধ্য)
	    {
	      memset (dest, L('\2'), মধ্য + 1);
	      বাবে (inner = 0; inner < মধ্য; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  যদি (memccpy (dest, &adr[outer], '\1', মধ্য + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy বাবে outer = %zu, মধ্য = %zu, inner = %zu\n",
			      outer, মধ্য, inner);
		      result = 1;
		    }
		  অন্যথা যদি (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much বাবে outer = %zu, মধ্য = %zu, inner = %zu\n",
			      outer, মধ্য, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  যদি (outer == 0)
	    ভঙ্গ;
	}
#endif
    }

  ঘূৰাই result;
}

#অন্তর্ভাৱ <support/test-driver.c>
