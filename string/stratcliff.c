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

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR எழுத்து
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


முழு
do_test (வெறுமை)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / அளவு (CHAR);
  CHAR *adr;
  CHAR *dest;
  முழு result = 0;

  adr = (CHAR *) mmap (வெற்று, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (வெற்று, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  எனில் (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      எனில் (errno == ENOSYS)
	puts ("No test, mmap not available.");
      இல்லையெனில்
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  இல்லையெனில்
    {
      size_t inner, நடு, outer, nchars64, max128;

      எனில் (nchars > 64)
	nchars64 = nchars - 64;
      இல்லையெனில்
	nchars64 = 0;

      எனில் (nchars > 128)
	max128 = nchars - 128;
      இல்லையெனில்
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      எனில் (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* strnlen/wcsnlen test */
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      எனில் (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      எனில் (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* strchr/wcschr test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      க்கு (inner = நடு; inner < nchars; ++inner)
		{
		  adr[நடு] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  எனில் ((inner == நடு && cp != வெற்று)
		      || (inner != நடு
			  && (cp - &adr[outer]) != நடு - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, நடு, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[நடு] = L('T');
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      எனில் (STRCHR (&adr[nchars - 1], L('\n')) != வெற்று)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      க்கு (inner = நடு; inner < nchars; ++inner)
		{
		  adr[நடு] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  எனில் ((inner == நடு && cp != வெற்று)
		      || (inner != நடு
			  && (cp - &adr[outer]) != நடு - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, நடு, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[நடு] = L('T');
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* memchr test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      adr[நடு] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      எனில் (cp - &adr[outer] != நடு - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, நடு);
		  result = 1;
		}

	      adr[நடு] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  எனில் (cp != வெற்று)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      adr[நடு] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      எனில் (cp - &adr[outer] != நடு - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, நடு);
		  result = 1;
		}

	      adr[நடு] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* memrchr test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      adr[நடு] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      எனில் (cp - &adr[outer] != நடு - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, நடு);
		  result = 1;
		}

	      adr[நடு] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  எனில் (cp != வெற்று)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
#endif

      /* strcpy/wcscpy test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      எனில் (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* strcmp/wcscmp tests */
      க்கு (outer = 1; outer < 32; ++outer)
	க்கு (நடு = 0; நடு < 16; ++நடு)
	  {
	    MEMSET (adr + நடு, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    எனில் (STRCMP (adr + நடு, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, நடு);
		result = 1;
	      }

	    எனில் (STRCMP (dest + nchars - outer, adr + நடு) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, நடு);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      க்கு (outer = 1; outer < 32; ++outer)
	க்கு (நடு = 0; நடு < 16; ++நடு)
	  {
	    MEMSET (adr + நடு, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    க்கு (inner = 0; inner < outer; ++inner)
	      {
		எனில் (STRNCMP (adr + நடு, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, நடு, inner);
		    result = 1;
		  }

		எனில் (STRNCMP (dest + nchars - outer, adr + நடு, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, நடு, inner);
		    result = 1;
		  }
	      }

	    எனில் (STRNCMP (adr + நடு, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, நடு);
		result = 1;
	      }

	    எனில் (STRNCMP (dest + nchars - outer, adr + நடு, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, நடு);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  க்கு (len = 0; len < nchars - outer; ++len)
	    {
	      எனில் (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      adr[nchars - 1] = L('\0');

      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      க்கு (len = 0; len < nchars - outer + 64; ++len)
		{
		  எனில் (STRNCPY (dest, &adr[outer], len) != dest
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
		  எனில் (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* stpcpy/wcpcpy test */
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      எனில் ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  க்கு (len = 0; len < nchars - outer; ++len)
	    {
	      எனில் (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      adr[nchars - 1] = L('\0');

      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = MAX (outer, nchars64); நடு < nchars; ++நடு)
	    {
	      adr[நடு] = L('\0');

	      க்கு (inner = 0; inner < nchars - outer; ++ inner)
		{
		  எனில் ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, நடு - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, நடு, inner);
		      result = 1;
		    }
		}

	      adr[நடு] = L('T');
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* memcpy/wmemcpy test */
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  க்கு (inner = 0; inner < nchars - outer; ++inner)
	    எனில் (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* mempcpy/wmempcpy test */
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  க்கு (inner = 0; inner < nchars - outer; ++inner)
	    எனில் (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  எனில் (outer == 0)
	    நிறுத்து;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      க்கு (outer = nchars; outer >= max128; --outer)
	{
	  க்கு (inner = 0; inner < nchars - outer; ++inner)
	    எனில் (memccpy (dest, &adr[outer], L('\1'), inner) != வெற்று)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
      க்கு (outer = nchars - 1; outer >= max128; --outer)
	{
	  க்கு (நடு = 0; நடு < nchars - outer; ++நடு)
	    {
	      memset (dest, L('\2'), நடு + 1);
	      க்கு (inner = 0; inner < நடு; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  எனில் (memccpy (dest, &adr[outer], '\1', நடு + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy க்கு outer = %zu, நடு = %zu, inner = %zu\n",
			      outer, நடு, inner);
		      result = 1;
		    }
		  இல்லையெனில் எனில் (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much க்கு outer = %zu, நடு = %zu, inner = %zu\n",
			      outer, நடு, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  எனில் (outer == 0)
	    நிறுத்து;
	}
#endif
    }

  திரும்பு result;
}

#அந்தர்பாவ <support/test-driver.c>
