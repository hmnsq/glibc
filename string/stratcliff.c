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
# define CHAR अक्षर
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


पूर्णांक
do_test (शून्य)
{
  माप_प्रकार size = sysconf (_SC_PAGESIZE);
  माप_प्रकार nchars = size / आकार (CHAR);
  CHAR *adr;
  CHAR *dest;
  पूर्णांक result = 0;

  adr = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (रिक्त, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  जर (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      जर (त्रुटि_सं == ENOSYS)
	माला_दो ("No test, mmap not available.");
      अन्यथा
	{
	  म_लिखो ("mmap failed: %m");
	  result = 1;
	}
    }
  अन्यथा
    {
      माप_प्रकार inner, मधला, outer, nchars64, max128;

      जर (nchars > 64)
	nchars64 = nchars - 64;
      अन्यथा
	nchars64 = 0;

      जर (nchars > 128)
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
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      जर (STRLEN (&adr[outer]) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* strnlen/wcsnlen test */
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      जर (STRNLEN (&adr[outer], inner - outer + 1)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      जर (STRNLEN (&adr[outer], inner - outer)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* strchr/wcschr test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      साठी (inner = मधला; inner < nchars; ++inner)
		{
		  adr[मधला] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  जर ((inner == मधला && cp != रिक्त)
		      || (inner != मधला
			  && (cp - &adr[outer]) != मधला - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, मधला, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[मधला] = L('T');
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      जर (STRCHR (&adr[nchars - 1], L('\n')) != रिक्त)
	{
	  म_लिखो ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      साठी (inner = मधला; inner < nchars; ++inner)
		{
		  adr[मधला] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  जर ((inner == मधला && cp != रिक्त)
		      || (inner != मधला
			  && (cp - &adr[outer]) != मधला - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, मधला, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[मधला] = L('T');
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* memchr test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      adr[मधला] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      जर (cp - &adr[outer] != मधला - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, मधला);
		  result = 1;
		}

	      adr[मधला] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  जर (cp != रिक्त)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      adr[मधला] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      जर (cp - &adr[outer] != मधला - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, मधला);
		  result = 1;
		}

	      adr[मधला] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* memrchr test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      adr[मधला] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      जर (cp - &adr[outer] != मधला - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, मधला);
		  result = 1;
		}

	      adr[मधला] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  जर (cp != रिक्त)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	  जर (outer == 0)
	    थांबा;
	}
#endif

      /* strcpy/wcscpy test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      जर (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* strcmp/wcscmp tests */
      साठी (outer = 1; outer < 32; ++outer)
	साठी (मधला = 0; मधला < 16; ++मधला)
	  {
	    MEMSET (adr + मधला, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    जर (STRCMP (adr + मधला, dest + nchars - outer) <= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मधला);
		result = 1;
	      }

	    जर (STRCMP (dest + nchars - outer, adr + मधला) >= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मधला);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      साठी (outer = 1; outer < 32; ++outer)
	साठी (मधला = 0; मधला < 16; ++मधला)
	  {
	    MEMSET (adr + मधला, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    साठी (inner = 0; inner < outer; ++inner)
	      {
		जर (STRNCMP (adr + मधला, dest + nchars - outer, inner) != 0)
		  {
		    म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मधला, inner);
		    result = 1;
		  }

		जर (STRNCMP (dest + nchars - outer, adr + मधला, inner) != 0)
		  {
		    म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मधला, inner);
		    result = 1;
		  }
	      }

	    जर (STRNCMP (adr + मधला, dest + nchars - outer, outer) >= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मधला);
		result = 1;
	      }

	    जर (STRNCMP (dest + nchars - outer, adr + मधला, outer) <= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मधला);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  साठी (len = 0; len < nchars - outer; ++len)
	    {
	      जर (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}
      adr[nchars - 1] = L('\0');

      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      माप_प्रकार len;

	      adr[inner] = L('\0');

	      साठी (len = 0; len < nchars - outer + 64; ++len)
		{
		  जर (STRNCPY (dest, &adr[outer], len) != dest
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
		  जर (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
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
	  जर (outer == 0)
	    थांबा;
	}

      /* stpcpy/wcpcpy test */
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      जर ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  साठी (len = 0; len < nchars - outer; ++len)
	    {
	      जर (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}
      adr[nchars - 1] = L('\0');

      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = MAX (outer, nchars64); मधला < nchars; ++मधला)
	    {
	      adr[मधला] = L('\0');

	      साठी (inner = 0; inner < nchars - outer; ++ inner)
		{
		  जर ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, मधला - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, मधला, inner);
		      result = 1;
		    }
		}

	      adr[मधला] = L('T');
	    }
	  जर (outer == 0)
	    थांबा;
	}

      /* memcpy/wmemcpy test */
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  साठी (inner = 0; inner < nchars - outer; ++inner)
	    जर (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		result = 1;
	      }
	  जर (outer == 0)
	    थांबा;
	}

      /* mempcpy/wmempcpy test */
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  साठी (inner = 0; inner < nchars - outer; ++inner)
	    जर (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		result = 1;
	      }
	  जर (outer == 0)
	    थांबा;
	}

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      स_रखो (adr, '\0', nchars);
      साठी (outer = nchars; outer >= max128; --outer)
	{
	  साठी (inner = 0; inner < nchars - outer; ++inner)
	    जर (memccpy (dest, &adr[outer], L('\1'), inner) != रिक्त)
	      {
		म_लिखो ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		result = 1;
	      }
	  जर (outer == 0)
	    थांबा;
	}
      साठी (outer = nchars - 1; outer >= max128; --outer)
	{
	  साठी (मधला = 0; मधला < nchars - outer; ++मधला)
	    {
	      स_रखो (dest, L('\2'), मधला + 1);
	      साठी (inner = 0; inner < मधला; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  जर (memccpy (dest, &adr[outer], '\1', मधला + 128)
		      !=  dest + inner + 1)
		    {
		      म_लिखो ("\
			      memccpy flunked partial copy साठी outer = %zu, मधला = %zu, inner = %zu\n",
			      outer, मधला, inner);
		      result = 1;
		    }
		  अन्यथा जर (dest[inner + 1] != L('\2'))
		    {
		      म_लिखो ("\
			      memccpy copied too much साठी outer = %zu, मधला = %zu, inner = %zu\n",
			      outer, मधला, inner);
		      result = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  जर (outer == 0)
	    थांबा;
	}
#endif
    }

  परत result;
}

#अन्तर्भाव <support/test-driver.c>
