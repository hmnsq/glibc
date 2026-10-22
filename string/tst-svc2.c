#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>


ساكن بنية
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


صحيح
compare (ثابت حرف *str1, ثابت حرف *str2, صحيح قوت_نما)
{
  صحيح c = strverscmp (str1, str2);
  إذا (c != 0)
    c /= مطلق_قدر (c);
  أرجع c != قوت_نما;
}


صحيح
do_test (فراغ)
{
  صحيح res = 0;
  لكل (صحيح i = 0; i < ntests; ++i)
    {
      إذا (compare (tests[i].str1, tests[i].str2, -1))
	{
	  لکھو ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      إذا (compare (tests[i].str2, tests[i].str1, +1))
	{
	  لکھو ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      حرف *copy1 = strdupa (tests[i].str1);
      إذا (compare (tests[i].str1, copy1, 0))
	{
	  لکھو ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      حرف *copy2 = strdupa (tests[i].str2);
      إذا (compare (tests[i].str2, copy2, 0))
	{
	  لکھو ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  أرجع res;
}

#ضمن <support/test-driver.c>
