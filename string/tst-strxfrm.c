/* Based on a test case by Paul Eggert.  */
#समावेश <locale.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>


अक्षर स्थिर string[] = "";


अटल पूर्णांक
test (स्थिर अक्षर *locale)
{
  माप_प्रकार bufsize;
  माप_प्रकार r;
  माप_प्रकार l;
  अक्षर *buf;
  locale_t loc;
  पूर्णांक परिणाम = 0;

  अगर (रखो_क्षेत्र (LC_COLLATE, locale) == शून्य)
    {
      म_लिखो ("cannot set locale \"%s\"\n", locale);
      वापस 1;
    }
  bufsize = strxfrm (शून्य, string, 0) + 1;
  buf = दो_स्मृति (bufsize);
  अगर (buf == शून्य)
    {
      म_लिखो ("cannot allocate %zd bytes\n", bufsize);
      वापस 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = म_माप (buf);
  अगर (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       परिणाम = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, शून्य);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = म_माप (buf);
  अगर (r != l)
    {
       म_लिखो ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       परिणाम = 1;
    }

  freelocale (loc);

  मुक्त (buf);

  वापस परिणाम;
}


पूर्णांक
do_test (व्योम)
{
  पूर्णांक परिणाम = 0;

  परिणाम |= test ("C");
  परिणाम |= test ("en_US.ISO-8859-1");
  परिणाम |= test ("de_DE.UTF-8");

  वापस परिणाम;
}

#समावेश <support/test-driver.c>
