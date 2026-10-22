#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>


ساکن ساخت
{
  ثابت حرف *str1;
  ثابت حرف *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#تعریف_کرو ntests (حجم (tests) / حجم (tests[0]))


صحیح
compare (ثابت حرف *str1, ثابت حرف *str2, صحیح قوت_نما)
{
  صحیح c = strverscmp (str1, str2);
  اگر (c != 0)
    c /= مطلق_قدر (c);
  واپس c != قوت_نما;
}


صحیح
do_test (خالی)
{
  صحیح res = 0;
  برائے (صحیح i = 0; i < ntests; ++i)
    {
      اگر (compare (tests[i].str1, tests[i].str2, -1))
	{
	  لکھو ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      اگر (compare (tests[i].str2, tests[i].str1, +1))
	{
	  لکھو ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      حرف *copy1 = strdupa (tests[i].str1);
      اگر (compare (tests[i].str1, copy1, 0))
	{
	  لکھو ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      حرف *copy2 = strdupa (tests[i].str2);
      اگر (compare (tests[i].str2, copy2, 0))
	{
	  لکھو ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  واپس res;
}

#شامل <support/test-driver.c>
