#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


स्थिर संरचना
{
  स्थिरांक अक्षर *str1;
  स्थिरांक अक्षर *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (आकार (tests) / आकार (tests[0]))


पूर्णांक
compare (स्थिरांक अक्षर *str1, स्थिरांक अक्षर *str2, पूर्णांक exp)
{
  पूर्णांक c = strverscmp (str1, str2);
  जर (c != 0)
    c /= असल (c);
  परत c != exp;
}


पूर्णांक
do_test (शून्य)
{
  पूर्णांक res = 0;
  साठी (पूर्णांक i = 0; i < ntests; ++i)
    {
      जर (compare (tests[i].str1, tests[i].str2, -1))
	{
	  म_लिखो ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      जर (compare (tests[i].str2, tests[i].str1, +1))
	{
	  म_लिखो ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      अक्षर *copy1 = strdupa (tests[i].str1);
      जर (compare (tests[i].str1, copy1, 0))
	{
	  म_लिखो ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      अक्षर *copy2 = strdupa (tests[i].str2);
      जर (compare (tests[i].str2, copy2, 0))
	{
	  म_लिखो ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  परत res;
}

#अन्तर्भाव <support/test-driver.c>
