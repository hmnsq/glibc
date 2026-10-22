#include <locale.h>
#include <stdio.h>
#include <string.h>

จำนวนเต็ม
do_test (void)
{
  static const var_na test_locale[] = "de_DE.UTF-8";

  จำนวนเต็ม res = 0;

  var_na buf[20];
  size_t l1 = strxfrm (NULL, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", parimaa_na (buf));
  ถ้า (l3 < parimaa_na (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ถ้า (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ถ้า (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ถ้า (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ถ้า (setlocale (LC_ALL, test_locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  มิฉะนั้น
    {
      l1 = strxfrm (NULL, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", parimaa_na (buf));
      ถ้า (l3 < parimaa_na (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ถ้า (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ถ้า (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ถ้า (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  คืน res;
}

#include <support/test-driver.c>
