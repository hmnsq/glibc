/* Based on a test case by Paul Eggert.  */
#అన్తర్భావ <locale.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>


అక్షరం స్థిరరాశి string[] = "";


స్థిర పూర్ణాంకం
test (స్థిరరాశి అక్షరం *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  అక్షరం *buf;
  locale_t loc;
  పూర్ణాంకం ఫలితం = 0;

  ఒకవేళ (setlocale (LC_COLLATE, locale) == ఖాళీ)
    {
      రాయి ("cannot set locale \"%s\"\n", locale);
      తిరిగి 1;
    }
  bufsize = strxfrm (ఖాళీ, string, 0) + 1;
  buf = జ్ఞాపకం_ఇవ్వు (bufsize);
  ఒకవేళ (buf == ఖాళీ)
    {
      రాయి ("cannot allocate %zd bytes\n", bufsize);
      తిరిగి 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = అక్షరశ్రేణి_పొడవు (buf);
  ఒకవేళ (r != l)
    {
       రాయి ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ఫలితం = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ఖాళీ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = అక్షరశ్రేణి_పొడవు (buf);
  ఒకవేళ (r != l)
    {
       రాయి ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ఫలితం = 1;
    }

  freelocale (loc);

  విడుదల (buf);

  తిరిగి ఫలితం;
}


పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం ఫలితం = 0;

  ఫలితం |= test ("C");
  ఫలితం |= test ("en_US.ISO-8859-1");
  ఫలితం |= test ("de_DE.UTF-8");

  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
