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


ចំនួនគត់
compare (const var_na *str1, const var_na *str2, ចំនួនគត់ exp)
{
  ចំនួនគត់ c = strverscmp (str1, str2);
  ប្រសិនបើ (c != 0)
    c /= abs (c);
  ត្រឡប់ c != exp;
}


ចំនួនគត់
do_test (void)
{
  ចំនួនគត់ res = 0;
  សម្រាប់ (ចំនួនគត់ i = 0; i < ntests; ++i)
    {
      ប្រសិនបើ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ប្រសិនបើ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      var_na *copy1 = strdupa (tests[i].str1);
      ប្រសិនបើ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      var_na *copy2 = strdupa (tests[i].str2);
      ប្រសិនបើ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ត្រឡប់ res;
}

#include <support/test-driver.c>
