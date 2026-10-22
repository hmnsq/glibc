#समावेश <locale.h>
#समावेश <stdio.h>
#समावेश <string.h>

पूर्णांक
do_test (व्योम)
{
  अटल स्थिर अक्षर test_locale[] = "de_DE.UTF-8";

  पूर्णांक res = 0;

  अक्षर buf[20];
  माप_प्रकार l1 = strxfrm (शून्य, "ab", 0);
  माप_प्रकार l2 = strxfrm (buf, "ab", 1);
  माप_प्रकार l3 = strxfrm (buf, "ab", माप (buf));
  अगर (l3 < माप (buf) && म_माप (buf) != l3)
    {
      माला_दो ("C locale l3 test failed");
      res = 1;
    }

  माप_प्रकार l4 = strxfrm (buf, "ab", l1 + 1);
  अगर (l4 < l1 + 1 && म_माप (buf) != l4)
    {
      माला_दो ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  माप_प्रकार l5 = strxfrm (buf, "ab", l1);
  अगर (buf[l1] != 'Z')
    {
      माला_दो ("C locale l5 test failed");
      res = 1;
    }

  अगर (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      माला_दो ("C locale retval test failed");
      res = 1;
    }

  अगर (रखो_क्षेत्र (LC_ALL, test_locale) == शून्य)
    {
      म_लिखो ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  अन्यथा
    {
      l1 = strxfrm (शून्य, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", माप (buf));
      अगर (l3 < माप (buf) && म_माप (buf) != l3)
	{
	  माला_दो ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      अगर (l4 < l1 + 1 && म_माप (buf) != l4)
	{
	  माला_दो ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      अगर (buf[l1] != 'Z')
	{
	  माला_दो ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      अगर (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  माला_दो ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  वापस res;
}

#समावेश <support/test-driver.c>
