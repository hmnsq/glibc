#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  സ്ഥിതം സ്ഥിരം അക്ഷരം test_locale[] = "de_DE.UTF-8";

  പൂർണ്ണസംഖ്യ res = 0;

  അക്ഷരം buf[20];
  size_t l1 = strxfrm (ശൂന്യ, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", വലുപ്പം (buf));
  എങ്കിൽ (l3 < വലുപ്പം (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  എങ്കിൽ (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  എങ്കിൽ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  എങ്കിൽ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  എങ്കിൽ (setlocale (LC_ALL, test_locale) == ശൂന്യ)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  അല്ലെങ്കിൽ
    {
      l1 = strxfrm (ശൂന്യ, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", വലുപ്പം (buf));
      എങ്കിൽ (l3 < വലുപ്പം (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      എങ്കിൽ (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      എങ്കിൽ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      എങ്കിൽ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  തിരികെ res;
}

#അന്തര്ഭാവ <support/test-driver.c>
