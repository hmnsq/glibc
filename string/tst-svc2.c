#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>


अटल काष्ठा
{
  स्थिर अक्षर *str1;
  स्थिर अक्षर *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#घोषणा ntests (माप (tests) / माप (tests[0]))


पूर्णांक
compare (स्थिर अक्षर *str1, स्थिर अक्षर *str2, पूर्णांक exp)
{
  पूर्णांक c = strverscmp (str1, str2);
  अगर (c != 0)
    c /= असल (c);
  वापस c != exp;
}


पूर्णांक
do_test (व्योम)
{
  पूर्णांक res = 0;
  क्रम (पूर्णांक i = 0; i < ntests; ++i)
    {
      अगर (compare (tests[i].str1, tests[i].str2, -1))
	{
	  म_लिखो ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      अगर (compare (tests[i].str2, tests[i].str1, +1))
	{
	  म_लिखो ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      अक्षर *copy1 = strdupa (tests[i].str1);
      अगर (compare (tests[i].str1, copy1, 0))
	{
	  म_लिखो ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      अक्षर *copy2 = strdupa (tests[i].str2);
      अगर (compare (tests[i].str2, copy2, 0))
	{
	  म_लिखो ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  वापस res;
}

#समावेश <support/test-driver.c>
