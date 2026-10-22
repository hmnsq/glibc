#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static struct
{
  const char *str1;
  const char *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (sizeof (tests) / sizeof (tests[0]))


整数
compare (const char *str1, const char *str2, 整数 exp)
{
  整数 c = strverscmp (str1, str2);
  もし (c != 0)
    c /= abs (c);
  戻る c != exp;
}


整数
do_test (void)
{
  整数 res = 0;
  ために (整数 i = 0; i < ntests; ++i)
    {
      もし (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      もし (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      char *copy1 = strdupa (tests[i].str1);
      もし (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      char *copy2 = strdupa (tests[i].str2);
      もし (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  戻る res;
}

#include <support/test-driver.c>
