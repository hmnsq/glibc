#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>


ಸ್ಥಿರ ರಚನೆ
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str1;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#ವ್ಯಾಖ್ಯಾನಿಸು ntests (ಗಾತ್ರ (tests) / ಗಾತ್ರ (tests[0]))


ಪೂರ್ಣಾಂಕ
compare (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str2, ಪೂರ್ಣಾಂಕ ಘಾತಾಂಕ)
{
  ಪೂರ್ಣಾಂಕ c = strverscmp (str1, str2);
  ಆದರೆ (c != 0)
    c /= ನಿರಪೇಕ್ಷ (c);
  ಹಿಂತಿರುಗಿ c != ಘಾತಾಂಕ;
}


ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ res = 0;
  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ntests; ++i)
    {
      ಆದರೆ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  ಬರೆ ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ಆದರೆ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  ಬರೆ ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      ಅಕ್ಷರ *copy1 = strdupa (tests[i].str1);
      ಆದರೆ (compare (tests[i].str1, copy1, 0))
	{
	  ಬರೆ ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      ಅಕ್ಷರ *copy2 = strdupa (tests[i].str2);
      ಆದರೆ (compare (tests[i].str2, copy2, 0))
	{
	  ಬರೆ ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ಹಿಂತಿರುಗಿ res;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
