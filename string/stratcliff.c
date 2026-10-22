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
# define MEMSET स_रखो
# define STRLEN म_माप
# define STRNLEN strnlen
# define STRCHR म_अक्षर
# define STRRCHR म_खोजप
# define STRCPY म_नकल
# define STRNCPY म_नकलन
# define MEMCMP स_भेद
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY स_नकल
# define MEMPCPY mempcpy
# define MEMCHR स_प्रथम
# define STRCMP म_भेद
# define STRNCMP म_भेदन
#endif


#define STRINGIFY(s) STRINGIFY2 (s)
#define STRINGIFY2(s) #s


पूर्णाङ्क
do_test (शून्य)
{
  माप_प्रकार size = sysconf (_SC_PAGESIZE);
  माप_प्रकार nchars = size / परिमाण (CHAR);
  CHAR *adr;
  CHAR *dest;
  पूर्णाङ्क result = 0;

  adr = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  यदि (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      यदि (त्रुटि_सं == ENOSYS)
	माला_दो ("No test, mmap not available.");
      अन्यथा
	{
	  म_लिखो ("mmap failed: %m");
	  result = 1;
	}
    }
  अन्यथा
    {
      माप_प्रकार inner, बीच, outer, nchars64, max128;

      यदि (nchars > 64)
	nchars64 = nchars - 64;
      अन्यथा
	nchars64 = 0;

      यदि (nchars > 128)
	max128 = nchars - 128;
      अन्यथा
	max128 = 0;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      यदि (STRLEN (&adr[outer]) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* strnlen/wcsnlen test */
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      यदि (STRNLEN (&adr[outer], inner - outer + 1)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      यदि (STRNLEN (&adr[outer], inner - outer)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* strchr/wcschr test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      लागि (inner = बीच; inner < nchars; ++inner)
		{
		  adr[बीच] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  यदि ((inner == बीच && cp != रिक्त)
		      || (inner != बीच
			  && (cp - &adr[outer]) != बीच - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, बीच, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[बीच] = L('T');
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      यदि (STRCHR (&adr[nchars - 1], L('\n')) != रिक्त)
	{
	  म_लिखो ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      लागि (inner = बीच; inner < nchars; ++inner)
		{
		  adr[बीच] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  यदि ((inner == बीच && cp != रिक्त)
		      || (inner != बीच
			  && (cp - &adr[outer]) != बीच - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, बीच, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[बीच] = L('T');
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* memchr test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      adr[बीच] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      यदि (cp - &adr[outer] != बीच - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, बीच);
		  result = 1;
		}

	      adr[बीच] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  यदि (cp != रिक्त)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      adr[बीच] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      यदि (cp - &adr[outer] != बीच - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, बीच);
		  result = 1;
		}

	      adr[बीच] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* memrchr test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      adr[बीच] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      यदि (cp - &adr[outer] != बीच - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, बीच);
		  result = 1;
		}

	      adr[बीच] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  यदि (cp != रिक्त)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  यदि (outer == 0)
	    रोक;
	}
#endif

      /* strcpy/wcscpy test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      यदि (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* strcmp/wcscmp tests */
      लागि (outer = 1; outer < 32; ++outer)
	लागि (बीच = 0; बीच < 16; ++बीच)
	  {
	    MEMSET (adr + बीच, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    यदि (STRCMP (adr + बीच, dest + nchars - outer) <= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, बीच);
		result = 1;
	      }

	    यदि (STRCMP (dest + nchars - outer, adr + बीच) >= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, बीच);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      लागि (outer = 1; outer < 32; ++outer)
	लागि (बीच = 0; बीच < 16; ++बीच)
	  {
	    MEMSET (adr + बीच, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    लागि (inner = 0; inner < outer; ++inner)
	      {
		यदि (STRNCMP (adr + बीच, dest + nchars - outer, inner) != 0)
		  {
		    म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, बीच, inner);
		    result = 1;
		  }

		यदि (STRNCMP (dest + nchars - outer, adr + बीच, inner) != 0)
		  {
		    म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, बीच, inner);
		    result = 1;
		  }
	      }

	    यदि (STRNCMP (adr + बीच, dest + nchars - outer, outer) >= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, बीच);
		result = 1;
	      }

	    यदि (STRNCMP (dest + nchars - outer, adr + बीच, outer) <= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, बीच);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  लागि (len = 0; len < nchars - outer; ++len)
	    {
	      यदि (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}
      adr[nchars - 1] = L('\0');

      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      माप_प्रकार len;

	      adr[inner] = L('\0');

	      लागि (len = 0; len < nchars - outer + 64; ++len)
		{
		  यदि (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      म_लिखो ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		  यदि (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      म_लिखो ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* stpcpy/wcpcpy test */
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      यदि ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  लागि (len = 0; len < nchars - outer; ++len)
	    {
	      यदि (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}
      adr[nchars - 1] = L('\0');

      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = MAX (outer, nchars64); बीच < nchars; ++बीच)
	    {
	      adr[बीच] = L('\0');

	      लागि (inner = 0; inner < nchars - outer; ++ inner)
		{
		  यदि ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, बीच - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, बीच, inner);
		      result = 1;
		    }
		}

	      adr[बीच] = L('T');
	    }
	  यदि (outer == 0)
	    रोक;
	}

      /* memcpy/wmemcpy test */
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  लागि (inner = 0; inner < nchars - outer; ++inner)
	    यदि (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  यदि (outer == 0)
	    रोक;
	}

      /* mempcpy/wmempcpy test */
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  लागि (inner = 0; inner < nchars - outer; ++inner)
	    यदि (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  यदि (outer == 0)
	    रोक;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      स_रखो (adr, '\0', nchars);
      लागि (outer = nchars; outer >= max128; --outer)
	{
	  लागि (inner = 0; inner < nchars - outer; ++inner)
	    यदि (memccpy (dest, &adr[outer], L('\1'), inner) != रिक्त)
	      {
		म_लिखो ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  यदि (outer == 0)
	    रोक;
	}
      लागि (outer = nchars - 1; outer >= max128; --outer)
	{
	  लागि (बीच = 0; बीच < nchars - outer; ++बीच)
	    {
	      स_रखो (dest, L('\2'), बीच + 1);
	      लागि (inner = 0; inner < बीच; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  यदि (memccpy (dest, &adr[outer], '\1', बीच + 128)
		      !=  dest + inner + 1)
		    {
		      म_लिखो ("\
			      memccpy flunked partial copy लागि outer = %zu, बीच = %zu, inner = %zu\n",
			      outer, बीच, inner);
		      result = 1;
		    }
		  अन्यथा यदि (dest[inner + 1] != L('\2'))
		    {
		      म_लिखो ("\
			      memccpy copied too much लागि outer = %zu, बीच = %zu, inner = %zu\n",
			      outer, बीच, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  यदि (outer == 0)
	    रोक;
	}
#endif
    }

  फर्काऊ result;
}

#अन्तर्भाव <support/test-driver.c>
