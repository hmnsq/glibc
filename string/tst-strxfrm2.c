#شامل <locale.h>
#شامل <stdio.h>
#شامل <string.h>

صحیح
do_test (خالی)
{
  ساکن ثابت حرف test_locale[] = "de_DE.UTF-8";

  صحیح res = 0;

  حرف buf[20];
  size_t l1 = strxfrm (تہی, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", حجم (buf));
  اگر (l3 < حجم (buf) && لڑی_لمبائی (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  اگر (l4 < l1 + 1 && لڑی_لمبائی (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  اگر (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  اگر (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  اگر (setlocale (LC_ALL, test_locale) == تہی)
    {
      لکھو ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  ورنہ
    {
      l1 = strxfrm (تہی, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", حجم (buf));
      اگر (l3 < حجم (buf) && لڑی_لمبائی (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      اگر (l4 < l1 + 1 && لڑی_لمبائی (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      اگر (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      اگر (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  واپس res;
}

#شامل <support/test-driver.c>
