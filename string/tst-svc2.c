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


ကိန်းပြည့်
compare (const var_na *str1, const var_na *str2, ကိန်းပြည့် exp)
{
  ကိန်းပြည့် c = strverscmp (str1, str2);
  အကယ်၍ (c != 0)
    c /= abs (c);
  ပြန်ပေး c != exp;
}


ကိန်းပြည့်
do_test (void)
{
  ကိန်းပြည့် res = 0;
  အတွက် (ကိန်းပြည့် i = 0; i < ntests; ++i)
    {
      အကယ်၍ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      အကယ်၍ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      var_na *copy1 = strdupa (tests[i].str1);
      အကယ်၍ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      var_na *copy2 = strdupa (tests[i].str2);
      အကယ်၍ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ပြန်ပေး res;
}

#include <support/test-driver.c>
