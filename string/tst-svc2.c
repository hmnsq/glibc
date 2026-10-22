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


цео
compare (const char *str1, const char *str2, цео exp)
{
  цео c = strverscmp (str1, str2);
  ако (c != 0)
    c /= abs (c);
  врати c != exp;
}


цео
do_test (void)
{
  цео res = 0;
  за (цео i = 0; i < ntests; ++i)
    {
      ако (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ако (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      char *copy1 = strdupa (tests[i].str1);
      ако (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      char *copy2 = strdupa (tests[i].str2);
      ако (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  врати res;
}

#include <support/test-driver.c>
