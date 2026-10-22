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


ຈຳນວນເຕັມ
compare (const var_na *str1, const var_na *str2, ຈຳນວນເຕັມ exp)
{
  ຈຳນວນເຕັມ c = strverscmp (str1, str2);
  ຖ້າ (c != 0)
    c /= abs (c);
  ສົ່ງຄືນ c != exp;
}


ຈຳນວນເຕັມ
do_test (void)
{
  ຈຳນວນເຕັມ res = 0;
  ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < ntests; ++i)
    {
      ຖ້າ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ຖ້າ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      var_na *copy1 = strdupa (tests[i].str1);
      ຖ້າ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      var_na *copy2 = strdupa (tests[i].str2);
      ຖ້າ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ສົ່ງຄືນ res;
}

#include <support/test-driver.c>
