/* Based on a test case by Paul Eggert.  */
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


वर्ण ध्रुव string[] = "";


स्थिर पूर्णाङ्क
test (ध्रुव वर्ण *locale)
{
  माप_प्रकार bufsize;
  माप_प्रकार r;
  माप_प्रकार l;
  वर्ण *buf;
  locale_t loc;
  पूर्णाङ्क result = 0;

  यदि (रखो_क्षेत्र (LC_COLLATE, locale) == रिक्त)
    {
      म_लिखो ("cannot set locale \"%s\"\n", locale);
      प्रत्यागम 1;
    }
  bufsize = strxfrm (रिक्त, string, 0) + 1;
  buf = दो_स्मृति (bufsize);
  यदि (buf == रिक्त)
    {
      म_लिखो ("cannot allocate %zd bytes\n", bufsize);
      प्रत्यागम 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = म_माप (buf);
  यदि (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, रिक्त);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = म_माप (buf);
  यदि (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
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
