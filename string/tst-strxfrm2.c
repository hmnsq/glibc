#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର test_locale[] = "de_DE.UTF-8";

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = 0;

  ଅକ୍ଷର buf[20];
  size_t l1 = strxfrm (ଖାଲି, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", ଆକାର (buf));
  ଯଦି (l3 < ଆକାର (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ଯଦି (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ଯଦି (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ଯଦି (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ଯଦି (setlocale (LC_ALL, test_locale) == ଖାଲି)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  ଅନ୍ୟଥା
    {
      l1 = strxfrm (ଖାଲି, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", ଆକାର (buf));
      ଯଦି (l3 < ଆକାର (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ଯଦି (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ଯଦି (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ଯଦି (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ଫେରନ୍ତୁ res;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
