#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਸਥਿਰ ਅਚਲ ਅੱਖਰ test_locale[] = "de_DE.UTF-8";

  ਪੂਰਨ res = 0;

  ਅੱਖਰ buf[20];
  size_t l1 = strxfrm (ਨਿਰਾ, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", ਆਕਾਰ (buf));
  ਜੇ (l3 < ਆਕਾਰ (buf) && ਲੜੀ_ਲੰਬਾਈ (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ਜੇ (l4 < l1 + 1 && ਲੜੀ_ਲੰਬਾਈ (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ਜੇ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ਜੇ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ਜੇ (setlocale (LC_ALL, test_locale) == ਨਿਰਾ)
    {
      ਲਿਖੋ ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  ਨਹੀਂਤਾਂ
    {
      l1 = strxfrm (ਨਿਰਾ, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", ਆਕਾਰ (buf));
      ਜੇ (l3 < ਆਕਾਰ (buf) && ਲੜੀ_ਲੰਬਾਈ (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ਜੇ (l4 < l1 + 1 && ਲੜੀ_ਲੰਬਾਈ (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ਜੇ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ਜੇ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ਵਾਪਸ res;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
