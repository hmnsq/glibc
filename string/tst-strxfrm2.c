#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  स्थिर ध्रुव वर्ण test_locale[] = "de_DE.UTF-8";

  पूर्णाङ्क res = 0;

  वर्ण buf[20];
  size_t l1 = strxfrm (रिक्त, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", परिमाण (buf));
  यदि (l3 < परिमाण (buf) && वाक्यदैर्घ्यम् (buf) != l3)
    {
      पङ्क्तिं_लिख ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  यदि (l4 < l1 + 1 && वाक्यदैर्घ्यम् (buf) != l4)
    {
      पङ्क्तिं_लिख ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  यदि (buf[l1] != 'Z')
    {
      पङ्क्तिं_लिख ("C locale l5 test failed");
      res = 1;
    }

  यदि (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      पङ्क्तिं_लिख ("C locale retval test failed");
      res = 1;
    }

  यदि (setlocale (LC_ALL, test_locale) == रिक्त)
    {
      प्रारूप_लिख ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  अन्यथा
    {
      l1 = strxfrm (रिक्त, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", परिमाण (buf));
      यदि (l3 < परिमाण (buf) && वाक्यदैर्घ्यम् (buf) != l3)
	{
	  पङ्क्तिं_लिख ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      यदि (l4 < l1 + 1 && वाक्यदैर्घ्यम् (buf) != l4)
	{
	  पङ्क्तिं_लिख ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      यदि (buf[l1] != 'Z')
	{
	  पङ्क्तिं_लिख ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      यदि (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  पङ्क्तिं_लिख ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  प्रत्यागम res;
}

#अन्तर्भाव <support/test-driver.c>
