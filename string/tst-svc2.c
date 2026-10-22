#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>


স্থির সংরচনা
{
  ধ্রুৱ ৱর্ণ *str1;
  ধ্রুৱ ৱর্ণ *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (পরিমাণ (tests) / পরিমাণ (tests[0]))


পূর্ণাঙ্ক
compare (ধ্রুৱ ৱর্ণ *str1, ধ্রুৱ ৱর্ণ *str2, পূর্ণাঙ্ক exp)
{
  পূর্ণাঙ্ক c = strverscmp (str1, str2);
  যদি (c != 0)
    c /= abs (c);
  ঘূৰাই c != exp;
}


পূর্ণাঙ্ক
do_test (শূন্য)
{
  পূর্ণাঙ্ক res = 0;
  বাবে (পূর্ণাঙ্ক i = 0; i < ntests; ++i)
    {
      যদি (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      যদি (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      ৱর্ণ *copy1 = strdupa (tests[i].str1);
      যদি (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      ৱর্ণ *copy2 = strdupa (tests[i].str2);
      যদি (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ঘূৰাই res;
}

#অন্তর্ভাৱ <support/test-driver.c>
