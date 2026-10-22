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
#تعریف_کن ntests (حجم (tests) / حجم (tests[0]))


صحيح
compare (ثابت حرف *str1, ثابت حرف *str2, صحيح نمایی_تابع)
{
  صحيح c = strverscmp (str1, str2);
  إذا (c != 0)
    c /= قدر_مطلق (c);
  أرجع c != نمایی_تابع;
}


صحيح
do_test (فراغ)
{
  صحيح res = 0;
  لكل (صحيح i = 0; i < ntests; ++i)
    {
      إذا (compare (tests[i].str1, tests[i].str2, -1))
	{
	  چاپ_کن ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      إذا (compare (tests[i].str2, tests[i].str1, +1))
	{
	  چاپ_کن ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      حرف *copy1 = strdupa (tests[i].str1);
      إذا (compare (tests[i].str1, copy1, 0))
	{
	  چاپ_کن ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      حرف *copy2 = strdupa (tests[i].str2);
      إذا (compare (tests[i].str2, copy2, 0))
	{
	  چاپ_کن ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  أرجع res;
}

#ضمن <support/test-driver.c>
