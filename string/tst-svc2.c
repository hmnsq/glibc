#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>


ایستا ساختار
{
  ثابت نویسه *str1;
  ثابت نویسه *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (اندازه (tests) / اندازه (tests[0]))


صحیح
compare (ثابت نویسه *str1, ثابت نویسه *str2, صحیح exp)
{
  صحیح c = strverscmp (str1, str2);
  اگر (c != 0)
    c /= abs (c);
  بازگشت c != exp;
}


صحیح
do_test (تهی)
{
  صحیح res = 0;
  برای (صحیح i = 0; i < ntests; ++i)
    {
      اگر (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      اگر (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      نویسه *copy1 = strdupa (tests[i].str1);
      اگر (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      نویسه *copy2 = strdupa (tests[i].str2);
      اگر (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  بازگشت res;
}

#شامل <support/test-driver.c>
