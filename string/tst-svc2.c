#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>


ସ୍ଥିର ସଂରଚନା
{
  ଅଚଳ ଅକ୍ଷର *str1;
  ଅଚଳ ଅକ୍ଷର *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (ଆକାର (tests) / ଆକାର (tests[0]))


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
compare (ଅଚଳ ଅକ୍ଷର *str1, ଅଚଳ ଅକ୍ଷର *str2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା exp)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = strverscmp (str1, str2);
  ଯଦି (c != 0)
    c /= abs (c);
  ଫେରନ୍ତୁ c != exp;
}


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = 0;
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ntests; ++i)
    {
      ଯଦି (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ଯଦି (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      ଅକ୍ଷର *copy1 = strdupa (tests[i].str1);
      ଯଦି (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      ଅକ୍ଷର *copy2 = strdupa (tests[i].str2);
      ଯଦି (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ଫେରନ୍ତୁ res;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
