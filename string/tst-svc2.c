#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>


ਸਥਿਰ ਬਣਤਰ
{
  ਅਚਲ ਅੱਖਰ *str1;
  ਅਚਲ ਅੱਖਰ *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ntests (ਆਕਾਰ (tests) / ਆਕਾਰ (tests[0]))


ਪੂਰਨ
compare (ਅਚਲ ਅੱਖਰ *str1, ਅਚਲ ਅੱਖਰ *str2, ਪੂਰਨ ਘਾਤਾਂਕ)
{
  ਪੂਰਨ c = strverscmp (str1, str2);
  ਜੇ (c != 0)
    c /= ਨਿਰਪੇਖ (c);
  ਵਾਪਸ c != ਘਾਤਾਂਕ;
}


ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ res = 0;
  ਲਈ (ਪੂਰਨ i = 0; i < ntests; ++i)
    {
      ਜੇ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  ਲਿਖੋ ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ਜੇ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  ਲਿਖੋ ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      ਅੱਖਰ *copy1 = strdupa (tests[i].str1);
      ਜੇ (compare (tests[i].str1, copy1, 0))
	{
	  ਲਿਖੋ ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      ਅੱਖਰ *copy2 = strdupa (tests[i].str2);
      ਜੇ (compare (tests[i].str2, copy2, 0))
	{
	  ਲਿਖੋ ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  ਵਾਪਸ res;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
