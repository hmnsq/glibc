#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>


நிலையான கட்டமைப்பு
{
  மாறிலி எழுத்து *str1;
  மாறிலி எழுத்து *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#define ntests (அளவு (tests) / அளவு (tests[0]))


முழு
compare (மாறிலி எழுத்து *str1, மாறிலி எழுத்து *str2, முழு exp)
{
  முழு c = strverscmp (str1, str2);
  எனில் (c != 0)
    c /= abs (c);
  திரும்பு c != exp;
}


முழு
do_test (வெறுமை)
{
  முழு res = 0;
  க்கு (முழு i = 0; i < ntests; ++i)
    {
      எனில் (compare (tests[i].str1, tests[i].str2, -1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      எனில் (compare (tests[i].str2, tests[i].str1, +1))
	{
	  printf ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      எழுத்து *copy1 = strdupa (tests[i].str1);
      எனில் (compare (tests[i].str1, copy1, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      எழுத்து *copy2 = strdupa (tests[i].str2);
      எனில் (compare (tests[i].str2, copy2, 0))
	{
	  printf ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  திரும்பு res;
}

#அந்தர்பாவ <support/test-driver.c>
