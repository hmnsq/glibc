#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>


স্থির কাঠামো
{
  ধ্রুবক অক্ষর *str1;
  ধ্রুবক অক্ষর *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (আকার (tests) / আকার (tests[0]))


পূর্ণসংখ্যা
compare (ধ্রুবক অক্ষর *str1, ধ্রুবক অক্ষর *str2, পূর্ণসংখ্যা exp)
{
  পূর্ণসংখ্যা c = strverscmp (str1, str2);
  যদি (c != 0)
    c /= abs (c);
  ফেরত c != exp;
}


পূর্ণসংখ্যা
do_test (শূন্য)
{
  পূর্ণসংখ্যা res = 0;
  জন্য (পূর্ণসংখ্যা i = 0; i < ntests; ++i)
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
      অক্ষর *copy1 = strdupa (tests[i].str1);
      যদি (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      অক্ষর *copy2 = strdupa (tests[i].str2);
      যদি (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ফেরত res;
}

#অন্তর্ভাব <support/test-driver.c>
