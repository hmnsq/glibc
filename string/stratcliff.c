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

#घोषणा _GNU_SOURCE 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#अघोषित __USE_STRING_INLINES

#समावेश <errno.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <sys/param.h>

#अगर_अघोषित CHAR
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
#पूर्ण_अगर


#घोषणा STRINGIFY(s) STRINGIFY2 (s)
#घोषणा STRINGIFY2(s) #s


पूर्णांक
do_test (व्योम)
{
  माप_प्रकार आकार = sysconf (_SC_PAGESIZE);
  माप_प्रकार nchars = आकार / माप (CHAR);
  CHAR *adr;
  CHAR *dest;
  पूर्णांक परिणाम = 0;

  adr = (CHAR *) mmap (शून्य, 3 * आकार, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (शून्य, 3 * आकार, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  अगर (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      अगर (त्रुटि_सं == ENOSYS)
	माला_दो ("No test, mmap not available.");
      अन्यथा
	{
	  म_लिखो ("mmap failed: %m");
	  परिणाम = 1;
	}
    }
  अन्यथा
    {
      माप_प्रकार inner, मध्य, outer, nchars64, max128;

      अगर (nchars > 64)
	nchars64 = nchars - 64;
      अन्यथा
	nchars64 = 0;

      अगर (nchars > 128)
	max128 = nchars - 128;
      अन्यथा
	max128 = 0;

      mprotect (adr, आकार, PROT_NONE);
      mprotect (adr + 2 * nchars, आकार, PROT_NONE);
      adr += nchars;

      mprotect (dest, आकार, PROT_NONE);
      mprotect (dest + 2 * nchars, आकार, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      अगर (STRLEN (&adr[outer]) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  परिणाम = 1;
		}

	      adr[inner] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* strnlen/wcsnlen test */
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      अगर (STRNLEN (&adr[outer], inner - outer + 1)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  परिणाम = 1;
		}

	      adr[inner] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      अगर (STRNLEN (&adr[outer], inner - outer)
		  != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  परिणाम = 1;
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* strchr/wcschr test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      क्रम (inner = मध्य; inner < nchars; ++inner)
		{
		  adr[मध्य] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  अगर ((inner == मध्य && cp != शून्य)
		      || (inner != मध्य
			  && (cp - &adr[outer]) != मध्य - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, मध्य, inner);
		      परिणाम = 1;
		    }

		  adr[inner] = L('T');
		  adr[मध्य] = L('T');
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      अगर (STRCHR (&adr[nchars - 1], L('\n')) != शून्य)
	{
	  म_लिखो ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  परिणाम = 1;
	}

      /* strrchr/wcsrchr test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      क्रम (inner = मध्य; inner < nchars; ++inner)
		{
		  adr[मध्य] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  अगर ((inner == मध्य && cp != शून्य)
		      || (inner != मध्य
			  && (cp - &adr[outer]) != मध्य - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, मध्य, inner);
		      परिणाम = 1;
		    }

		  adr[inner] = L('T');
		  adr[मध्य] = L('T');
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* memchr test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      adr[मध्य] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * आकार);

	      अगर (cp - &adr[outer] != मध्य - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, मध्य);
		  परिणाम = 1;
		}

	      adr[मध्य] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  अगर (cp != शून्य)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      परिणाम = 1;
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* These functions only exist for single-byte characters.  */
#अगर_अघोषित WCSTEST
      /* rawmemchr test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      adr[मध्य] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      अगर (cp - &adr[outer] != मध्य - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, मध्य);
		  परिणाम = 1;
		}

	      adr[मध्य] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* memrchr test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      adr[मध्य] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      अगर (cp - &adr[outer] != मध्य - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, मध्य);
		  परिणाम = 1;
		}

	      adr[मध्य] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  अगर (cp != शून्य)
	    {
	      म_लिखो ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      परिणाम = 1;
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
#पूर्ण_अगर

      /* strcpy/wcscpy test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      अगर (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (माप_प्रकार) (inner - outer))
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  परिणाम = 1;
		}

	      adr[inner] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* strcmp/wcscmp tests */
      क्रम (outer = 1; outer < 32; ++outer)
	क्रम (मध्य = 0; मध्य < 16; ++मध्य)
	  {
	    MEMSET (adr + मध्य, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    अगर (STRCMP (adr + मध्य, dest + nchars - outer) <= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मध्य);
		परिणाम = 1;
	      }

	    अगर (STRCMP (dest + nchars - outer, adr + मध्य) >= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, मध्य);
		परिणाम = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      क्रम (outer = 1; outer < 32; ++outer)
	क्रम (मध्य = 0; मध्य < 16; ++मध्य)
	  {
	    MEMSET (adr + मध्य, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    क्रम (inner = 0; inner < outer; ++inner)
	      {
		अगर (STRNCMP (adr + मध्य, dest + nchars - outer, inner) != 0)
		  {
		    म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मध्य, inner);
		    परिणाम = 1;
		  }

		अगर (STRNCMP (dest + nchars - outer, adr + मध्य, inner) != 0)
		  {
		    म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, मध्य, inner);
		    परिणाम = 1;
		  }
	      }

	    अगर (STRNCMP (adr + मध्य, dest + nchars - outer, outer) >= 0)
	      {
		म_लिखो ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मध्य);
		परिणाम = 1;
	      }

	    अगर (STRNCMP (dest + nchars - outer, adr + मध्य, outer) <= 0)
	      {
		म_लिखो ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, मध्य);
		परिणाम = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  क्रम (len = 0; len < nchars - outer; ++len)
	    {
	      अगर (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  परिणाम = 1;
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
      adr[nchars - 1] = L('\0');

      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      माप_प्रकार len;

	      adr[inner] = L('\0');

	      क्रम (len = 0; len < nchars - outer + 64; ++len)
		{
		  अगर (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      म_लिखो ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      परिणाम = 1;
		    }
		  अगर (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      म_लिखो ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      परिणाम = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* stpcpy/wcpcpy test */
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      अगर ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  परिणाम = 1;
		}

	      adr[inner] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  माप_प्रकार len;

	  क्रम (len = 0; len < nchars - outer; ++len)
	    {
	      अगर (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  म_लिखो ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  परिणाम = 1;
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
      adr[nchars - 1] = L('\0');

      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = MAX (outer, nchars64); मध्य < nchars; ++मध्य)
	    {
	      adr[मध्य] = L('\0');

	      क्रम (inner = 0; inner < nchars - outer; ++ inner)
		{
		  अगर ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, मध्य - outer))
		    {
		      म_लिखो ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, मध्य, inner);
		      परिणाम = 1;
		    }
		}

	      adr[मध्य] = L('T');
	    }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* memcpy/wmemcpy test */
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  क्रम (inner = 0; inner < nchars - outer; ++inner)
	    अगर (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		परिणाम = 1;
	      }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* mempcpy/wmempcpy test */
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  क्रम (inner = 0; inner < nchars - outer; ++inner)
	    अगर (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		म_लिखो ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		परिणाम = 1;
	      }
	  अगर (outer == 0)
	    अवरोध;
	}

      /* This function only exists for single-byte characters.  */
#अगर_अघोषित WCSTEST
      /* memccpy test */
      स_रखो (adr, '\0', nchars);
      क्रम (outer = nchars; outer >= max128; --outer)
	{
	  क्रम (inner = 0; inner < nchars - outer; ++inner)
	    अगर (memccpy (dest, &adr[outer], L('\1'), inner) != शून्य)
	      {
		म_लिखो ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		परिणाम = 1;
	      }
	  अगर (outer == 0)
	    अवरोध;
	}
      क्रम (outer = nchars - 1; outer >= max128; --outer)
	{
	  क्रम (मध्य = 0; मध्य < nchars - outer; ++मध्य)
	    {
	      स_रखो (dest, L('\2'), मध्य + 1);
	      क्रम (inner = 0; inner < मध्य; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  अगर (memccpy (dest, &adr[outer], '\1', मध्य + 128)
		      !=  dest + inner + 1)
		    {
		      म_लिखो ("\
			      memccpy flunked partial copy क्रम outer = %zu, मध्य = %zu, inner = %zu\n",
			      outer, मध्य, inner);
		      परिणाम = 1;
		    }
		  अन्यथा अगर (dest[inner + 1] != L('\2'))
		    {
		      म_लिखो ("\
			      memccpy copied too much क्रम outer = %zu, मध्य = %zu, inner = %zu\n",
			      outer, मध्य, inner);
		      परिणाम = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  अगर (outer == 0)
	    अवरोध;
	}
#पूर्ण_अगर
    }

  वापस परिणाम;
}

#समावेश <support/test-driver.c>
