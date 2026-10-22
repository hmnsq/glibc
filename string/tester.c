/* Tester for string functions.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#जर !defined DO_STRING_INLINES
#undef __USE_STRING_INLINES
#endif

#अन्तर्भाव <sys/cdefs.h>
#अन्तर्भाव <libc-diag.h>

/* Triggered by strncpy fortify wrapper when it is enabled.  */
#जर __GNUC_PREREQ (8, 0)
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif

/* When building with fortify enabled, GCC < 12 issues a warning on the
   fortify strncat wrapper might overflow the destination buffer (the
   failure is tied to -Werror).
   Triggered by strncat fortify wrapper when it is enabled.  */
#जर __GNUC_PREREQ (11, 0)
DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif

#अन्तर्भाव <errno.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <strings.h>
#अन्तर्भाव <fcntl.h>

स्थिर __typeof (bzero) * अस्थिर bzero_indirect = bzero;
स्थिर __typeof (स_रखो) * अस्थिर memset_indirect = स_रखो;

#undef bzero
#undef स_रखो

#define bzero bzero_indirect
#define स_रखो memset_indirect

/* This file tests a range of corner cases of string functions,
   including cases where truncation occurs or where sizes specified
   are larger than the actual buffers, which result in various
   warnings.  */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
#जर __GNUC_PREREQ (5, 0)
DIAG_IGNORE_NEEDS_COMMENT (5.0, "-Wmemset-transposed-args");
#endif
#जर __GNUC_PREREQ (7, 0)
DIAG_IGNORE_NEEDS_COMMENT (9, "-Wrestrict");
DIAG_IGNORE_NEEDS_COMMENT (7, "-Wstringop-overflow=");
#endif


#define	STREQ(a, b)	(म_भेद((a), (b)) == 0)

स्थिरांक अक्षर *it = "<UNSET>";	/* Routine name for message routines. */
माप_प्रकार errors = 0;

/* Complain if condition is not true.  */
स्थिर शून्य
check (पूर्णांक thing, पूर्णांक संख्या)
{
  जर (!thing)
    {
      म_लिखो ("%s flunked test %d\n", it, संख्या);
      ++errors;
    }
}

/* Complain if first two args don't strcmp as equal.  */
स्थिर शून्य
equal (स्थिरांक अक्षर *a, स्थिरांक अक्षर *b, पूर्णांक संख्या)
{
  check (a != रिक्त && b != रिक्त && STREQ (a, b), संख्या);
}

अक्षर one[50];
अक्षर two[50];
अक्षर *cp;

स्थिर शून्य
test_strcmp (शून्य)
{
  it = "strcmp";
  check (म_भेद ("", "") == 0, 1);		/* Trivial case. */
  check (म_भेद ("a", "a") == 0, 2);		/* Identity. */
  check (म_भेद ("abc", "abc") == 0, 3);	/* Multicharacter. */
  check (म_भेद ("abc", "abcd") < 0, 4);	/* Length mismatches. */
  check (म_भेद ("abcd", "abc") > 0, 5);
  check (म_भेद ("abcd", "abce") < 0, 6);	/* Honest miscompares. */
  check (म_भेद ("abce", "abcd") > 0, 7);
  check (म_भेद ("a\203", "a") > 0, 8);		/* Tricky if char signed. */
  check (म_भेद ("a\203", "a\003") > 0, 9);

  {
    अक्षर buf1[0x40], buf2[0x40];
    पूर्णांक i, j;
    साठी (i=0; i < 0x10; i++)
      साठी (j = 0; j < 0x10; j++)
	{
	  पूर्णांक k;
	  साठी (k = 0; k < 0x3f; k++)
	    {
	      buf1[k] = '0' ^ (k & 4);
	      buf2[k] = '4' ^ (k & 4);
	    }
	  buf1[i] = buf1[0x3f] = 0;
	  buf2[j] = buf2[0x3f] = 0;
	  साठी (k = 0; k < 0xf; k++)
	    {
	      पूर्णांक cnum = 0x10+0x10*k+0x100*j+0x1000*i;
	      check (म_भेद (buf1+i,buf2+j) == 0, cnum);
	      buf1[i+k] = 'A' + i + k;
	      buf1[i+k+1] = 0;
	      check (म_भेद (buf1+i,buf2+j) > 0, cnum+1);
	      check (म_भेद (buf2+j,buf1+i) < 0, cnum+2);
	      buf2[j+k] = 'B' + i + k;
	      buf2[j+k+1] = 0;
	      check (म_भेद (buf1+i,buf2+j) < 0, cnum+3);
	      check (म_भेद (buf2+j,buf1+i) > 0, cnum+4);
	      buf2[j+k] = 'A' + i + k;
	      buf1[i] = 'A' + i + 0x80;
	      check (म_भेद (buf1+i,buf2+j) > 0, cnum+5);
	      check (म_भेद (buf2+j,buf1+i) < 0, cnum+6);
	      buf1[i] = 'A' + i;
	    }
	}
  }
}

#define SIMPLE_COPY(fn, n, str, ntest) \
  करा {									      \
    पूर्णांक __n;								      \
    अक्षर *cp;								      \
    साठी (__n = 0; __n < (पूर्णांक) आकार (one); ++__n)			      \
      one[__n] = 'Z';							      \
    fn (one, str);							      \
    साठी (cp = one, __n = 0; __n < n; ++__n, ++cp)			      \
      check (*cp == '0' + (n % 10), ntest);				      \
    check (*cp == '\0', ntest);						      \
  } पर्यंत (0)

स्थिर शून्य
test_strcpy (शून्य)
{
  पूर्णांक i;
  it = "strcpy";
  check (म_नकल (one, "abcd") == one, 1); /* Returned value. */
  equal (one, "abcd", 2);		/* Basic test. */

  (शून्य) म_नकल (one, "x");
  equal (one, "x", 3);			/* Writeover. */
  equal (one+2, "cd", 4);		/* Wrote too much? */

  (शून्य) म_नकल (two, "hi there");
  (शून्य) म_नकल (one, two);
  equal (one, "hi there", 5);		/* Basic test encore. */
  equal (two, "hi there", 6);		/* Stomped on source? */

  (शून्य) म_नकल (one, "");
  equal (one, "", 7);			/* Boundary condition. */

  साठी (i = 0; i < 16; i++)
    {
      (शून्य) म_नकल (one + i, "hi there");	/* Unaligned destination. */
      equal (one + i, "hi there", 8 + (i * 2));
      (शून्य) म_नकल (two, one + i);		/* Unaligned source. */
      equal (two, "hi there", 9 + (i * 2));
    }

  SIMPLE_COPY(म_नकल, 0, "", 41);
  SIMPLE_COPY(म_नकल, 1, "1", 42);
  SIMPLE_COPY(म_नकल, 2, "22", 43);
  SIMPLE_COPY(म_नकल, 3, "333", 44);
  SIMPLE_COPY(म_नकल, 4, "4444", 45);
  SIMPLE_COPY(म_नकल, 5, "55555", 46);
  SIMPLE_COPY(म_नकल, 6, "666666", 47);
  SIMPLE_COPY(म_नकल, 7, "7777777", 48);
  SIMPLE_COPY(म_नकल, 8, "88888888", 49);
  SIMPLE_COPY(म_नकल, 9, "999999999", 50);
  SIMPLE_COPY(म_नकल, 10, "0000000000", 51);
  SIMPLE_COPY(म_नकल, 11, "11111111111", 52);
  SIMPLE_COPY(म_नकल, 12, "222222222222", 53);
  SIMPLE_COPY(म_नकल, 13, "3333333333333", 54);
  SIMPLE_COPY(म_नकल, 14, "44444444444444", 55);
  SIMPLE_COPY(म_नकल, 15, "555555555555555", 56);
  SIMPLE_COPY(म_नकल, 16, "6666666666666666", 57);

  /* Simple test using implicitly coerced `void *' arguments.  */
  स्थिरांक शून्य *src = "frobozz";
  शून्य *dst = one;
  check (म_नकल (dst, src) == dst, 1);
  equal (dst, "frobozz", 2);
}

