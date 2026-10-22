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

#تعریف_کن GNU_منبع 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#لغو_تعریف __USE_STRING_INLINES

#ضمن <errno.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <unistd.h>
#ضمن <sys/mman.h>
#ضمن <sys/param.h>

#اگر_تعریف_نشده CHAR
# define L(c) c
# define CHAR حرف
# define MEMSET memset
# define STRLEN طول_رشته
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY کپی_حافظه
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP مقایسه_رشته
#پایان_اگر


#تعریف_کن STRINGIFY(s) STRINGIFY2 (s)
#تعریف_کن STRINGIFY2(s) #s


صحيح
do_test (فراغ)
{
  size_t اندازه = sysconf (_SC_PAGESIZE);
  size_t nchars = اندازه / حجم (CHAR);
  CHAR *adr;
  CHAR *dest;
  صحيح نتیجه = 0;

  adr = (CHAR *) mmap (عدم, 3 * اندازه, PROT_READ | PROT_WRITE,
		       MAP_خصوصی | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (عدم, 3 * اندازه, PROT_READ | PROT_WRITE,
			MAP_خصوصی | MAP_ANON, -1, 0);
  إذا (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      إذا (errno == ENOSYS)
	puts ("No test, mmap not available.");
      وإلا
	{
	  چاپ_کن ("mmap failed: %m");
	  نتیجه = 1;
	}
    }
  وإلا
    {
      size_t inner, میانه, outer, nchars64, max128;

      إذا (nchars > 64)
	nchars64 = nchars - 64;
      وإلا
	nchars64 = 0;

      إذا (nchars > 128)
	max128 = nchars - 128;
      وإلا
	max128 = 0;

      mprotect (adr, اندازه, PROT_NONE);
      mprotect (adr + 2 * nchars, اندازه, PROT_NONE);
      adr += nchars;

      mprotect (dest, اندازه, PROT_NONE);
      mprotect (dest + 2 * nchars, اندازه, PROT_NONE);
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
		  چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  نتیجه = 1;
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
		  چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  نتیجه = 1;
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
		  چاپ_کن ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  نتیجه = 1;
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* strchr/wcschr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      لكل (inner = میانه; inner < nchars; ++inner)
		{
		  adr[میانه] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  إذا ((inner == میانه && cp != عدم)
		      || (inner != میانه
			  && (cp - &adr[outer]) != میانه - outer))
		    {
		      چاپ_کن ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, میانه, inner);
		      نتیجه = 1;
		    }

		  adr[inner] = L('T');
		  adr[میانه] = L('T');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      إذا (STRCHR (&adr[nchars - 1], L('\n')) != عدم)
	{
	  چاپ_کن ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  نتیجه = 1;
	}

      /* strrchr/wcsrchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      لكل (inner = میانه; inner < nchars; ++inner)
		{
		  adr[میانه] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  إذا ((inner == میانه && cp != عدم)
		      || (inner != میانه
			  && (cp - &adr[outer]) != میانه - outer))
		    {
		      چاپ_کن ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, میانه, inner);
		      نتیجه = 1;
		    }

		  adr[inner] = L('T');
		  adr[میانه] = L('T');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* memchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * اندازه);

	      إذا (cp - &adr[outer] != میانه - outer)
		{
		  چاپ_کن ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, میانه);
		  نتیجه = 1;
		}

	      adr[میانه] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  إذا (cp != عدم)
	    {
	      چاپ_کن ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      نتیجه = 1;
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* These functions only exist for single-byte characters.  */
#اگر_تعریف_نشده WCSTEST
      /* rawmemchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      إذا (cp - &adr[outer] != میانه - outer)
		{
		  چاپ_کن ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, میانه);
		  نتیجه = 1;
		}

	      adr[میانه] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* memrchr test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      إذا (cp - &adr[outer] != میانه - outer)
		{
		  چاپ_کن ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, میانه);
		  نتیجه = 1;
		}

	      adr[میانه] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  إذا (cp != عدم)
	    {
	      چاپ_کن ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      نتیجه = 1;
	    }
	  إذا (outer == 0)
	    اكسر;
	}
#پایان_اگر

      /* strcpy/wcscpy test */
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      إذا (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  نتیجه = 1;
		}

	      adr[inner] = L('T');
	    }
	  إذا (outer == 0)
	    اكسر;
	}

      /* strcmp/wcscmp tests */
      لكل (outer = 1; outer < 32; ++outer)
	لكل (میانه = 0; میانه < 16; ++میانه)
	  {
	    MEMSET (adr + میانه, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    إذا (STRCMP (adr + میانه, dest + nchars - outer) <= 0)
	      {
		چاپ_کن ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, میانه);
		نتیجه = 1;
	      }

	    إذا (STRCMP (dest + nchars - outer, adr + میانه) >= 0)
	      {
		چاپ_کن ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, میانه);
		نتیجه = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      لكل (outer = 1; outer < 32; ++outer)
	لكل (میانه = 0; میانه < 16; ++میانه)
	  {
	    MEMSET (adr + میانه, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    لكل (inner = 0; inner < outer; ++inner)
	      {
		إذا (STRNCMP (adr + میانه, dest + nchars - outer, inner) != 0)
		  {
		    چاپ_کن ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, میانه, inner);
		    نتیجه = 1;
		  }

		إذا (STRNCMP (dest + nchars - outer, adr + میانه, inner) != 0)
		  {
		    چاپ_کن ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, میانه, inner);
		    نتیجه = 1;
		  }
	      }

	    إذا (STRNCMP (adr + میانه, dest + nchars - outer, outer) >= 0)
	      {
		چاپ_کن ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, میانه);
		نتیجه = 1;
	      }

	    إذا (STRNCMP (dest + nchars - outer, adr + میانه, outer) <= 0)
	      {
		چاپ_کن ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, میانه);
		نتیجه = 1;
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
		  چاپ_کن ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  نتیجه = 1;
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
		      چاپ_کن ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      نتیجه = 1;
		    }
		  إذا (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      چاپ_کن ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      نتیجه = 1;
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
		  چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  نتیجه = 1;
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
		  چاپ_کن ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  نتیجه = 1;
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}
      adr[nchars - 1] = L('\0');

      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = MAX (outer, nchars64); میانه < nchars; ++میانه)
	    {
	      adr[میانه] = L('\0');

	      لكل (inner = 0; inner < nchars - outer; ++ inner)
		{
		  إذا ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, میانه - outer))
		    {
		      چاپ_کن ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, میانه, inner);
		      نتیجه = 1;
		    }
		}

	      adr[میانه] = L('T');
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
		چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		نتیجه = 1;
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
		چاپ_کن ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		نتیجه = 1;
	      }
	  إذا (outer == 0)
	    اكسر;
	}

      /* This function only exists for single-byte characters.  */
