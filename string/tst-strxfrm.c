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
  पूर्णाङ्क परिणाम = 0;

  यदि (setlocale (LC_COLLATE, locale) == रिक्त)
    {
      प्रारूप_लिख ("cannot set locale \"%s\"\n", locale);
      प्रत्यागम 1;
    }
  bufsize = strxfrm (रिक्त, string, 0) + 1;
  buf = स्मृतिं_देहि (bufsize);
  यदि (buf == रिक्त)
    {
      प्रारूप_लिख ("cannot allocate %zd bytes\n", bufsize);
      प्रत्यागम 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = वाक्यदैर्घ्यम् (buf);
  यदि (r != l)
    {
       प्रारूप_लिख ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       परिणाम = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, रिक्त);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = वाक्यदैर्घ्यम् (buf);
  यदि (r != l)
    {
       प्रारूप_लिख ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       परिणाम = 1;
    }

  freelocale (loc);

  मुक्त (buf);

  प्रत्यागम परिणाम;
}


पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क परिणाम = 0;

  परिणाम |= test ("C");
  परिणाम |= test ("en_US.ISO-8859-1");
  परिणाम |= test ("de_DE.UTF-8");

  प्रत्यागम परिणाम;
}

#अन्तर्भाव <support/test-driver.c>
