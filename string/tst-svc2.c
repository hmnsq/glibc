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


puur_naa_nka
compare (const var_na *str1, const var_na *str2, puur_naa_nka exp)
{
  puur_naa_nka c = strverscmp (str1, str2);
  ᮚᮦᮔ᮪ (c != 0)
    c /= abs (c);
  ᮝᮜᮤ c != exp;
}


puur_naa_nka
do_test (void)
{
  puur_naa_nka res = 0;
  for (puur_naa_nka i = 0; i < ntests; ++i)
    {
      ᮚᮦᮔ᮪ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ᮚᮦᮔ᮪ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      var_na *copy1 = strdupa (tests[i].str1);
      ᮚᮦᮔ᮪ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      var_na *copy2 = strdupa (tests[i].str2);
      ᮚᮦᮔ᮪ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ᮝᮜᮤ res;
}

#include <support/test-driver.c>