#اگر_تعریف_نشده WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      لكل (outer = nchars; outer >= max128; --outer)
	{
	  لكل (inner = 0; inner < nchars - outer; ++inner)
	    إذا (memccpy (dest, &adr[outer], L('\1'), inner) != عدم)
	      {
		چاپ_کن ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		نتیجه = 1;
	      }
	  إذا (outer == 0)
	    اكسر;
	}
      لكل (outer = nchars - 1; outer >= max128; --outer)
	{
	  لكل (میانه = 0; میانه < nchars - outer; ++میانه)
	    {
	      memset (dest, L('\2'), میانه + 1);
	      لكل (inner = 0; inner < میانه; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  إذا (memccpy (dest, &adr[outer], '\1', میانه + 128)
		      !=  dest + inner + 1)
		    {
		      چاپ_کن ("\
			      memccpy flunked partial copy لكل outer = %zu, میانه = %zu, inner = %zu\n",
			      outer, میانه, inner);
		      نتیجه = 1;
		    }
		  وإلا إذا (dest[inner + 1] != L('\2'))
		    {
		      چاپ_کن ("\
			      memccpy copied too much لكل outer = %zu, میانه = %zu, inner = %zu\n",
			      outer, میانه, inner);
		      نتیجه = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  إذا (outer == 0)
	    اكسر;
	}
#پایان_اگر
    }

  أرجع نتیجه;
}

#ضمن <support/test-driver.c>
