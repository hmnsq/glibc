#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


स्थिर संरचना
{
  ध्रुव वर्ण *str1;
  ध्रुव वर्ण *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (परिमाण (tests) / परिमाण (tests[0]))


पूर्णाङ्क
compare (ध्रुव वर्ण *str1, ध्रुव वर्ण *str2, पूर्णाङ्क exp)
{
  पूर्णाङ्क c = strverscmp (str1, str2);
  यदि (c != 0)
    c /= abs (c);
  प्रत्यागम c != exp;
}


पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क res = 0;
  प्रति (पूर्णाङ्क i = 0; i < ntests; ++i)
    {
      यदि (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      यदि (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      वर्ण *copy1 = strdupa (tests[i].str1);
      यदि (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      वर्ण *copy2 = strdupa (tests[i].str2);
      यदि (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  प्रत्यागम res;
}

#अन्तर्भाव <support/test-driver.c>
