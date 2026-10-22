#ضمن <locale.h>
#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت حرف test_locale[] = "de_DE.UTF-8";

  صحيح res = 0;

  حرف buf[20];
  size_t l1 = strxfrm (عدم, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", حجم (buf));
  إذا (l3 < حجم (buf) && مزي_اوږدوالی (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  إذا (l4 < l1 + 1 && مزي_اوږدوالی (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  إذا (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  إذا (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  إذا (setlocale (LC_ALL, test_locale) == عدم)
    {
      چاپ_کړه ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  وإلا
    {
      l1 = strxfrm (عدم, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", حجم (buf));
      إذا (l3 < حجم (buf) && مزي_اوږدوالی (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      إذا (l4 < l1 + 1 && مزي_اوږدوالی (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      إذا (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      إذا (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  أرجع res;
}

#ضمن <support/test-driver.c>
