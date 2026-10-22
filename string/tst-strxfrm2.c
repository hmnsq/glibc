#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

পূর্ণসংখ্যা
do_test (শূন্য)
{
  স্থির ধ্রুবক অক্ষর test_locale[] = "de_DE.UTF-8";

  পূর্ণসংখ্যা res = 0;

  অক্ষর buf[20];
  size_t l1 = strxfrm (ফাঁকা, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", আকার (buf));
  যদি (l3 < আকার (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  যদি (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  যদি (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  যদি (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  যদি (setlocale (LC_ALL, test_locale) == ফাঁকা)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  অন্যথা
    {
      l1 = strxfrm (ফাঁকা, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", আকার (buf));
      যদি (l3 < আকার (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      যদি (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      যদি (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      যদি (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ফেরত res;
}

#অন্তর্ভাব <support/test-driver.c>
