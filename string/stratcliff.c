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

#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <sys/mman.h>
#અન્તર્ભાવ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR અક્ષર
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


પૂર્ણાંક
do_test (શૂન્ય)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / કદ (CHAR);
  CHAR *adr;
  CHAR *dest;
  પૂર્ણાંક result = 0;

  adr = (CHAR *) mmap (ખાલી, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ખાલી, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  જો (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      જો (errno == ENOSYS)
	puts ("No test, mmap not available.");
      નહીંતર
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  નહીંતર
    {
      size_t inner, મધ્ય, outer, nchars64, max128;

      જો (nchars > 64)
	nchars64 = nchars - 64;
      નહીંતર
	nchars64 = 0;

      જો (nchars > 128)
	max128 = nchars - 128;
      નહીંતર
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      જો (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* strnlen/wcsnlen test */
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      જો (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      જો (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* strchr/wcschr test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      માટે (inner = મધ્ય; inner < nchars; ++inner)
		{
		  adr[મધ્ય] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  જો ((inner == મધ્ય && cp != ખાલી)
		      || (inner != મધ્ય
			  && (cp - &adr[outer]) != મધ્ય - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, મધ્ય, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[મધ્ય] = L('T');
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      જો (STRCHR (&adr[nchars - 1], L('\n')) != ખાલી)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      માટે (inner = મધ્ય; inner < nchars; ++inner)
		{
		  adr[મધ્ય] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  જો ((inner == મધ્ય && cp != ખાલી)
		      || (inner != મધ્ય
			  && (cp - &adr[outer]) != મધ્ય - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, મધ્ય, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[મધ્ય] = L('T');
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* memchr test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      adr[મધ્ય] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      જો (cp - &adr[outer] != મધ્ય - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, મધ્ય);
		  result = 1;
		}

	      adr[મધ્ય] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  જો (cp != ખાલી)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      adr[મધ્ય] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      જો (cp - &adr[outer] != મધ્ય - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, મધ્ય);
		  result = 1;
		}

	      adr[મધ્ય] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* memrchr test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      adr[મધ્ય] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      જો (cp - &adr[outer] != મધ્ય - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, મધ્ય);
		  result = 1;
		}

	      adr[મધ્ય] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  જો (cp != ખાલી)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  જો (outer == 0)
	    તોડો;
	}
#endif

      /* strcpy/wcscpy test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      જો (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* strcmp/wcscmp tests */
      માટે (outer = 1; outer < 32; ++outer)
	માટે (મધ્ય = 0; મધ્ય < 16; ++મધ્ય)
	  {
	    MEMSET (adr + મધ્ય, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    જો (STRCMP (adr + મધ્ય, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, મધ્ય);
		result = 1;
	      }

	    જો (STRCMP (dest + nchars - outer, adr + મધ્ય) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, મધ્ય);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      માટે (outer = 1; outer < 32; ++outer)
	માટે (મધ્ય = 0; મધ્ય < 16; ++મધ્ય)
	  {
	    MEMSET (adr + મધ્ય, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    માટે (inner = 0; inner < outer; ++inner)
	      {
		જો (STRNCMP (adr + મધ્ય, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, મધ્ય, inner);
		    result = 1;
		  }

		જો (STRNCMP (dest + nchars - outer, adr + મધ્ય, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, મધ્ય, inner);
		    result = 1;
		  }
	      }

	    જો (STRNCMP (adr + મધ્ય, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, મધ્ય);
		result = 1;
	      }

	    જો (STRNCMP (dest + nchars - outer, adr + મધ્ય, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, મધ્ય);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  માટે (len = 0; len < nchars - outer; ++len)
	    {
	      જો (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}
      adr[nchars - 1] = L('\0');

      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      માટે (len = 0; len < nchars - outer + 64; ++len)
		{
		  જો (STRNCPY (dest, &adr[outer], len) != dest
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
		  જો (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  જો (outer == 0)
	    તોડો;
	}

      /* stpcpy/wcpcpy test */
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      જો ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  માટે (len = 0; len < nchars - outer; ++len)
	    {
	      જો (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}
      adr[nchars - 1] = L('\0');

      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = MAX (outer, nchars64); મધ્ય < nchars; ++મધ્ય)
	    {
	      adr[મધ્ય] = L('\0');

	      માટે (inner = 0; inner < nchars - outer; ++ inner)
		{
		  જો ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, મધ્ય - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, મધ્ય, inner);
		      result = 1;
		    }
		}

	      adr[મધ્ય] = L('T');
	    }
	  જો (outer == 0)
	    તોડો;
	}

      /* memcpy/wmemcpy test */
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  માટે (inner = 0; inner < nchars - outer; ++inner)
	    જો (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  જો (outer == 0)
	    તોડો;
	}

      /* mempcpy/wmempcpy test */
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  માટે (inner = 0; inner < nchars - outer; ++inner)
	    જો (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  જો (outer == 0)
	    તોડો;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      માટે (outer = nchars; outer >= max128; --outer)
	{
	  માટે (inner = 0; inner < nchars - outer; ++inner)
	    જો (memccpy (dest, &adr[outer], L('\1'), inner) != ખાલી)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  જો (outer == 0)
	    તોડો;
	}
      માટે (outer = nchars - 1; outer >= max128; --outer)
	{
	  માટે (મધ્ય = 0; મધ્ય < nchars - outer; ++મધ્ય)
	    {
	      memset (dest, L('\2'), મધ્ય + 1);
	      માટે (inner = 0; inner < મધ્ય; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  જો (memccpy (dest, &adr[outer], '\1', મધ્ય + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy માટે outer = %zu, મધ્ય = %zu, inner = %zu\n",
			      outer, મધ્ય, inner);
		      result = 1;
		    }
		  નહીંતર જો (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much માટે outer = %zu, મધ્ય = %zu, inner = %zu\n",
			      outer, મધ્ય, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  જો (outer == 0)
	    તોડો;
	}
#endif
    }

  પાછા result;
}

#અન્તર્ભાવ <support/test-driver.c>
