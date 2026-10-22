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


ціле
compare (const char *str1, const char *str2, ціле exp)
{
  ціле c = strverscmp (str1, str2);
  якщо (c != 0)
    c /= abs (c);
  повернути c != exp;
}


ціле
do_test (void)
{
  ціле res = 0;
  для (ціле i = 0; i < ntests; ++i)
    {
      якщо (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      якщо (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      char *copy1 = strdupa (tests[i].str1);
      якщо (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      char *copy2 = strdupa (tests[i].str2);
      якщо (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  повернути res;
}

#include <support/test-driver.c>
