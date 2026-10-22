#అన్తర్భావ <locale.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

పూర్ణాంకం
do_test (శూన్య)
{
  స్థిర స్థిరరాశి అక్షరం test_locale[] = "de_DE.UTF-8";

  పూర్ణాంకం res = 0;

  అక్షరం buf[20];
  size_t l1 = strxfrm (ఖాళీ, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", పరిమాణం (buf));
  ఒకవేళ (l3 < పరిమాణం (buf) && అక్షరశ్రేణి_పొడవు (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ఒకవేళ (l4 < l1 + 1 && అక్షరశ్రేణి_పొడవు (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ఒకవేళ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ఒకవేళ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ఒకవేళ (setlocale (LC_ALL, test_locale) == ఖాళీ)
    {
      రాయి ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  లేకపోతే
    {
      l1 = strxfrm (ఖాళీ, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", పరిమాణం (buf));
      ఒకవేళ (l3 < పరిమాణం (buf) && అక్షరశ్రేణి_పొడవు (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ఒకవేళ (l4 < l1 + 1 && అక్షరశ్రేణి_పొడవు (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ఒకవేళ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ఒకవేళ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  తిరిగి res;
}

#అన్తర్భావ <support/test-driver.c>
