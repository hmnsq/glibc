#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static sa_nracanaa
{
  const var_na *str1;
  const var_na *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (parimaa_na (tests) / parimaa_na (tests[0]))


ཧྲིལ
compare (const var_na *str1, const var_na *str2, ཧྲིལ exp)
{
  ཧྲིལ c = strverscmp (str1, str2);
  གལ་སྲིད (c != 0)
    c /= abs (c);
  ལོག c != exp;
}


ཧྲིལ
do_test (void)
{
  ཧྲིལ res = 0;
  དོན་ལུ (ཧྲིལ i = 0; i < ntests; ++i)
    {
      གལ་སྲིད (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      གལ་སྲིད (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      var_na *copy1 = strdupa (tests[i].str1);
      གལ་སྲིད (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      var_na *copy2 = strdupa (tests[i].str2);
      གལ་སྲིད (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ལོག res;
}

#include <support/test-driver.c>