स्थिर शून्य
test_stpcpy (शून्य)
{
  it = "stpcpy";
  check ((stpcpy (one, "a") - one) == 1, 1);
  equal (one, "a", 2);

  check ((stpcpy (one, "ab") - one) == 2, 3);
  equal (one, "ab", 4);

  check ((stpcpy (one, "abc") - one) == 3, 5);
  equal (one, "abc", 6);

  check ((stpcpy (one, "abcd") - one) == 4, 7);
  equal (one, "abcd", 8);

  check ((stpcpy (one, "abcde") - one) == 5, 9);
  equal (one, "abcde", 10);

  check ((stpcpy (one, "abcdef") - one) == 6, 11);
  equal (one, "abcdef", 12);

  check ((stpcpy (one, "abcdefg") - one) == 7, 13);
  equal (one, "abcdefg", 14);

  check ((stpcpy (one, "abcdefgh") - one) == 8, 15);
  equal (one, "abcdefgh", 16);

  check ((stpcpy (one, "abcdefghi") - one) == 9, 17);
  equal (one, "abcdefghi", 18);

  check ((stpcpy (one, "x") - one) == 1, 19);
  equal (one, "x", 20);			/* Writeover. */
  equal (one+2, "cdefghi", 21);		/* Wrote too much? */

  check ((stpcpy (one, "xx") - one) == 2, 22);
  equal (one, "xx", 23);		/* Writeover. */
  equal (one+3, "defghi", 24);		/* Wrote too much? */

  check ((stpcpy (one, "xxx") - one) == 3, 25);
  equal (one, "xxx", 26);		/* Writeover. */
  equal (one+4, "efghi", 27);		/* Wrote too much? */

  check ((stpcpy (one, "xxxx") - one) == 4, 28);
  equal (one, "xxxx", 29);		/* Writeover. */
  equal (one+5, "fghi", 30);		/* Wrote too much? */

  check ((stpcpy (one, "xxxxx") - one) == 5, 31);
  equal (one, "xxxxx", 32);		/* Writeover. */
  equal (one+6, "ghi", 33);		/* Wrote too much? */

  check ((stpcpy (one, "xxxxxx") - one) == 6, 34);
  equal (one, "xxxxxx", 35);		/* Writeover. */
  equal (one+7, "hi", 36);		/* Wrote too much? */

  check ((stpcpy (one, "xxxxxxx") - one) == 7, 37);
  equal (one, "xxxxxxx", 38);		/* Writeover. */
  equal (one+8, "i", 39);		/* Wrote too much? */

  check ((stpcpy (stpcpy (stpcpy (one, "a"), "b"), "c") - one) == 3, 40);
  equal (one, "abc", 41);
  equal (one + 4, "xxx", 42);

  SIMPLE_COPY(stpcpy, 0, "", 43);
  SIMPLE_COPY(stpcpy, 1, "1", 44);
  SIMPLE_COPY(stpcpy, 2, "22", 45);
  SIMPLE_COPY(stpcpy, 3, "333", 46);
  SIMPLE_COPY(stpcpy, 4, "4444", 47);
  SIMPLE_COPY(stpcpy, 5, "55555", 48);
  SIMPLE_COPY(stpcpy, 6, "666666", 49);
  SIMPLE_COPY(stpcpy, 7, "7777777", 50);
  SIMPLE_COPY(stpcpy, 8, "88888888", 51);
  SIMPLE_COPY(stpcpy, 9, "999999999", 52);
  SIMPLE_COPY(stpcpy, 10, "0000000000", 53);
  SIMPLE_COPY(stpcpy, 11, "11111111111", 54);
  SIMPLE_COPY(stpcpy, 12, "222222222222", 55);
  SIMPLE_COPY(stpcpy, 13, "3333333333333", 56);
  SIMPLE_COPY(stpcpy, 14, "44444444444444", 57);
  SIMPLE_COPY(stpcpy, 15, "555555555555555", 58);
  SIMPLE_COPY(stpcpy, 16, "6666666666666666", 59);
}

स्थिर शून्य
test_stpncpy (शून्य)
{
  it = "stpncpy";
  स_रखो (one, 'x', आकार (one));
  check (stpncpy (one, "abc", 2) == one + 2, 1);
  check (stpncpy (one, "abc", 3) == one + 3, 2);
  check (stpncpy (one, "abc", 4) == one + 3, 3);
  check (one[3] == '\0' && one[4] == 'x', 4);
  check (stpncpy (one, "abcd", 5) == one + 4, 5);
  check (one[4] == '\0' && one[5] == 'x', 6);
  check (stpncpy (one, "abcd", 6) == one + 4, 7);
  check (one[4] == '\0' && one[5] == '\0' && one[6] == 'x', 8);
}

स्थिर शून्य
test_strcat (शून्य)
{
  it = "strcat";
  (शून्य) म_नकल (one, "ijk");
  check (म_जोड़ो (one, "lmn") == one, 1); /* Returned value. */
  equal (one, "ijklmn", 2);		/* Basic test. */

  (शून्य) म_नकल (one, "x");
  (शून्य) म_जोड़ो (one, "yz");
  equal (one, "xyz", 3);			/* Writeover. */
  equal (one+4, "mn", 4);			/* Wrote too much? */

  (शून्य) म_नकल (one, "gh");
  (शून्य) म_नकल (two, "ef");
  (शून्य) म_जोड़ो (one, two);
  equal (one, "ghef", 5);			/* Basic test encore. */
  equal (two, "ef", 6);			/* Stomped on source? */

  (शून्य) म_नकल (one, "");
  (शून्य) म_जोड़ो (one, "");
  equal (one, "", 7);			/* Boundary conditions. */
  (शून्य) म_नकल (one, "ab");
  (शून्य) म_जोड़ो (one, "");
  equal (one, "ab", 8);
  (शून्य) म_नकल (one, "");
  (शून्य) म_जोड़ो (one, "cd");
  equal (one, "cd", 9);

  पूर्णांक ntest = 10;
  अक्षर buf1[80] __attribute__ ((aligned (16)));
  अक्षर buf2[32] __attribute__ ((aligned (16)));
  साठी (माप_प्रकार n1 = 0; n1 < 16; ++n1)
    साठी (माप_प्रकार n2 = 0; n2 < 16; ++n2)
      साठी (माप_प्रकार n3 = 0; n3 < 32; ++n3)
	{
	  माप_प्रकार olderrors = errors;

	  स_रखो (buf1, 'b', आकार (buf1));

	  स_रखो (buf1 + n2, 'a', n3);
	  buf1[n2 + n3] = '\0';
	  म_नकल (buf2 + n1, "123");

	  check (म_जोड़ो (buf1 + n2, buf2 + n1) == buf1 + n2, ntest);
	  जर (errors == olderrors)
	    साठी (माप_प्रकार i = 0; i < आकार (buf1); ++i)
	      {
		जर (i < n2)
		  check (buf1[i] == 'b', ntest);
		अन्यथा जर (i < n2 + n3)
		  check (buf1[i] == 'a', ntest);
		अन्यथा जर (i < n2 + n3 + 3)
		  check (buf1[i] == "123"[i - (n2 + n3)], ntest);
		अन्यथा जर (i == n2 + n3 + 3)
		  check (buf1[i] == '\0', ntest);
		अन्यथा
		  check (buf1[i] == 'b', ntest);

		जर (errors != olderrors)
		  {
		    म_लिखो ("n1=%zu, n2=%zu, n3=%zu, buf1=%02hhx",
			    n1, n2, n3, buf1[0]);
		    साठी (माप_प्रकार j = 1; j < आकार (buf1); ++j)
		      म_लिखो (",%02hhx", buf1[j]);
		    putchar_unlocked ('\n');
		    थांबा;
		  }
	      }
	}
}

स्थिर शून्य
test_strncat (शून्य)
{
  /* First test it as strcat, with big counts, then test the count
     mechanism.  */
  it = "strncat";
  (शून्य) म_नकल (one, "ijk");
  check (म_जोड़न (one, "lmn", 99) == one, 1);	/* Returned value. */
  equal (one, "ijklmn", 2);		/* Basic test. */

  (शून्य) म_नकल (one, "x");
  (शून्य) म_जोड़न (one, "yz", 99);
  equal (one, "xyz", 3);		/* Writeover. */
  equal (one+4, "mn", 4);		/* Wrote too much? */

  (शून्य) म_नकल (one, "gh");
  (शून्य) म_नकल (two, "ef");
  /* When building with fortify enabled, GCC 6 issues an warning the fortify
     wrapper might overflow the destination buffer.  However, GCC does not
     provide a specific flag to disable the warning (the failure is tied to
     -Werror).  So to avoid disable all errors, only enable the check for
     GCC 7 or newer.  */
#जर __GNUC_PREREQ (7, 0)
  (शून्य) म_जोड़न (one, two, 99);
  equal (one, "ghef", 5);			/* Basic test encore. */
#अन्यथा
  equal (one, "gh", 2);
#endif
  equal (two, "ef", 6);			/* Stomped on source? */

  (शून्य) म_नकल (one, "");
  (शून्य) म_जोड़न (one, "", 99);
  equal (one, "", 7);			/* Boundary conditions. */
  (शून्य) म_नकल (one, "ab");
  (शून्य) म_जोड़न (one, "", 99);
  equal (one, "ab", 8);
  (शून्य) म_नकल (one, "");
  (शून्य) म_जोड़न (one, "cd", 99);
  equal (one, "cd", 9);

  (शून्य) म_नकल (one, "ab");
  (शून्य) म_जोड़न (one, "cdef", 2);
  equal (one, "abcd", 10);			/* Count-limited. */

  (शून्य) म_जोड़न (one, "gh", 0);
  equal (one, "abcd", 11);			/* Zero count. */

  (शून्य) म_जोड़न (one, "gh", 2);
  equal (one, "abcdgh", 12);		/* Count and length equal. */

  (शून्य) म_जोड़न (one, "ij", (माप_प्रकार)-1);	/* set sign bit in count */
  equal (one, "abcdghij", 13);

  पूर्णांक ntest = 14;
  अक्षर buf1[80] __attribute__ ((aligned (16)));
  अक्षर buf2[32] __attribute__ ((aligned (16)));
  साठी (माप_प्रकार n1 = 0; n1 < 16; ++n1)
    साठी (माप_प्रकार n2 = 0; n2 < 16; ++n2)
      साठी (माप_प्रकार n3 = 0; n3 < 32; ++n3)
	साठी (माप_प्रकार n4 = 0; n4 < 16; ++n4)
	  {
	    माप_प्रकार olderrors = errors;

	    स_रखो (buf1, 'b', आकार (buf1));

	    स_रखो (buf1 + n2, 'a', n3);
	    buf1[n2 + n3] = '\0';
	    म_नकल (buf2 + n1, "123");

	    check (म_जोड़न (buf1 + n2, buf2 + n1, ~((माप_प्रकार) 0) - n4)
		   == buf1 + n2, ntest);
	    जर (errors == olderrors)
	      साठी (माप_प्रकार i = 0; i < आकार (buf1); ++i)
		{
		  जर (i < n2)
		    check (buf1[i] == 'b', ntest);
		  अन्यथा जर (i < n2 + n3)
		    check (buf1[i] == 'a', ntest);
		  अन्यथा जर (i < n2 + n3 + 3)
		    check (buf1[i] == "123"[i - (n2 + n3)], ntest);
		  अन्यथा जर (i == n2 + n3 + 3)
		    check (buf1[i] == '\0', ntest);
		  अन्यथा
		    check (buf1[i] == 'b', ntest);

		  जर (errors != olderrors)
		    {
		      म_लिखो ("n1=%zu, n2=%zu, n3=%zu, n4=%zu, buf1=%02hhx",
			      n1, n2, n3, n4, buf1[0]);
		      साठी (माप_प्रकार j = 1; j < आकार (buf1); ++j)
			म_लिखो (",%02hhx", buf1[j]);
		      putchar_unlocked ('\n');
		      थांबा;
		    }
		}
	  }
}

