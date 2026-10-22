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

#تعریف_کرو GNU_ماخذ 1

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#تعریف_منسوخ __USE_STRING_INLINES

#شامل <errno.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <unistd.h>
#شامل <sys/mman.h>
#شامل <sys/param.h>

#اگر_غیر_تعریف_شدہ CHAR
# define L(c) c
# define CHAR حرف
# define MEMSET memset
# define STRLEN لڑی_لمبائی
# define STRNLEN strnlen
# define STRCHR strchr
# define STRRCHR strrchr
# define STRCPY strcpy
# define STRNCPY strncpy
# define MEMCMP memcmp
# define STPCPY stpcpy
# define STPNCPY stpncpy
# define MEMCPY حافظہ_نقل
# define MEMPCPY mempcpy
# define MEMCHR memchr
# define STRCMP strcmp
# define STRNCMP لڑی_موازنہ
#اگر_ختم


#تعریف_کرو STRINGIFY(s) STRINGIFY2 (s)
#تعریف_کرو STRINGIFY2(s) #s


صحیح
do_test (خالی)
{
  size_t سائز = sysconf (_SC_PAGESIZE);
  size_t nchars = سائز / حجم (CHAR);
  CHAR *adr;
  CHAR *dest;
  صحیح نتیجہ = 0;

  adr = (CHAR *) mmap (تہی, 3 * سائز, PROT_READ | PROT_WRITE,
		       MAP_نجی | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (تہی, 3 * سائز, PROT_READ | PROT_WRITE,
			MAP_نجی | MAP_ANON, -1, 0);
  اگر (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      اگر (errno == ENOSYS)
	puts ("No test, mmap not available.");
      ورنہ
	{
	  لکھو ("mmap failed: %m");
	  نتیجہ = 1;
	}
    }
  ورنہ
    {
      size_t inner, درمیان, outer, nchars64, max128;

      اگر (nchars > 64)
	nchars64 = nchars - 64;
      ورنہ
	nchars64 = 0;

      اگر (nchars > 128)
	max128 = nchars - 128;
      ورنہ
	max128 = 0;

      mprotect (adr, سائز, PROT_NONE);
      mprotect (adr + 2 * nchars, سائز, PROT_NONE);
      adr += nchars;

      mprotect (dest, سائز, PROT_NONE);
      mprotect (dest + 2 * nchars, سائز, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRLEN), outer, inner);
		  نتیجہ = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* strnlen/wcsnlen test */
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  نتیجہ = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner <= nchars; ++inner)
	    {
	      اگر (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  لکھو ("%s flunked bounded for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  نتیجہ = 1;
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* strchr/wcschr test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      برائے (inner = درمیان; inner < nchars; ++inner)
		{
		  adr[درمیان] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  اگر ((inner == درمیان && cp != تہی)
		      || (inner != درمیان
			  && (cp - &adr[outer]) != درمیان - outer))
		    {
		      لکھو ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRCHR), outer, درمیان, inner);
		      نتیجہ = 1;
		    }

		  adr[inner] = L('T');
		  adr[درمیان] = L('T');
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      اگر (STRCHR (&adr[nchars - 1], L('\n')) != تہی)
	{
	  لکھو ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  نتیجہ = 1;
	}

      /* strrchr/wcsrchr test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      برائے (inner = درمیان; inner < nchars; ++inner)
		{
		  adr[درمیان] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  اگر ((inner == درمیان && cp != تہی)
		      || (inner != درمیان
			  && (cp - &adr[outer]) != درمیان - outer))
		    {
		      لکھو ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STRRCHR), outer, درمیان, inner);
		      نتیجہ = 1;
		    }

		  adr[inner] = L('T');
		  adr[درمیان] = L('T');
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* memchr test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      adr[درمیان] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * سائز);

	      اگر (cp - &adr[outer] != درمیان - outer)
		{
		  لکھو ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (MEMCHR), outer, درمیان);
		  نتیجہ = 1;
		}

	      adr[درمیان] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  اگر (cp != تہی)
	    {
	      لکھو ("%s flunked for outer = %zu\n",
		      STRINGIFY (MEMCHR), outer);
	      نتیجہ = 1;
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* These functions only exist for single-byte characters.  */
#اگر_غیر_تعریف_شدہ WCSTEST
      /* rawmemchr test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      adr[درمیان] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      اگر (cp - &adr[outer] != درمیان - outer)
		{
		  لکھو ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (rawmemchr), outer, درمیان);
		  نتیجہ = 1;
		}

	      adr[درمیان] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* memrchr test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      adr[درمیان] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      اگر (cp - &adr[outer] != درمیان - outer)
		{
		  لکھو ("%s flunked for outer = %zu, middle = %zu\n",
			  STRINGIFY (memrchr), outer, درمیان);
		  نتیجہ = 1;
		}

	      adr[درمیان] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  اگر (cp != تہی)
	    {
	      لکھو ("%s flunked for outer = %zu\n",
		      STRINGIFY (memrchr), outer);
	      نتیجہ = 1;
	    }
	  اگر (outer == 0)
	    توڑو;
	}
#اگر_ختم

      /* strcpy/wcscpy test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STRCPY), outer, inner);
		  نتیجہ = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* strcmp/wcscmp tests */
      برائے (outer = 1; outer < 32; ++outer)
	برائے (درمیان = 0; درمیان < 16; ++درمیان)
	  {
	    MEMSET (adr + درمیان, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    اگر (STRCMP (adr + درمیان, dest + nchars - outer) <= 0)
	      {
		لکھو ("%s 1 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, درمیان);
		نتیجہ = 1;
	      }

	    اگر (STRCMP (dest + nchars - outer, adr + درمیان) >= 0)
	      {
		لکھو ("%s 2 flunked for outer = %zu, middle = %zu\n",
			STRINGIFY (STRCMP), outer, درمیان);
		نتیجہ = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      برائے (outer = 1; outer < 32; ++outer)
	برائے (درمیان = 0; درمیان < 16; ++درمیان)
	  {
	    MEMSET (adr + درمیان, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    برائے (inner = 0; inner < outer; ++inner)
	      {
		اگر (STRNCMP (adr + درمیان, dest + nchars - outer, inner) != 0)
		  {
		    لکھو ("%s 1 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, درمیان, inner);
		    نتیجہ = 1;
		  }

		اگر (STRNCMP (dest + nchars - outer, adr + درمیان, inner) != 0)
		  {
		    لکھو ("%s 2 flunked for outer = %zu, middle = %zu, "
			    "inner = %zu\n",
			    STRINGIFY (STRNCMP), outer, درمیان, inner);
		    نتیجہ = 1;
		  }
	      }

	    اگر (STRNCMP (adr + درمیان, dest + nchars - outer, outer) >= 0)
	      {
		لکھو ("%s 1 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, درمیان);
		نتیجہ = 1;
	      }

	    اگر (STRNCMP (dest + nchars - outer, adr + درمیان, outer) <= 0)
	      {
		لکھو ("%s 2 flunked for outer = %zu, middle = %zu, full\n",
			STRINGIFY (STRNCMP), outer, درمیان);
		نتیجہ = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  برائے (len = 0; len < nchars - outer; ++len)
	    {
	      اگر (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  لکھو ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STRNCPY), outer, len);
		  نتیجہ = 1;
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}
      adr[nchars - 1] = L('\0');

      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      برائے (len = 0; len < nchars - outer + 64; ++len)
		{
		  اگر (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      لکھو ("%s flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      نتیجہ = 1;
		    }
		  اگر (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      لکھو ("%s+1 flunked for outer = %zu, inner = %zu, "
			      "len = %zu\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      نتیجہ = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* stpcpy/wcpcpy test */
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (inner = MAX (outer, nchars64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      اگر ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			  STRINGIFY (STPCPY), outer, inner);
		  نتیجہ = 1;
		}

	      adr[inner] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  size_t len;

	  برائے (len = 0; len < nchars - outer; ++len)
	    {
	      اگر (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  لکھو ("outer %s flunked for outer = %zu, len = %zu\n",
			  STRINGIFY (STPNCPY), outer, len);
		  نتیجہ = 1;
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}
      adr[nchars - 1] = L('\0');

      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = MAX (outer, nchars64); درمیان < nchars; ++درمیان)
	    {
	      adr[درمیان] = L('\0');

	      برائے (inner = 0; inner < nchars - outer; ++ inner)
		{
		  اگر ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, درمیان - outer))
		    {
		      لکھو ("%s flunked for outer = %zu, middle = %zu, "
			      "inner = %zu\n",
			      STRINGIFY (STPNCPY), outer, درمیان, inner);
		      نتیجہ = 1;
		    }
		}

	      adr[درمیان] = L('T');
	    }
	  اگر (outer == 0)
	    توڑو;
	}

      /* memcpy/wmemcpy test */
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  برائے (inner = 0; inner < nchars - outer; ++inner)
	    اگر (MEMCPY (dest, &adr[outer], inner) !=  dest)
	      {
		لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMCPY), outer, inner);
		نتیجہ = 1;
	      }
	  اگر (outer == 0)
	    توڑو;
	}

      /* mempcpy/wmempcpy test */
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  برائے (inner = 0; inner < nchars - outer; ++inner)
	    اگر (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	      {
		لکھو ("%s flunked for outer = %zu, inner = %zu\n",
			STRINGIFY (MEMPCPY), outer, inner);
		نتیجہ = 1;
	      }
	  اگر (outer == 0)
	    توڑو;
	}

      /* This function only exists for single-byte characters.  */
#اگر_غیر_تعریف_شدہ WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      برائے (outer = nchars; outer >= max128; --outer)
	{
	  برائے (inner = 0; inner < nchars - outer; ++inner)
	    اگر (memccpy (dest, &adr[outer], L('\1'), inner) != تہی)
	      {
		لکھو ("memccpy flunked full copy for outer = %zu, inner = %zu\n",
			outer, inner);
		نتیجہ = 1;
	      }
	  اگر (outer == 0)
	    توڑو;
	}
      برائے (outer = nchars - 1; outer >= max128; --outer)
	{
	  برائے (درمیان = 0; درمیان < nchars - outer; ++درمیان)
	    {
	      memset (dest, L('\2'), درمیان + 1);
	      برائے (inner = 0; inner < درمیان; ++inner)
		{
		  adr[outer + inner] = L('\1');

		  اگر (memccpy (dest, &adr[outer], '\1', درمیان + 128)
		      !=  dest + inner + 1)
		    {
		      لکھو ("\
			      memccpy flunked partial copy برائے outer = %zu, درمیان = %zu, inner = %zu\n",
			      outer, درمیان, inner);
		      نتیجہ = 1;
		    }
		  ورنہ اگر (dest[inner + 1] != L('\2'))
		    {
		      لکھو ("\
			      memccpy copied too much برائے outer = %zu, درمیان = %zu, inner = %zu\n",
			      outer, درمیان, inner);
		      نتیجہ = 1;
		    }
		  adr[outer + inner] = L('\0');
		}
	    }
	  اگر (outer == 0)
	    توڑو;
	}
#اگر_ختم
    }

  واپس نتیجہ;
}

#شامل <support/test-driver.c>
