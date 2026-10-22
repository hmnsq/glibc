#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>


స్థిర నిర్మాణం
{
  స్థిరరాశి అక్షరం *str1;
  స్థిరరాశి అక్షరం *str2;
} tests[] =
  {
    { "B0075022800016.gbp.corp.com", "B007502280067.gbp.corp.com" },
    { "B0075022800016.gbp.corp.com", "B007502357019.GBP.CORP.COM" },
    { "B007502280067.gbp.corp.com", "B007502357019.GBP.CORP.COM" }
  };
#నిర్వచించు ntests (పరిమాణం (tests) / పరిమాణం (tests[0]))


పూర్ణాంకం
compare (స్థిరరాశి అక్షరం *str1, స్థిరరాశి అక్షరం *str2, పూర్ణాంకం ఘాతాంకం)
{
  పూర్ణాంకం c = strverscmp (str1, str2);
  ఒకవేళ (c != 0)
    c /= నిరపేక్ష (c);
  తిరిగి c != ఘాతాంకం;
}


పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం res = 0;
  కొరకు (పూర్ణాంకం i = 0; i < ntests; ++i)
    {
      ఒకవేళ (compare (tests[i].str1, tests[i].str2, -1))
	{
	  రాయి ("FAIL: \"%s\" > \"%s\"\n", tests[i].str1, tests[i].str2);
	  res = 1;
	}
      ఒకవేళ (compare (tests[i].str2, tests[i].str1, +1))
	{
	  రాయి ("FAIL: \"%s\" > \"%s\"\n", tests[i].str2, tests[i].str1);
	  res = 1;
	}
      అక్షరం *copy1 = strdupa (tests[i].str1);
      ఒకవేళ (compare (tests[i].str1, copy1, 0))
	{
	  రాయి ("FAIL: \"%s\" != \"%s\"\n", tests[i].str1, copy1);
	  res = 1;
	}
      అక్షరం *copy2 = strdupa (tests[i].str2);
      ఒకవేళ (compare (tests[i].str2, copy2, 0))
	{
	  రాయి ("FAIL: \"%s\" != \"%s\"\n", tests[i].str2, copy2);
	  res = 1;
	}
    }
  తిరిగి res;
}

#అన్తర్భావ <support/test-driver.c>
