#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>


સ્થિર સંરચના
{
  અચલ અક્ષર *str1;
  અચલ અક્ષર *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (કદ (tests) / કદ (tests[0]))


પૂર્ણાંક
compare (અચલ અક્ષર *str1, અચલ અક્ષર *str2, પૂર્ણાંક exp)
{
  પૂર્ણાંક c = strverscmp (str1, str2);
  જો (c != 0)
    c /= abs (c);
  પાછા c != exp;
}


પૂર્ણાંક
do_test (શૂન્ય)
{
  પૂર્ણાંક res = 0;
  માટે (પૂર્ણાંક i = 0; i < ntests; ++i)
    {
      જો (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      જો (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      અક્ષર *copy1 = strdupa (tests[i].str1);
      જો (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      અક્ષર *copy2 = strdupa (tests[i].str2);
      જો (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  પાછા res;
}

#અન્તર્ભાવ <support/test-driver.c>
