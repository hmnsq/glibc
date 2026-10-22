/* Based on a test case by Paul Eggert.  */
#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>


अक्षर स्थिरांक string[] = "";


स्थिर पूर्णांक
test (स्थिरांक अक्षर *locale)
{
  माप_प्रकार bufsize;
  माप_प्रकार r;
  माप_प्रकार l;
  अक्षर *buf;
  locale_t loc;
  पूर्णांक result = 0;

  जर (रखो_क्षेत्र (LC_COLLATE, locale) == रिक्त)
    {
      म_लिखो ("cannot set locale \"%s\"\n", locale);
      परत 1;
    }
  bufsize = strxfrm (रिक्त, string, 0) + 1;
  buf = दो_स्मृति (bufsize);
  जर (buf == रिक्त)
    {
      म_लिखो ("cannot allocate %zd bytes\n", bufsize);
      परत 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = म_माप (buf);
  जर (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, रिक्त);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = म_माप (buf);
  जर (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  मुक्त (buf);

  परत result;
}


पूर्णांक
do_test (शून्य)
{
  पूर्णांक result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  परत result;
}

#अन्तर्भाव <support/test-driver.c>
