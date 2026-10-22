/* Based on a test case by Paul Eggert.  */
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


वर्ण ध्रुव string[] = "";


स्थिर पूर्णाङ्क
test (ध्रुव वर्ण *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  वर्ण *buf;
  locale_t loc;
  पूर्णाङ्क result = 0;

  जइ (setlocale (LC_COLLATE, locale) == रिक्त)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      प्रत्यागम 1;
    }
  bufsize = strxfrm (रिक्त, string, 0) + 1;
  buf = malloc (bufsize);
  जइ (buf == रिक्त)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      प्रत्यागम 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  जइ (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, रिक्त);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  जइ (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  मुक्त (buf);

  प्रत्यागम result;
}


पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
