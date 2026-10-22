#include <locale.h>
#include <stdio.h>
#include <string.h>

ចំនួនគត់
do_test (void)
{
  static const var_na test_locale[] = "de_DE.UTF-8";

  ចំនួនគត់ res = 0;

  var_na buf[20];
  size_t l1 = strxfrm (NULL, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", parimaa_na (buf));
  ប្រសិនបើ (l3 < parimaa_na (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ប្រសិនបើ (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ប្រសិនបើ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ប្រសិនបើ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ប្រសិនបើ (setlocale (LC_ALL, test_locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  បើមិនដូច្នេះ
    {
      l1 = strxfrm (NULL, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", parimaa_na (buf));
      ប្រសិនបើ (l3 < parimaa_na (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ប្រសិនបើ (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ប្រសិនបើ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ប្រសិនបើ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ត្រឡប់ res;
}

#include <support/test-driver.c>
