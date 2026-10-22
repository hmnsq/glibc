#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>


ಸ್ಥಿರ ಸಂರಚನಾ
{
  ಧ್ರುವ ವರ್ಣ *str1;
  ಧ್ರುವ ವರ್ಣ *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (ಪರಿಮಾಣ (tests) / ಪರಿಮಾಣ (tests[0]))


ಪೂರ್ಣಾಙ್ಕ
compare (ಧ್ರುವ ವರ್ಣ *str1, ಧ್ರುವ ವರ್ಣ *str2, ಪೂರ್ಣಾಙ್ಕ exp)
{
  ಪೂರ್ಣಾಙ್ಕ c = strverscmp (str1, str2);
  ಯದಿ (c != 0)
    c /= abs (c);
  ಪ್ರತ್ಯಾಗಮ c != exp;
}


ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ res = 0;
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ntests; ++i)
    {
      ಯದಿ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ಯದಿ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      ವರ್ಣ *copy1 = strdupa (tests[i].str1);
      ಯದಿ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      ವರ್ಣ *copy2 = strdupa (tests[i].str2);
      ಯದಿ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ಪ್ರತ್ಯಾಗಮ res;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
