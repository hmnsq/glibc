#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>


സ്ഥിതം ഘടന
{
  സ്ഥിരം അക്ഷരം *str1;
  സ്ഥിരം അക്ഷരം *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (വലുപ്പം (tests) / വലുപ്പം (tests[0]))


പൂർണ്ണസംഖ്യ
compare (സ്ഥിരം അക്ഷരം *str1, സ്ഥിരം അക്ഷരം *str2, പൂർണ്ണസംഖ്യ exp)
{
  പൂർണ്ണസംഖ്യ c = strverscmp (str1, str2);
  എങ്കിൽ (c != 0)
    c /= abs (c);
  തിരികെ c != exp;
}


പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ res = 0;
  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < ntests; ++i)
    {
      എങ്കിൽ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      എങ്കിൽ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      അക്ഷരം *copy1 = strdupa (tests[i].str1);
      എങ്കിൽ (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      അക്ഷരം *copy2 = strdupa (tests[i].str2);
      എങ്കിൽ (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  തിരികെ res;
}

#അന്തര്ഭാവ <support/test-driver.c>
