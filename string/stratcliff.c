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

#నిర్వచించు GNU_ఆధారం 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#నిర్వచనం_రద్దు __USE_STRING_INLINES

#అన్తర్భావ <errno.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <sys/param.h>

#నిర్వచితం_కాకపోతే CHAR
# define L(c) c
# define CHAR అక్షరం
# define MEMSET memset
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY జ్ఞాపకం_నకలు
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP అక్షరశ్రేణి_పోలిక
#అయితే_ముగింపు


#నిర్వచించు STRINGIFY(s) STRINGIFY2 (s)
#నిర్వచించు STRINGIFY2(s) #s


పూర్ణాంకం
do_test (శూన్య)
{
  size_t కొలత = sysconf (_SC_PAGESIZE);
  size_t nchars = కొలత / పరిమాణం (CHAR);
  CHAR *adr;
  CHAR *dest;
  పూర్ణాంకం ఫలితం = 0;

  adr = (CHAR *) mmap (ఖాళీ, 3 * కొలత, PROT_READ | PROT_WRITE,
		       MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (ఖాళీ, 3 * కొలత, PROT_READ | PROT_WRITE,
			MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  ఒకవేళ (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      ఒకవేళ (errno == ENOSYS)
	puts ("No test, mmap not available.");
      లేకపోతే
	{
	  రాయి ("mmap failed: %m");
	  ఫలితం = 1;
	}
    }
  లేకపోతే
    {
      size_t inner, మధ్య, outer, nchars64, max128;

      ఒకవేళ (nchars > 64)
	nchars64 = nchars - 64;
      లేకపోతే
	nchars64 = 0;

      ఒకవేళ (nchars > 128)
	max128 = nchars - 128;
      లేకపోతే
	max128 = 0;

      mprotect (adr, కొలత, PROT_NONE);
      mprotect (adr + 2 * nchars, కొలత, PROT_NONE);
      adr += nchars;

      mprotect (dest, కొలత, PROT_NONE);
      mprotect (dest + 2 * nchars, కొలత, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ఒకవేళ (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  ఫలితం = 1;
		}

	      adr[inner] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* strnlen/wcsnlen test */
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ఒకవేళ (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ఫలితం = 1;
		}

	      adr[inner] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      ఒకవేళ (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  రాయి ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  ఫలితం = 1;
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* strchr/wcschr test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      కొరకు (inner = మధ్య; inner < nchars; ++inner)
		{
		  adr[మధ్య] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  ఒకవేళ ((inner == మధ్య && cp != ఖాళీ)
		      || (inner != మధ్య
			  && (cp - &adr[outer]) != మధ్య - outer))
		    {
		      రాయి ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, మధ్య, inner);
		      ఫలితం = 1;
		    }

		  adr[inner] = L('T');
		  adr[మధ్య] = L('T');
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      ఒకవేళ (STRCHR (&adr[nchars - 1], L('\n')) != ఖాళీ)
	{
	  రాయి ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  ఫలితం = 1;
	}

      /* strrchr/wcsrchr test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      కొరకు (inner = మధ్య; inner < nchars; ++inner)
		{
		  adr[మధ్య] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  ఒకవేళ ((inner == మధ్య && cp != ఖాళీ)
		      || (inner != మధ్య
			  && (cp - &adr[outer]) != మధ్య - outer))
		    {
		      రాయి ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, మధ్య, inner);
		      ఫలితం = 1;
		    }

		  adr[inner] = L('T');
		  adr[మధ్య] = L('T');
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* memchr test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      adr[మధ్య] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * కొలత);

	      ఒకవేళ (cp - &adr[outer] != మధ్య - outer)
		{
		  రాయి ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, మధ్య);
		  ఫలితం = 1;
		}

	      adr[మధ్య] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  ఒకవేళ (cp != ఖాళీ)
	    {
	      రాయి ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      ఫలితం = 1;
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* These functions only exist for single-byte characters.  */
#నిర్వచితం_కాకపోతే WCSTEST
      /* rawmemchr test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      adr[మధ్య] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      ఒకవేళ (cp - &adr[outer] != మధ్య - outer)
		{
		  రాయి ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, మధ్య);
		  ఫలితం = 1;
		}

	      adr[మధ్య] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* memrchr test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      adr[మధ్య] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      ఒకవేళ (cp - &adr[outer] != మధ్య - outer)
		{
		  రాయి ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, మధ్య);
		  ఫలితం = 1;
		}

	      adr[మధ్య] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  ఒకవేళ (cp != ఖాళీ)
	    {
	      రాయి ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      ఫలితం = 1;
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
#అయితే_ముగింపు

      /* strcpy/wcscpy test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ఒకవేళ (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  ఫలితం = 1;
		}

	      adr[inner] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* strcmp/wcscmp tests */
      కొరకు (outer = 1; outer < 32; ++outer)
	కొరకు (మధ్య = 0; మధ్య < 16; ++మధ్య)
	  {
	    MEMSET (adr + మధ్య, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    ఒకవేళ (STRCMP (adr + మధ్య, dest + nchars - outer) <= 0)
	      {
		రాయి ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, మధ్య);
		ఫలితం = 1;
	      }

	    ఒకవేళ (STRCMP (dest + nchars - outer, adr + మధ్య) >= 0)
	      {
		రాయి ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, మధ్య);
		ఫలితం = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      కొరకు (outer = 1; outer < 32; ++outer)
	కొరకు (మధ్య = 0; మధ్య < 16; ++మధ్య)
	  {
	    MEMSET (adr + మధ్య, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    కొరకు (inner = 0; inner < outer; ++inner)
	      {
		ఒకవేళ (STRNCMP (adr + మధ్య, dest + nchars - outer, inner) != 0)
		  {
		    రాయి ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, మధ్య, inner);
		    ఫలితం = 1;
		  }

		ఒకవేళ (STRNCMP (dest + nchars - outer, adr + మధ్య, inner) != 0)
		  {
		    రాయి ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, మధ్య, inner);
		    ఫలితం = 1;
		  }
	      }

	    ఒకవేళ (STRNCMP (adr + మధ్య, dest + nchars - outer, outer) >= 0)
	      {
		రాయి ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, మధ్య);
		ఫలితం = 1;
	      }

	    ఒకవేళ (STRNCMP (dest + nchars - outer, adr + మధ్య, outer) <= 0)
	      {
		రాయి ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, మధ్య);
		ఫలితం = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  కొరకు (len = 0; len < nchars - outer; ++len)
	    {
	      ఒకవేళ (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  రాయి ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  ఫలితం = 1;
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      adr[nchars - 1] = L('\0');

      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      కొరకు (len = 0; len < nchars - outer + 64; ++len)
		{
		  ఒకవేళ (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      రాయి ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ఫలితం = 1;
		    }
		  ఒకవేళ (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      రాయి ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      ఫలితం = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* stpcpy/wcpcpy test */
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      ఒకవేళ ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  ఫలితం = 1;
		}

	      adr[inner] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  కొరకు (len = 0; len < nchars - outer; ++len)
	    {
	      ఒకవేళ (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  రాయి ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  ఫలితం = 1;
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      adr[nchars - 1] = L('\0');

      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = MAX (outer, nchars64); మధ్య < nchars; ++మధ్య)
	    {
	      adr[మధ్య] = L('\0');

	      కొరకు (inner = 0; inner < nchars - outer; ++ inner)
		{
		  ఒకవేళ ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, మధ్య - outer))
		    {
		      రాయి ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, మధ్య, inner);
		      ఫలితం = 1;
		    }
		}

	      adr[మధ్య] = L('T');
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* memcpy/wmemcpy test */
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  కొరకు (inner = 0; inner < nchars - outer; ++inner)
	    ఒకవేళ (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		ఫలితం = 1;
	      }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* mempcpy/wmempcpy test */
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  కొరకు (inner = 0; inner < nchars - outer; ++inner)
	    ఒకవేళ (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		రాయి ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		ఫలితం = 1;
	      }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}

      /* This function only exists for single-byte characters.  */
#నిర్వచితం_కాకపోతే WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      కొరకు (outer = nchars; outer >= max128; --outer)
	{
	  కొరకు (inner = 0; inner < nchars - outer; ++inner)
	    ఒకవేళ (memccpy (dest, &adr[outer], L('\1'), inner) != ఖాళీ)
	      {
		రాయి ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		ఫలితం = 1;
	      }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
      కొరకు (outer = nchars - 1; outer >= max128; --outer)
	{
	  కొరకు (మధ్య = 0; మధ్య < nchars - outer; ++మధ్య)
	    {
	      memset (dest, L('\2'), మధ్య + 1);
	      కొరకు (inner = 0; inner < మధ్య; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  ఒకవేళ (memccpy (dest, &adr[outer], '\1', మధ్య + 128)
		      !=  dest + inner + 1)
		    {
		      రాయి ("\
			      memccpy flunked partial copy కొరకు outer = %zu, మధ్య = %zu, inner = %zu\n",
			      outer, మధ్య, inner);
		      ఫలితం = 1;
		    }
		  లేకపోతే ఒకవేళ (dest[inner + 1] != L('\2'))
		    {
		      రాయి ("\
			      memccpy copied too much కొరకు outer = %zu, మధ్య = %zu, inner = %zu\n",
			      outer, మధ్య, inner);
		      ఫలితం = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  ఒకవేళ (outer == 0)
	    ఆపు;
	}
#అయితే_ముగింపు
    }

  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
