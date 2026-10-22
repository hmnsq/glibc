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

#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <sys/mman.h>
#അന്തര്ഭാവ <sys/param.h>

#ifndef CHAR
# define L(c) c
# define CHAR അക്ഷരം
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


പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  size_t size = sysconf (_SC_PAGESIZE);
  size_t nchars = size / വലുപ്പം (CHAR);
  CHAR *adr;
  CHAR *dest;
  പൂർണ്ണസംഖ്യ result = 0;

  adr = (CHAR *) mmap (ശൂന്യ, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ശൂന്യ, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  എങ്കിൽ (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      എങ്കിൽ (errno == ENOSYS)
	puts ("No test, mmap not available.");
      അല്ലെങ്കിൽ
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  അല്ലെങ്കിൽ
    {
      size_t inner, നടുവ്, outer, nchars64, max128;

      എങ്കിൽ (nchars > 64)
	nchars64 = nchars - 64;
      അല്ലെങ്കിൽ
	nchars64 = 0;

      എങ്കിൽ (nchars > 128)
	max128 = nchars - 128;
      അല്ലെങ്കിൽ
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      എങ്കിൽ (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* strnlen/wcsnlen test */
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      എങ്കിൽ (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      എങ്കിൽ (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* strchr/wcschr test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      വേണ്ടി (inner = നടുവ്; inner < nchars; ++inner)
		{
		  adr[നടുവ്] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  എങ്കിൽ ((inner == നടുവ് && cp != ശൂന്യ)
		      || (inner != നടുവ്
			  && (cp - &adr[outer]) != നടുവ് - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, നടുവ്, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[നടുവ്] = L('T');
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      എങ്കിൽ (STRCHR (&adr[nchars - 1], L('\n')) != ശൂന്യ)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      വേണ്ടി (inner = നടുവ്; inner < nchars; ++inner)
		{
		  adr[നടുവ്] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  എങ്കിൽ ((inner == നടുവ് && cp != ശൂന്യ)
		      || (inner != നടുവ്
			  && (cp - &adr[outer]) != നടുവ് - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, നടുവ്, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[നടുവ്] = L('T');
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* memchr test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      adr[നടുവ്] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      എങ്കിൽ (cp - &adr[outer] != നടുവ് - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, നടുവ്);
		  result = 1;
		}

	      adr[നടുവ്] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  എങ്കിൽ (cp != ശൂന്യ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      adr[നടുവ്] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      എങ്കിൽ (cp - &adr[outer] != നടുവ് - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, നടുവ്);
		  result = 1;
		}

	      adr[നടുവ്] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* memrchr test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      adr[നടുവ്] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      എങ്കിൽ (cp - &adr[outer] != നടുവ് - outer)
		{
		  printf ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, നടുവ്);
		  result = 1;
		}

	      adr[നടുവ്] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  എങ്കിൽ (cp != ശൂന്യ)
	    {
	      printf ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
#endif

      /* strcpy/wcscpy test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      എങ്കിൽ (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* strcmp/wcscmp tests */
      വേണ്ടി (outer = 1; outer < 32; ++outer)
	വേണ്ടി (നടുവ് = 0; നടുവ് < 16; ++നടുവ്)
	  {
	    MEMSET (adr + നടുവ്, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    എങ്കിൽ (STRCMP (adr + നടുവ്, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, നടുവ്);
		result = 1;
	      }

	    എങ്കിൽ (STRCMP (dest + nchars - outer, adr + നടുവ്) >= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, നടുവ്);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      വേണ്ടി (outer = 1; outer < 32; ++outer)
	വേണ്ടി (നടുവ് = 0; നടുവ് < 16; ++നടുവ്)
	  {
	    MEMSET (adr + നടുവ്, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    വേണ്ടി (inner = 0; inner < outer; ++inner)
	      {
		എങ്കിൽ (STRNCMP (adr + നടുവ്, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, നടുവ്, inner);
		    result = 1;
		  }

		എങ്കിൽ (STRNCMP (dest + nchars - outer, adr + നടുവ്, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, നടുവ്, inner);
		    result = 1;
		  }
	      }

	    എങ്കിൽ (STRNCMP (adr + നടുവ്, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, നടുവ്);
		result = 1;
	      }

	    എങ്കിൽ (STRNCMP (dest + nchars - outer, adr + നടുവ്, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, നടുവ്);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  വേണ്ടി (len = 0; len < nchars - outer; ++len)
	    {
	      എങ്കിൽ (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      adr[nchars - 1] = L('\0');

      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      വേണ്ടി (len = 0; len < nchars - outer + 64; ++len)
		{
		  എങ്കിൽ (STRNCPY (dest, &adr[outer], len) != dest
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
		  എങ്കിൽ (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* stpcpy/wcpcpy test */
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      എങ്കിൽ ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  വേണ്ടി (len = 0; len < nchars - outer; ++len)
	    {
	      എങ്കിൽ (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      adr[nchars - 1] = L('\0');

      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = MAX (outer, nchars64); നടുവ് < nchars; ++നടുവ്)
	    {
	      adr[നടുവ്] = L('\0');

	      വേണ്ടി (inner = 0; inner < nchars - outer; ++ inner)
		{
		  എങ്കിൽ ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, നടുവ് - outer))
		    {
		      printf ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, നടുവ്, inner);
		      result = 1;
		    }
		}

	      adr[നടുവ്] = L('T');
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* memcpy/wmemcpy test */
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = 0; inner < nchars - outer; ++inner)
	    എങ്കിൽ (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* mempcpy/wmempcpy test */
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = 0; inner < nchars - outer; ++inner)
	    എങ്കിൽ (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		printf ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      വേണ്ടി (outer = nchars; outer >= max128; --outer)
	{
	  വേണ്ടി (inner = 0; inner < nchars - outer; ++inner)
	    എങ്കിൽ (memccpy (dest, &adr[outer], L('\1'), inner) != ശൂന്യ)
	      {
		printf ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
      വേണ്ടി (outer = nchars - 1; outer >= max128; --outer)
	{
	  വേണ്ടി (നടുവ് = 0; നടുവ് < nchars - outer; ++നടുവ്)
	    {
	      memset (dest, L('\2'), നടുവ് + 1);
	      വേണ്ടി (inner = 0; inner < നടുവ്; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  എങ്കിൽ (memccpy (dest, &adr[outer], '\1', നടുവ് + 128)
		      !=  dest + inner + 1)
		    {
		      printf ("\
			      memccpy flunked partial copy വേണ്ടി outer = %zu, നടുവ് = %zu, inner = %zu\n",
			      outer, നടുവ്, inner);
		      result = 1;
		    }
		  അല്ലെങ്കിൽ എങ്കിൽ (dest[inner + 1] != L('\2'))
		    {
		      printf ("\
			      memccpy copied too much വേണ്ടി outer = %zu, നടുവ് = %zu, inner = %zu\n",
			      outer, നടുവ്, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  എങ്കിൽ (outer == 0)
	    നിർത്തുക;
	}
#endif
    }

  തിരികെ result;
}

#അന്തര്ഭാവ <support/test-driver.c>