स्थिर शून्य
test_strncmp (शून्य)
{
  /* First test as strcmp with big counts, then test count code.  */
  it = "strncmp";
  check (म_भेदन ("", "", 99) == 0, 1);	/* Trivial case. */
  check (म_भेदन ("a", "a", 99) == 0, 2);	/* Identity. */
  check (म_भेदन ("abc", "abc", 99) == 0, 3);	/* Multicharacter. */
  check (म_भेदन ("abc", "abcd", 99) < 0, 4);	/* Length unequal. */
  check (म_भेदन ("abcd", "abc", 99) > 0, 5);
  check (म_भेदन ("abcd", "abce", 99) < 0, 6);	/* Honestly unequal. */
  check (म_भेदन ("abce", "abcd", 99) > 0, 7);
  check (म_भेदन ("a\203", "a", 2) > 0, 8);	/* Tricky if '\203' < 0 */
  check (म_भेदन ("a\203", "a\003", 2) > 0, 9);
  check (म_भेदन ("abce", "abcd", 3) == 0, 10);	/* Count limited. */
  check (म_भेदन ("abce", "abc", 3) == 0, 11);	/* Count == length. */
  check (म_भेदन ("abcd", "abce", 4) < 0, 12);	/* Nudging limit. */
  check (म_भेदन ("abc", "def", 0) == 0, 13);	/* Zero count. */
  check (म_भेदन ("abc", "", (माप_प्रकार)-1) > 0, 14);	/* set sign bit in count */
  check (म_भेदन ("abc", "abc", (माप_प्रकार)-2) == 0, 15);
}

स्थिर शून्य
test_strncpy (शून्य)
{
  /* Testing is a bit different because of odd semantics.  */
  it = "strncpy";
  check (म_नकलन (one, "abc", 4) == one, 1);	/* Returned value. */
  equal (one, "abc", 2);			/* Did the copy go right? */

  (शून्य) म_नकल (one, "abcdefgh");
  (शून्य) म_नकलन (one, "xyz", 2);
  equal (one, "xycdefgh", 3);			/* Copy cut by count. */

  (शून्य) म_नकल (one, "abcdefgh");
  (शून्य) म_नकलन (one, "xyz", 3);		/* Copy cut just before NUL. */
  equal (one, "xyzdefgh", 4);

  (शून्य) म_नकल (one, "abcdefgh");
  (शून्य) म_नकलन (one, "xyz", 4);		/* Copy just includes NUL. */
  equal (one, "xyz", 5);
  equal (one+4, "efgh", 6);			/* Wrote too much? */

  (शून्य) म_नकल (one, "abcdefgh");
  (शून्य) म_नकलन (one, "xyz", 5);		/* Copy includes padding. */
  equal (one, "xyz", 7);
  equal (one+4, "", 8);
  equal (one+5, "fgh", 9);

  (शून्य) म_नकल (one, "abc");
  (शून्य) म_नकलन (one, "xyz", 0);		/* Zero-length copy. */
  equal (one, "abc", 10);

  (शून्य) म_नकलन (one, "", 2);		/* Zero-length source. */
  equal (one, "", 11);
  equal (one+1, "", 12);
  equal (one+2, "c", 13);

  (शून्य) म_नकल (one, "hi there");
  (शून्य) म_नकलन (two, one, 9);
  equal (two, "hi there", 14);		/* Just paranoia. */
  equal (one, "hi there", 15);		/* Stomped on source? */
}

स्थिर शून्य
test_strlen (शून्य)
{
  it = "strlen";
  check (म_माप ("") == 0, 1);		/* Empty. */
  check (म_माप ("a") == 1, 2);		/* Single char. */
  check (म_माप ("abcd") == 4, 3);	/* Multiple chars. */
  {
    अक्षर buf[4096];
    पूर्णांक i;
    अक्षर *p;
    साठी (i=0; i < 0x100; i++)
      {
	p = (अक्षर *) ((uintptr_t)(buf + 0xff) & ~0xff) + i;
	म_नकल (p, "OK");
	म_नकल (p+3, "BAD/WRONG");
	check (म_माप (p) == 2, 4+i);
      }
   }
}

स्थिर शून्य
test_strnlen (शून्य)
{
  it = "strnlen";
  check (strnlen ("", 10) == 0, 1);		/* Empty. */
  check (strnlen ("a", 10) == 1, 2);		/* Single char. */
  check (strnlen ("abcd", 10) == 4, 3);		/* Multiple chars. */
  check (strnlen ("foo", (माप_प्रकार) -1) == 3, 4);	/* limits of n. */
  check (strnlen ("abcd", 0) == 0, 5);		/* Restricted. */
  check (strnlen ("abcd", 1) == 1, 6);		/* Restricted. */
  check (strnlen ("abcd", 2) == 2, 7);		/* Restricted. */
  check (strnlen ("abcd", 3) == 3, 8);		/* Restricted. */
  check (strnlen ("abcd", 4) == 4, 9);		/* Restricted. */

  अक्षर buf[4096];
  साठी (पूर्णांक i = 0; i < 0x100; ++i)
    {
      अक्षर *p = (अक्षर *) ((uintptr_t)(buf + 0xff) & ~0xff) + i;
      म_नकल (p, "OK");
      म_नकल (p + 3, "BAD/WRONG");
      check (strnlen (p, 100) == 2, 10 + i);
    }
}

स्थिर शून्य
test_strchr (शून्य)
{
  it = "strchr";
  check (म_अक्षर ("abcd", 'z') == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल (one, "abcd");
  check (म_अक्षर (one, 'c') == one+2, 2);	/* Basic test. */
  check (म_अक्षर (one, 'd') == one+3, 3);	/* End of string. */
  check (म_अक्षर (one, 'a') == one, 4);		/* Beginning. */
  check (म_अक्षर (one, '\0') == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (म_अक्षर (one, 'b') == one+1, 6);	/* Finding first. */
  (शून्य) म_नकल (one, "");
  check (म_अक्षर (one, 'b') == रिक्त, 7);		/* Empty string. */
  check (म_अक्षर (one, '\0') == one, 8);		/* NUL in empty string. */
  {
    अक्षर buf[4096];
    पूर्णांक i;
    अक्षर *p;
    साठी (i=0; i < 0x100; i++)
      {
	p = (अक्षर *) ((uintptr_t) (buf + 0xff) & ~0xff) + i;
	म_नकल (p, "OK");
	म_नकल (p+3, "BAD/WRONG");
	check (म_अक्षर (p, '/') == रिक्त, 9+i);
      }
   }
}

स्थिर शून्य
test_strchrnul (शून्य)
{
  स्थिरांक अक्षर *os;
  it = "strchrnul";
  cp = strchrnul ((os = "abcd"), 'z');
  check (*cp == '\0', 1);			/* Not found. */
  check (cp == os + 4, 2);
  (शून्य) म_नकल (one, "abcd");
  check (strchrnul (one, 'c') == one+2, 3);	/* Basic test. */
  check (strchrnul (one, 'd') == one+3, 4);	/* End of string. */
  check (strchrnul (one, 'a') == one, 5);	/* Beginning. */
  check (strchrnul (one, '\0') == one+4, 6);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (strchrnul (one, 'b') == one+1, 7);	/* Finding first. */
  (शून्य) म_नकल (one, "");
  check (strchrnul (one, 'b') == one, 8);	/* Empty string. */
  check (strchrnul (one, '\0') == one, 9);	/* NUL in empty string. */
  {
    अक्षर buf[4096];
    पूर्णांक i;
    अक्षर *p;
    साठी (i=0; i < 0x100; i++)
      {
	p = (अक्षर *) ((uintptr_t) (buf + 0xff) & ~0xff) + i;
	म_नकल (p, "OK");
	म_नकल (p+3, "BAD/WRONG");
	cp = strchrnul (p, '/');
	check (*cp == '\0', 9+2*i);
	check (cp == p+2, 10+2*i);
      }
   }
}

स्थिर शून्य
test_rawmemchr (शून्य)
{
  it = "rawmemchr";
  (शून्य) म_नकल (one, "abcd");
  check (rawmemchr (one, 'c') == one+2, 1);	/* Basic test. */
  check (rawmemchr (one, 'd') == one+3, 2);	/* End of string. */
  check (rawmemchr (one, 'a') == one, 3);		/* Beginning. */
  check (rawmemchr (one, '\0') == one+4, 4);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (rawmemchr (one, 'b') == one+1, 5);	/* Finding first. */
  (शून्य) म_नकल (one, "");
  check (rawmemchr (one, '\0') == one, 6);	/* NUL in empty string. */
  {
    अक्षर buf[4096];
    पूर्णांक i;
    अक्षर *p;
    साठी (i=0; i < 0x100; i++)
      {
	p = (अक्षर *) ((uintptr_t) (buf + 0xff) & ~0xff) + i;
	म_नकल (p, "OK");
	म_नकल (p+3, "BAD/WRONG");
	check (rawmemchr (p, 'R') == p+8, 6+i);
      }
   }
}

स्थिर शून्य
test_index (शून्य)
{
  it = "index";
  check (index ("abcd", 'z') == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल (one, "abcd");
  check (index (one, 'c') == one+2, 2);	/* Basic test. */
  check (index (one, 'd') == one+3, 3);	/* End of string. */
  check (index (one, 'a') == one, 4);	/* Beginning. */
  check (index (one, '\0') == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (index (one, 'b') == one+1, 6);	/* Finding first. */
  (शून्य) म_नकल (one, "");
  check (index (one, 'b') == रिक्त, 7);	/* Empty string. */
  check (index (one, '\0') == one, 8);	/* NUL in empty string. */
}

स्थिर शून्य
test_strrchr (शून्य)
{
  it = "strrchr";
  check (म_खोजप ("abcd", 'z') == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल (one, "abcd");
  check (म_खोजप (one, 'c') == one+2, 2);	/* Basic test. */
  check (म_खोजप (one, 'd') == one+3, 3);	/* End of string. */
  check (म_खोजप (one, 'a') == one, 4);		/* Beginning. */
  check (म_खोजप (one, '\0') == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (म_खोजप (one, 'b') == one+3, 6);	/* Finding last. */
  (शून्य) म_नकल (one, "");
  check (म_खोजप (one, 'b') == रिक्त, 7);	/* Empty string. */
  check (म_खोजप (one, '\0') == one, 8);	/* NUL in empty string. */
  {
    अक्षर buf[4096];
    पूर्णांक i;
    अक्षर *p;
    साठी (i=0; i < 0x100; i++)
      {
	p = (अक्षर *) ((uintptr_t) (buf + 0xff) & ~0xff) + i;
	म_नकल (p, "OK");
	म_नकल (p+3, "BAD/WRONG");
	check (म_खोजप (p, '/') == रिक्त, 9+i);
      }
   }
}

स्थिर शून्य
test_memrchr (शून्य)
{
  माप_प्रकार l;
  it = "memrchr";
  check (memrchr ("abcd", 'z', 5) == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल (one, "abcd");
  l = म_माप (one) + 1;
  check (memrchr (one, 'c', l) == one+2, 2);	/* Basic test. */
  check (memrchr (one, 'd', l) == one+3, 3);	/* End of string. */
  check (memrchr (one, 'a', l) == one, 4);		/* Beginning. */
  check (memrchr (one, '\0', l) == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  l = म_माप (one) + 1;
  check (memrchr (one, 'b', l) == one+3, 6);	/* Finding last. */
  (शून्य) म_नकल (one, "");
  l = म_माप (one) + 1;
  check (memrchr (one, 'b', l) == रिक्त, 7);	/* Empty string. */
  check (memrchr (one, '\0', l) == one, 8);	/* NUL in empty string. */

  /* now test all possible alignment and length combinations to catch
     bugs due to unrolled loops (assuming unrolling is limited to no
     more than 128 byte chunks: */
  {
    अक्षर buf[128 + आकार (दीर्घ)];
    दीर्घ align, len, i, pos, n = 9;

    साठी (align = 0; align < (दीर्घ) आकार (दीर्घ); ++align) {
      साठी (len = 0; len < (दीर्घ) (आकार (buf) - align); ++len) {
	साठी (i = 0; i < len; ++i)
	  buf[align + i] = 'x';		/* don't depend on memset... */

	साठी (pos = len - 1; pos >= 0; --pos) {
#जर 0
	  म_लिखो("align %d, len %d, pos %d\n", align, len, pos);
#endif
	  check(memrchr(buf + align, 'x', len) == buf + align + pos, n++);
	  check(memrchr(buf + align + pos + 1, 'x', len - (pos + 1)) == रिक्त,
		n++);
	  buf[align + pos] = '-';
	}
      }
    }
  }
}

स्थिर शून्य
test_rindex (शून्य)
{
  it = "rindex";
  check (rindex ("abcd", 'z') == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल (one, "abcd");
  check (rindex (one, 'c') == one+2, 2);	/* Basic test. */
  check (rindex (one, 'd') == one+3, 3);	/* End of string. */
  check (rindex (one, 'a') == one, 4);	/* Beginning. */
  check (rindex (one, '\0') == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल (one, "ababa");
  check (rindex (one, 'b') == one+3, 6);	/* Finding last. */
  (शून्य) म_नकल (one, "");
  check (rindex (one, 'b') == रिक्त, 7);	/* Empty string. */
  check (rindex (one, '\0') == one, 8);	/* NUL in empty string. */
}

स्थिर शून्य
test_strpbrk (शून्य)
{
  it = "strpbrk";
  check(strpbrk("abcd", "z") == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल(one, "abcd");
  check(strpbrk(one, "c") == one+2, 2);	/* Basic test. */
  check(strpbrk(one, "d") == one+3, 3);	/* End of string. */
  check(strpbrk(one, "a") == one, 4);	/* Beginning. */
  check(strpbrk(one, "") == रिक्त, 5);	/* Empty search list. */
  check(strpbrk(one, "cb") == one+1, 6);	/* Multiple search. */
  (शून्य) म_नकल(one, "abcabdea");
  check(strpbrk(one, "b") == one+1, 7);	/* Finding first. */
  check(strpbrk(one, "cb") == one+1, 8);	/* With multiple search. */
  check(strpbrk(one, "db") == one+1, 9);	/* Another variant. */
  (शून्य) म_नकल(one, "");
  check(strpbrk(one, "bc") == रिक्त, 10);	/* Empty string. */
  (शून्य) म_नकल(one, "");
  check(strpbrk(one, "bcd") == रिक्त, 11);	/* Empty string. */
  (शून्य) म_नकल(one, "");
  check(strpbrk(one, "bcde") == रिक्त, 12);	/* Empty string. */
  check(strpbrk(one, "") == रिक्त, 13);	/* Both strings empty. */
  (शून्य) म_नकल(one, "abcabdea");
  check(strpbrk(one, "befg") == one+1, 14);	/* Finding first. */
  check(strpbrk(one, "cbr") == one+1, 15);	/* With multiple search. */
  check(strpbrk(one, "db") == one+1, 16);	/* Another variant. */
  check(strpbrk(one, "efgh") == one+6, 17);	/* And yet another. */
}

स्थिर शून्य
test_strstr (शून्य)
{
  it = "strstr";
  check(म_माला("abcd", "z") == रिक्त, 1);	/* Not found. */
  check(म_माला("abcd", "abx") == रिक्त, 2);	/* Dead end. */
  (शून्य) म_नकल(one, "abcd");
  check(म_माला(one, "c") == one+2, 3);	/* Basic test. */
  check(म_माला(one, "bc") == one+1, 4);	/* Multichar. */
  check(म_माला(one, "d") == one+3, 5);	/* End of string. */
  check(म_माला(one, "cd") == one+2, 6);	/* Tail of string. */
  check(म_माला(one, "abc") == one, 7);	/* Beginning. */
  check(म_माला(one, "abcd") == one, 8);	/* Exact match. */
  check(म_माला(one, "abcde") == रिक्त, 9);	/* Too long. */
  check(म_माला(one, "de") == रिक्त, 10);	/* Past end. */
  check(म_माला(one, "") == one, 11);	/* Finding empty. */
  (शून्य) म_नकल(one, "ababa");
  check(म_माला(one, "ba") == one+1, 12);	/* Finding first. */
  (शून्य) म_नकल(one, "");
  check(म_माला(one, "b") == रिक्त, 13);	/* Empty string. */
  check(म_माला(one, "") == one, 14);	/* Empty in empty string. */
  (शून्य) म_नकल(one, "bcbca");
  check(म_माला(one, "bca") == one+2, 15);	/* False start. */
  (शून्य) म_नकल(one, "bbbcabbca");
  check(म_माला(one, "bbca") == one+1, 16);	/* With overlap. */
}

स्थिर शून्य
test_strspn (शून्य)
{
  it = "strspn";
  check(म_अखोज("abcba", "abc") == 5, 1);	/* Whole string. */
  check(म_अखोज("abcba", "ab") == 2, 2);	/* Partial. */
  check(म_अखोज("abc", "qx") == 0, 3);	/* None. */
  check(म_अखोज("", "ab") == 0, 4);	/* Null string. */
  check(म_अखोज("abc", "") == 0, 5);	/* Null search list. */
}

स्थिर शून्य
test_strcspn (शून्य)
{
  it = "strcspn";
  check(म_खोज("abcba", "qx") == 5, 1);	/* Whole string. */
  check(म_खोज("abcba", "cx") == 2, 2);	/* Partial. */
  check(म_खोज("abc", "abc") == 0, 3);	/* None. */
  check(म_खोज("", "ab") == 0, 4);	/* Null string. */
  check(म_खोज("abc", "") == 3, 5);	/* Null search list. */
}

स्थिर शून्य
test_strtok (शून्य)
{
  it = "strtok";
  (शून्य) म_नकल(one, "first, second, third");
  equal(म_मोहर(one, ", "), "first", 1);	/* Basic test. */
  equal(one, "first", 2);
  equal(म_मोहर((अक्षर *)रिक्त, ", "), "second", 3);
  equal(म_मोहर((अक्षर *)रिक्त, ", "), "third", 4);
  check(म_मोहर((अक्षर *)रिक्त, ", ") == रिक्त, 5);
  (शून्य) म_नकल(one, ", first, ");
  equal(म_मोहर(one, ", "), "first", 6);	/* Extra delims, 1 tok. */
  check(म_मोहर((अक्षर *)रिक्त, ", ") == रिक्त, 7);
  (शून्य) म_नकल(one, "1a, 1b; 2a, 2b");
  equal(म_मोहर(one, ", "), "1a", 8);	/* Changing delim lists. */
  equal(म_मोहर((अक्षर *)रिक्त, "; "), "1b", 9);
  equal(म_मोहर((अक्षर *)रिक्त, ", "), "2a", 10);
  (शून्य) म_नकल(two, "x-y");
  equal(म_मोहर(two, "-"), "x", 11);	/* New string before done. */
  equal(म_मोहर((अक्षर *)रिक्त, "-"), "y", 12);
  check(म_मोहर((अक्षर *)रिक्त, "-") == रिक्त, 13);
  (शून्य) म_नकल(one, "a,b, c,, ,d");
  equal(म_मोहर(one, ", "), "a", 14);	/* Different separators. */
  equal(म_मोहर((अक्षर *)रिक्त, ", "), "b", 15);
  equal(म_मोहर((अक्षर *)रिक्त, " ,"), "c", 16);	/* Permute list too. */
  equal(म_मोहर((अक्षर *)रिक्त, " ,"), "d", 17);
  check(म_मोहर((अक्षर *)रिक्त, ", ") == रिक्त, 18);
  check(म_मोहर((अक्षर *)रिक्त, ", ") == रिक्त, 19);	/* Persistence. */
  (शून्य) म_नकल(one, ", ");
  check(म_मोहर(one, ", ") == रिक्त, 20);	/* No tokens. */
  (शून्य) म_नकल(one, "");
  check(म_मोहर(one, ", ") == रिक्त, 21);	/* Empty string. */
  (शून्य) म_नकल(one, "abc");
  equal(म_मोहर(one, ", "), "abc", 22);	/* No delimiters. */
  check(म_मोहर((अक्षर *)रिक्त, ", ") == रिक्त, 23);
  (शून्य) म_नकल(one, "abc");
  equal(म_मोहर(one, ""), "abc", 24);	/* Empty delimiter list. */
  check(म_मोहर((अक्षर *)रिक्त, "") == रिक्त, 25);
  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) म_नकल(one, "a,b,c");
  equal(म_मोहर(one, ","), "a", 26);	/* Basics again... */
  equal(म_मोहर((अक्षर *)रिक्त, ","), "b", 27);
  equal(म_मोहर((अक्षर *)रिक्त, ","), "c", 28);
  check(म_मोहर((अक्षर *)रिक्त, ",") == रिक्त, 29);
  equal(one+6, "gh", 30);			/* Stomped past end? */
  equal(one, "a", 31);			/* Stomped old tokens? */
  equal(one+2, "b", 32);
  equal(one+4, "c", 33);
}

स्थिर शून्य
test_strtok_r (शून्य)
{
  it = "strtok_r";
  (शून्य) म_नकल(one, "first, second, third");
  cp = रिक्त;	/* Always initialize cp to make sure it doesn't point to some old data.  */
  equal(strtok_r(one, ", ", &cp), "first", 1);	/* Basic test. */
  equal(one, "first", 2);
  equal(strtok_r((अक्षर *)रिक्त, ", ", &cp), "second", 3);
  equal(strtok_r((अक्षर *)रिक्त, ", ", &cp), "third", 4);
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 5);
  (शून्य) म_नकल(one, ", first, ");
  cp = रिक्त;
  equal(strtok_r(one, ", ", &cp), "first", 6);	/* Extra delims, 1 tok. */
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 7);
  (शून्य) म_नकल(one, "1a, 1b; 2a, 2b");
  cp = रिक्त;
  equal(strtok_r(one, ", ", &cp), "1a", 8);	/* Changing delim lists. */
  equal(strtok_r((अक्षर *)रिक्त, "; ", &cp), "1b", 9);
  equal(strtok_r((अक्षर *)रिक्त, ", ", &cp), "2a", 10);
  (शून्य) म_नकल(two, "x-y");
  cp = रिक्त;
  equal(strtok_r(two, "-", &cp), "x", 11);	/* New string before done. */
  equal(strtok_r((अक्षर *)रिक्त, "-", &cp), "y", 12);
  check(strtok_r((अक्षर *)रिक्त, "-", &cp) == रिक्त, 13);
  (शून्य) म_नकल(one, "a,b, c,, ,d");
  cp = रिक्त;
  equal(strtok_r(one, ", ", &cp), "a", 14);	/* Different separators. */
  equal(strtok_r((अक्षर *)रिक्त, ", ", &cp), "b", 15);
  equal(strtok_r((अक्षर *)रिक्त, " ,", &cp), "c", 16);	/* Permute list too. */
  equal(strtok_r((अक्षर *)रिक्त, " ,", &cp), "d", 17);
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 18);
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 19);	/* Persistence. */
  (शून्य) म_नकल(one, ", ");
  cp = रिक्त;
  check(strtok_r(one, ", ", &cp) == रिक्त, 20);	/* No tokens. */
  (शून्य) म_नकल(one, "");
  cp = रिक्त;
  check(strtok_r(one, ", ", &cp) == रिक्त, 21);	/* Empty string. */
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 22);	/* Persistence. */
  (शून्य) म_नकल(one, "abc");
  cp = रिक्त;
  equal(strtok_r(one, ", ", &cp), "abc", 23);	/* No delimiters. */
  check(strtok_r((अक्षर *)रिक्त, ", ", &cp) == रिक्त, 24);
  (शून्य) म_नकल(one, "abc");
  cp = रिक्त;
  equal(strtok_r(one, "", &cp), "abc", 25);	/* Empty delimiter list. */
  check(strtok_r((अक्षर *)रिक्त, "", &cp) == रिक्त, 26);
  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) म_नकल(one, "a,b,c");
  cp = रिक्त;
  equal(strtok_r(one, ",", &cp), "a", 27);	/* Basics again... */
  equal(strtok_r((अक्षर *)रिक्त, ",", &cp), "b", 28);
  equal(strtok_r((अक्षर *)रिक्त, ",", &cp), "c", 29);
  check(strtok_r((अक्षर *)रिक्त, ",", &cp) == रिक्त, 30);
  equal(one+6, "gh", 31);			/* Stomped past end? */
  equal(one, "a", 32);				/* Stomped old tokens? */
  equal(one+2, "b", 33);
  equal(one+4, "c", 34);
  म_नकल (one, ":::");
  cp = रिक्त;
  check (strtok_r (one, ":", &cp) == रिक्त, 35);	/* Must store pointer in cp. */
  check (strtok_r (रिक्त, ":", &cp) == रिक्त, 36);
}

स्थिर शून्य
test_strsep (शून्य)
{
  अक्षर *ptr;
  it = "strsep";
  cp = म_नकल(one, "first, second, third");
  equal(strsep(&cp, ", "), "first", 1);	/* Basic test. */
  equal(one, "first", 2);
  equal(strsep(&cp, ", "), "", 3);
  equal(strsep(&cp, ", "), "second", 4);
  equal(strsep(&cp, ", "), "", 5);
  equal(strsep(&cp, ", "), "third", 6);
  check(strsep(&cp, ", ") == रिक्त, 7);
  cp = म_नकल(one, ", first, ");
  equal(strsep(&cp, ", "), "", 8);
  equal(strsep(&cp, ", "), "", 9);
  equal(strsep(&cp, ", "), "first", 10);	/* Extra delims, 1 tok. */
  equal(strsep(&cp, ", "), "", 11);
  equal(strsep(&cp, ", "), "", 12);
  check(strsep(&cp, ", ") == रिक्त, 13);
  cp = म_नकल(one, "1a, 1b; 2a, 2b");
  equal(strsep(&cp, ", "), "1a", 14);	/* Changing delim lists. */
  equal(strsep(&cp, ", "), "", 15);
  equal(strsep(&cp, "; "), "1b", 16);
  equal(strsep(&cp, ", "), "", 17);
  equal(strsep(&cp, ", "), "2a", 18);
  cp = म_नकल(two, "x-y");
  equal(strsep(&cp, "-"), "x", 19);	/* New string before done. */
  equal(strsep(&cp, "-"), "y", 20);
  check(strsep(&cp, "-") == रिक्त, 21);
  cp = म_नकल(one, "a,b, c,, ,d ");
  equal(strsep(&cp, ", "), "a", 22);	/* Different separators. */
  equal(strsep(&cp, ", "), "b", 23);
  equal(strsep(&cp, " ,"), "", 24);
  equal(strsep(&cp, " ,"), "c", 25);	/* Permute list too. */
  equal(strsep(&cp, " ,"), "", 26);
  equal(strsep(&cp, " ,"), "", 27);
  equal(strsep(&cp, " ,"), "", 28);
  equal(strsep(&cp, " ,"), "d", 29);
  equal(strsep(&cp, " ,"), "", 30);
  check(strsep(&cp, ", ") == रिक्त, 31);
  check(strsep(&cp, ", ") == रिक्त, 32);	/* Persistence. */
  cp = म_नकल(one, ", ");
  equal(strsep(&cp, ", "), "", 33);
  equal(strsep(&cp, ", "), "", 34);
  equal(strsep(&cp, ", "), "", 35);
  check(strsep(&cp, ", ") == रिक्त, 36);	/* No tokens. */
  cp = म_नकल(one, "");
  equal(strsep(&cp, ", "), "", 37);
  check(strsep(&cp, ", ") == रिक्त, 38);	/* Empty string. */
  cp = म_नकल(one, "abc");
  equal(strsep(&cp, ", "), "abc", 39);	/* No delimiters. */
  check(strsep(&cp, ", ") == रिक्त, 40);
  cp = म_नकल(one, "abc");
  equal(strsep(&cp, ""), "abc", 41);	/* Empty delimiter list. */
  check(strsep(&cp, "") == रिक्त, 42);
  (शून्य) म_नकल(one, "abcdefgh");
  cp = म_नकल(one, "a,b,c");
  equal(strsep(&cp, ","), "a", 43);	/* Basics again... */
  equal(strsep(&cp, ","), "b", 44);
  equal(strsep(&cp, ","), "c", 45);
  check(strsep(&cp, ",") == रिक्त, 46);
  equal(one+6, "gh", 47);		/* Stomped past end? */
  equal(one, "a", 48);			/* Stomped old tokens? */
  equal(one+2, "b", 49);
  equal(one+4, "c", 50);

  {
    अक्षर text[] = "This,is,a,test";
    अक्षर *list = strdupa (text);
    equal (strsep (&list, ","), "This", 51);
    equal (strsep (&list, ","), "is", 52);
    equal (strsep (&list, ","), "a", 53);
    equal (strsep (&list, ","), "test", 54);
    check (strsep (&list, ",") == रिक्त, 55);
  }

  cp = म_नकल(one, "a,b, c,, ,d,");
  equal(strsep(&cp, ","), "a", 56);	/* Different separators. */
  equal(strsep(&cp, ","), "b", 57);
  equal(strsep(&cp, ","), " c", 58);	/* Permute list too. */
  equal(strsep(&cp, ","), "", 59);
  equal(strsep(&cp, ","), " ", 60);
  equal(strsep(&cp, ","), "d", 61);
  equal(strsep(&cp, ","), "", 62);
  check(strsep(&cp, ",") == रिक्त, 63);
  check(strsep(&cp, ",") == रिक्त, 64);	/* Persistence. */

  cp = म_नकल(one, "a,b, c,, ,d,");
  equal(strsep(&cp, "xy,"), "a", 65);	/* Different separators. */
  equal(strsep(&cp, "x,y"), "b", 66);
  equal(strsep(&cp, ",xy"), " c", 67);	/* Permute list too. */
  equal(strsep(&cp, "xy,"), "", 68);
  equal(strsep(&cp, "x,y"), " ", 69);
  equal(strsep(&cp, ",xy"), "d", 70);
  equal(strsep(&cp, "xy,"), "", 71);
  check(strsep(&cp, "x,y") == रिक्त, 72);
  check(strsep(&cp, ",xy") == रिक्त, 73);	/* Persistence. */

  cp = म_नकल(one, "ABC");
  one[4] = ':';
  equal(strsep(&cp, "C"), "AB", 74);	/* Access beyond NUL.  */
  ptr = strsep(&cp, ":");
  equal(ptr, "", 75);
  check(ptr == one + 3, 76);
  check(cp == रिक्त, 77);

  cp = म_नकल(one, "ABC");
  one[4] = ':';
  equal(strsep(&cp, "CD"), "AB", 78);	/* Access beyond NUL.  */
  ptr = strsep(&cp, ":.");
  equal(ptr, "", 79);
  check(ptr == one + 3, 80);

  cp = म_नकल(one, "ABC");		/* No token in string.  */
  equal(strsep(&cp, ","), "ABC", 81);
  check(cp == रिक्त, 82);

  *one = '\0';				/* Empty string. */
  cp = one;
  ptr = strsep(&cp, ",");
  equal(ptr, "", 83);
  check(ptr == one, 84);
  check(cp == रिक्त, 85);

  *one = '\0';				/* Empty string and no token. */
  cp = one;
  ptr = strsep(&cp, "");
  equal(ptr, "", 86);
  check(ptr == one , 87);
  check(cp == रिक्त, 88);
}

स्थिर शून्य
test_memcmp (शून्य)
{
  पूर्णांक cnt = 1;
  अक्षर one[21];
  अक्षर two[21];

  it = "memcmp";
  check(स_भेद("a", "a", 1) == 0, cnt++);	/* Identity. */
  check(स_भेद("abc", "abc", 3) == 0, cnt++);	/* Multicharacter. */
  check(स_भेद("abcd", "abcf", 4) < 0, cnt++);	/* Honestly unequal. */
  check(स_भेद("abcf", "abcd", 4) > 0, cnt++);
  check(स_भेद("alph", "cold", 4) < 0, cnt++);
  check(स_भेद("a\203", "a\003", 2) > 0, cnt++);
  check(स_भेद("a\003", "a\203", 2) < 0, cnt++);
  check(स_भेद("a\003bc", "a\203bc", 2) < 0, cnt++);
  check(स_भेद("abc\203", "abc\003", 4) > 0, cnt++);
  check(स_भेद("abc\003", "abc\203", 4) < 0, cnt++);
  check(स_भेद("abcf", "abcd", 3) == 0, cnt++);	/* Count limited. */
  check(स_भेद("abc", "def", 0) == 0, cnt++);	/* Zero count. */
  /* Comparisons with shifting 4-byte boundaries. */
  साठी (पूर्णांक i = 0; i < 4; ++i)
    {
      अक्षर *a = one + i;
      अक्षर *b = two + i;
      स_नकल(a, "--------11112222", 16);
      स_नकल(b, "--------33334444", 16);
      check(स_भेद(b, a, 16) > 0, cnt++);
      check(स_भेद(a, b, 16) < 0, cnt++);
    }
}

स्थिर शून्य
test_memchr (शून्य)
{
  it = "memchr";
  check(स_प्रथम("abcd", 'z', 4) == रिक्त, 1);	/* Not found. */
  (शून्य) म_नकल(one, "abcd");
  check(स_प्रथम(one, 'c', 4) == one+2, 2);	/* Basic test. */
  check(स_प्रथम(one, ~0xff|'c', 4) == one+2, 2);	/* ignore highorder bits. */
  check(स_प्रथम(one, 'd', 4) == one+3, 3);	/* End of string. */
  check(स_प्रथम(one, 'a', 4) == one, 4);	/* Beginning. */
  check(स_प्रथम(one, '\0', 5) == one+4, 5);	/* Finding NUL. */
  (शून्य) म_नकल(one, "ababa");
  check(स_प्रथम(one, 'b', 5) == one+1, 6);	/* Finding first. */
  check(स_प्रथम(one, 'b', 0) == रिक्त, 7);	/* Zero count. */
  check(स_प्रथम(one, 'a', 1) == one, 8);	/* Singleton case. */
  (शून्य) म_नकल(one, "a\203b");
  check(स_प्रथम(one, 0203, 3) == one+1, 9);	/* Unsignedness. */

  /* now test all possible alignment and length combinations to catch
     bugs due to unrolled loops (assuming unrolling is limited to no
     more than 128 byte chunks: */
  {
    अक्षर buf[128 + आकार (दीर्घ)];
    दीर्घ align, len, i, pos;

    साठी (align = 0; align < (दीर्घ) आकार (दीर्घ); ++align) {
      साठी (len = 0; len < (दीर्घ) (आकार (buf) - align); ++len) {
	साठी (i = 0; i < len; ++i) {
	  buf[align + i] = 'x';		/* don't depend on memset... */
	}
	साठी (pos = 0; pos < len; ++pos) {
#जर 0
	  म_लिखो("align %d, len %d, pos %d\n", align, len, pos);
#endif
	  check(स_प्रथम(buf + align, 'x', len) == buf + align + pos, 10);
	  check(स_प्रथम(buf + align, 'x', pos) == रिक्त, 11);
	  buf[align + pos] = '-';
	}
      }
    }
  }
}

स्थिर शून्य
test_memcpy (शून्य)
{
  पूर्णांक i;
  it = "memcpy";
  check(स_नकल(one, "abc", 4) == one, 1);	/* Returned value. */
  equal(one, "abc", 2);			/* Did the copy go right? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) स_नकल(one+1, "xyz", 2);
  equal(one, "axydefgh", 3);		/* Basic test. */

  (शून्य) म_नकल(one, "abc");
  (शून्य) स_नकल(one, "xyz", 0);
  equal(one, "abc", 4);			/* Zero-length copy. */

  (शून्य) म_नकल(one, "hi there");
  (शून्य) म_नकल(two, "foo");
  (शून्य) स_नकल(two, one, 9);
  equal(two, "hi there", 5);		/* Just paranoia. */
  equal(one, "hi there", 6);		/* Stomped on source? */

  साठी (i = 0; i < 16; i++)
    {
      स्थिरांक अक्षर *x = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
      म_नकल (one, x);
      check (स_नकल (one + i, "hi there", 9) == one + i,
	     7 + (i * 6));		/* Unaligned destination. */
      check (स_भेद (one, x, i) == 0, 8 + (i * 6));  /* Wrote under? */
      equal (one + i, "hi there", 9 + (i * 6));
      check (one[i + 9] == 'x', 10 + (i * 6));       /* Wrote over? */
      check (स_नकल (two, one + i, 9) == two,
	     11 + (i * 6));		/* Unaligned source. */
      equal (two, "hi there", 12 + (i * 6));
    }
}

स्थिर शून्य
test_mempcpy (शून्य)
{
  पूर्णांक i;
  it = "mempcpy";
  check(mempcpy(one, "abc", 4) == one + 4, 1);	/* Returned value. */
  equal(one, "abc", 2);			/* Did the copy go right? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) mempcpy(one+1, "xyz", 2);
  equal(one, "axydefgh", 3);		/* Basic test. */

  (शून्य) म_नकल(one, "abc");
  (शून्य) mempcpy(one, "xyz", 0);
  equal(one, "abc", 4);			/* Zero-length copy. */

  (शून्य) म_नकल(one, "hi there");
  (शून्य) म_नकल(two, "foo");
  (शून्य) mempcpy(two, one, 9);
  equal(two, "hi there", 5);		/* Just paranoia. */
  equal(one, "hi there", 6);		/* Stomped on source? */

  साठी (i = 0; i < 16; i++)
    {
      स्थिरांक अक्षर *x = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
      म_नकल (one, x);
      check (mempcpy (one + i, "hi there", 9) == one + i + 9,
	     7 + (i * 6));		/* Unaligned destination. */
      check (स_भेद (one, x, i) == 0, 8 + (i * 6));  /* Wrote under? */
      equal (one + i, "hi there", 9 + (i * 6));
      check (one[i + 9] == 'x', 10 + (i * 6));       /* Wrote over? */
      check (mempcpy (two, one + i, 9) == two + 9,
	     11 + (i * 6));		/* Unaligned source. */
      equal (two, "hi there", 12 + (i * 6));
    }
}

स्थिर शून्य
test_memmove (शून्य)
{
  it = "memmove";
  check(स_हटाओ(one, "abc", 4) == one, 1);	/* Returned value. */
  equal(one, "abc", 2);			/* Did the copy go right? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) स_हटाओ(one+1, "xyz", 2);
  equal(one, "axydefgh", 3);		/* Basic test. */

  (शून्य) म_नकल(one, "abc");
  (शून्य) स_हटाओ(one, "xyz", 0);
  equal(one, "abc", 4);			/* Zero-length copy. */

  (शून्य) म_नकल(one, "hi there");
  (शून्य) म_नकल(two, "foo");
  (शून्य) स_हटाओ(two, one, 9);
  equal(two, "hi there", 5);		/* Just paranoia. */
  equal(one, "hi there", 6);		/* Stomped on source? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) स_हटाओ(one+1, one, 9);
  equal(one, "aabcdefgh", 7);		/* Overlap, right-to-left. */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) स_हटाओ(one+1, one+2, 7);
  equal(one, "acdefgh", 8);		/* Overlap, left-to-right. */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) स_हटाओ(one, one, 9);
  equal(one, "abcdefgh", 9);		/* 100% overlap. */
}

स्थिर शून्य
test_memccpy (शून्य)
{
  /* First test like memcpy, then the search part The SVID, the only
     place where memccpy is mentioned, says overlap might fail, so we
     don't try it.  Besides, it's hard to see the rationale for a
     non-left-to-right memccpy.  */
  it = "memccpy";
  check(memccpy(one, "abc", 'q', 4) == रिक्त, 1);	/* Returned value. */
  equal(one, "abc", 2);			/* Did the copy go right? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) memccpy(one+1, "xyz", 'q', 2);
  equal(one, "axydefgh", 3);		/* Basic test. */

  (शून्य) म_नकल(one, "abc");
  (शून्य) memccpy(one, "xyz", 'q', 0);
  equal(one, "abc", 4);			/* Zero-length copy. */

  (शून्य) म_नकल(one, "hi there");
  (शून्य) म_नकल(two, "foo");
  (शून्य) memccpy(two, one, 'q', 9);
  equal(two, "hi there", 5);		/* Just paranoia. */
  equal(one, "hi there", 6);		/* Stomped on source? */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) म_नकल(two, "horsefeathers");
  check(memccpy(two, one, 'f', 9) == two+6, 7);	/* Returned value. */
  equal(one, "abcdefgh", 8);		/* Source intact? */
  equal(two, "abcdefeathers", 9);		/* Copy correct? */

  (शून्य) म_नकल(one, "abcd");
  (शून्य) म_नकल(two, "bumblebee");
  check(memccpy(two, one, 'a', 4) == two+1, 10);	/* First char. */
  equal(two, "aumblebee", 11);
  check(memccpy(two, one, 'd', 4) == two+4, 12);	/* Last char. */
  equal(two, "abcdlebee", 13);
  (शून्य) म_नकल(one, "xyz");
  check(memccpy(two, one, 'x', 1) == two+1, 14);	/* Singleton. */
  equal(two, "xbcdlebee", 15);
}

स्थिर शून्य
test_memset (शून्य)
{
  पूर्णांक i;

  it = "memset";
  (शून्य) म_नकल(one, "abcdefgh");
  check(स_रखो(one+1, 'x', 3) == one+1, 1);	/* Return value. */
  equal(one, "axxxefgh", 2);		/* Basic test. */

  (शून्य) स_रखो(one+2, 'y', 0);
  equal(one, "axxxefgh", 3);		/* Zero-length set. */

  (शून्य) स_रखो(one+5, 0, 1);
  equal(one, "axxxe", 4);			/* Zero fill. */
  equal(one+6, "gh", 5);			/* And the leftover. */

  (शून्य) स_रखो(one+2, 010045, 1);
  equal(one, "ax\045xe", 6);		/* Unsigned char convert. */

  /* Non-8bit fill character.  */
  स_रखो (one, 0x101, आकार (one));
  साठी (i = 0; i < (पूर्णांक) आकार (one); ++i)
    check (one[i] == '\01', 7);

  /* Test for more complex versions of memset, for all alignments and
     lengths up to 256. This test takes a little while, perhaps it should
     be made weaker?  */
  {
    अक्षर data[512];
    पूर्णांक j;
    पूर्णांक k;
    पूर्णांक c;

    साठी (i = 0; i < 512; i++)
      data[i] = 'x';
    साठी (c = 0; c <= 'y'; c += 'y')  /* check for memset(,0,) and
					memset(,'y',) */
      साठी (j = 0; j < 256; j++)
	साठी (i = 0; i < 256; i++)
	  {
	    स_रखो (data + i, c, j);
	    साठी (k = 0; k < i; k++)
	      जर (data[k] != 'x')
		जा fail;
	    साठी (k = i; k < i+j; k++)
	      {
		जर (data[k] != c)
		  जा fail;
		data[k] = 'x';
	      }
	    साठी (k = i+j; k < 512; k++)
	      जर (data[k] != 'x')
		जा fail;
	    सुरूठेवा;

	  fail:
	    check (0, 8 + i + j * 256 + (c != 0) * 256 * 256);
	  }
  }
}

स्थिर शून्य
test_bcopy (शून्य)
{
  /* Much like memcpy.  Berklix manual is silent about overlap, so
     don't test it.  */
  it = "bcopy";
  (शून्य) bcopy("abc", one, 4);
  equal(one, "abc", 1);			/* Simple copy. */

  (शून्य) म_नकल(one, "abcdefgh");
  (शून्य) bcopy("xyz", one+1, 2);
  equal(one, "axydefgh", 2);		/* Basic test. */

  (शून्य) म_नकल(one, "abc");
  (शून्य) bcopy("xyz", one, 0);
  equal(one, "abc", 3);			/* Zero-length copy. */

  (शून्य) म_नकल(one, "hi there");
  (शून्य) म_नकल(two, "foo");
  (शून्य) bcopy(one, two, 9);
  equal(two, "hi there", 4);		/* Just paranoia. */
  equal(one, "hi there", 5);		/* Stomped on source? */
}

स्थिर शून्य
test_bzero (शून्य)
{
  it = "bzero";
  (शून्य) म_नकल(one, "abcdef");
  bzero(one+2, 2);
  equal(one, "ab", 1);			/* Basic test. */
  equal(one+3, "", 2);
  equal(one+4, "ef", 3);

  (शून्य) म_नकल(one, "abcdef");
  bzero(one+2, 0);
  equal(one, "abcdef", 4);		/* Zero-length copy. */
}

स्थिर शून्य
test_strndup (शून्य)
{
  अक्षर *p, *q;
  it = "strndup";
  p = strndup("abcdef", 12);
  check(p != रिक्त, 1);
  जर (p != रिक्त)
    {
      equal(p, "abcdef", 2);
      q = strndup(p + 1, 2);
      check(q != रिक्त, 3);
      जर (q != रिक्त)
	equal(q, "bc", 4);
      मुक्त (q);
    }
  मुक्त (p);
  p = strndup("abc def", 3);
  check(p != रिक्त, 5);
  जर (p != रिक्त)
    equal(p, "abc", 6);
  मुक्त (p);
}

स्थिर शून्य
test_bcmp (शून्य)
{
  it = "bcmp";
  check(bcmp("a", "a", 1) == 0, 1);	/* Identity. */
  check(bcmp("abc", "abc", 3) == 0, 2);	/* Multicharacter. */
  check(bcmp("abcd", "abce", 4) != 0, 3);	/* Honestly unequal. */
  check(bcmp("abce", "abcd", 4) != 0, 4);
  check(bcmp("alph", "beta", 4) != 0, 5);
  check(bcmp("abce", "abcd", 3) == 0, 6);	/* Count limited. */
  check(bcmp("abc", "def", 0) == 0, 8);	/* Zero count. */
}

स्थिर शून्य
test_memcmpeq (शून्य)
{
  it = "__memcmpeq";
  check (__memcmpeq ("a", "a", 1) == 0, 1); /* Identity.  */
  check (__memcmpeq ("abc", "abc", 3) == 0, 2); /* Multicharacter.  */
  check (__memcmpeq ("abcd", "abce", 4) != 0, 3); /* Honestly unequal.  */
  check (__memcmpeq ("abce", "abcd", 4) != 0, 4);
  check (__memcmpeq ("alph", "beta", 4) != 0, 5);
  check (__memcmpeq ("abce", "abcd", 3) == 0, 6); /* Count limited.  */
  check (__memcmpeq ("abc", "def", 0) == 0, 8); /* Zero count.  */
}

स्थिर शून्य
test_strerror (शून्य)
{
  it = "strerror";
  check(म_त्रुटि(गलत_तर्क) != 0, 1);
  check(म_त्रुटि(दुस्फल) != 0, 2);
  check(म_त्रुटि(ENOENT) != 0, 3);
}

स्थिर शून्य
test_strcasecmp (शून्य)
{
  it = "strcasecmp";
  /* Note that the locale is "C".  */
  check(strcasecmp("a", "a") == 0, 1);
  check(strcasecmp("a", "A") == 0, 2);
  check(strcasecmp("A", "a") == 0, 3);
  check(strcasecmp("a", "b") < 0, 4);
  check(strcasecmp("c", "b") > 0, 5);
  check(strcasecmp("abc", "AbC") == 0, 6);
  check(strcasecmp("0123456789", "0123456789") == 0, 7);
  check(strcasecmp("", "0123456789") < 0, 8);
  check(strcasecmp("AbC", "") > 0, 9);
  check(strcasecmp("AbC", "A") > 0, 10);
  check(strcasecmp("AbC", "Ab") > 0, 11);
  check(strcasecmp("AbC", "ab") > 0, 12);
}

स्थिर शून्य
test_strncasecmp (शून्य)
{
  it = "strncasecmp";
  /* Note that the locale is "C".  */
  check(strncasecmp("a", "a", 5) == 0, 1);
  check(strncasecmp("a", "A", 5) == 0, 2);
  check(strncasecmp("A", "a", 5) == 0, 3);
  check(strncasecmp("a", "b", 5) < 0, 4);
  check(strncasecmp("c", "b", 5) > 0, 5);
  check(strncasecmp("abc", "AbC", 5) == 0, 6);
  check(strncasecmp("0123456789", "0123456789", 10) == 0, 7);
  check(strncasecmp("", "0123456789", 10) < 0, 8);
  check(strncasecmp("AbC", "", 5) > 0, 9);
  check(strncasecmp("AbC", "A", 5) > 0, 10);
  check(strncasecmp("AbC", "Ab", 5) > 0, 11);
  check(strncasecmp("AbC", "ab", 5) > 0, 12);
  check(strncasecmp("0123456789", "AbC", 0) == 0, 13);
  check(strncasecmp("AbC", "abc", 1) == 0, 14);
  check(strncasecmp("AbC", "abc", 2) == 0, 15);
  check(strncasecmp("AbC", "abc", 3) == 0, 16);
  check(strncasecmp("AbC", "abcd", 3) == 0, 17);
  check(strncasecmp("AbC", "abcd", 4) < 0, 18);
  check(strncasecmp("ADC", "abcd", 1) == 0, 19);
  check(strncasecmp("ADC", "abcd", 2) > 0, 20);
}

पूर्णांक
main (शून्य)
{
  पूर्णांक status;

  /* Test strcmp first because we use it to test other things.  */
  test_strcmp ();

  /* Test strcpy next because we need it to set up other tests.  */
  test_strcpy ();

  /* A closely related function is stpcpy.  */
  test_stpcpy ();

  /* stpncpy.  */
  test_stpncpy ();

  /* strcat.  */
  test_strcat ();

  /* strncat.  */
  test_strncat ();

  /* strncmp.  */
  test_strncmp ();

  /* strncpy.  */
  test_strncpy ();

  /* strlen.  */
  test_strlen ();

  /* strnlen.  */
  test_strnlen ();

  /* strchr.  */
  test_strchr ();

  /* strchrnul.  */
  test_strchrnul ();

  /* rawmemchr.  */
  test_rawmemchr ();

  /* index - just like strchr.  */
  test_index ();

  /* strrchr.  */
  test_strrchr ();

  /* memrchr.  */
  test_memrchr ();

  /* rindex - just like strrchr.  */
  test_rindex ();

  /* strpbrk - somewhat like strchr.  */
  test_strpbrk ();

  /* strstr - somewhat like strchr.  */
  test_strstr ();

  /* strspn.  */
  test_strspn ();

  /* strcspn.  */
  test_strcspn ();

  /* strtok - the hard one.  */
  test_strtok ();

  /* strtok_r.  */
  test_strtok_r ();

  /* strsep.  */
  test_strsep ();

  /* memcmp.  */
  test_memcmp ();

  /* memchr.  */
  test_memchr ();

  /* memcpy - need not work for overlap.  */
  test_memcpy ();

  /* memmove - must work on overlap.  */
  test_memmove ();

  /* mempcpy */
  test_mempcpy ();

  /* memccpy.  */
  test_memccpy ();

  /* memset.  */
  test_memset ();

  /* bcopy.  */
  test_bcopy ();

  /* bzero.  */
  test_bzero ();

  /* bcmp - somewhat like memcmp.  */
  test_bcmp ();

  /* __memcmpeq - somewhat like memcmp.  */
  test_memcmpeq ();

  /* strndup.  */
  test_strndup ();

  /* strerror - VERY system-dependent.  */
  test_strerror ();

  /* strcasecmp.  Without locale dependencies.  */
  test_strcasecmp ();

  /* strncasecmp.  Without locale dependencies.  */
  test_strncasecmp ();

  जर (errors == 0)
    {
      status = निकास_सफल;
      माला_दो("No errors.");
    }
  अन्यथा
    {
      status = निकास_त्रुटि;
      म_लिखो("%zd errors.\n", errors);
    }

  परत status;
}
