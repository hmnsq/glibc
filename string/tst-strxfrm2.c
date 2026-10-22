#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ test_locale[] = "de_DE.UTF-8";

  ಪೂರ್ಣಾಙ್ಕ res = 0;

  ವರ್ಣ buf[20];
  size_t l1 = strxfrm (ರಿಕ್ತ, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", ಪರಿಮಾಣ (buf));
  ಯದಿ (l3 < ಪರಿಮಾಣ (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ಯದಿ (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ಯದಿ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ಯದಿ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ಯದಿ (setlocale (LC_ALL, test_locale) == ರಿಕ್ತ)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  ಅನ್ಯಥಾ
    {
      l1 = strxfrm (ರಿಕ್ತ, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", ಪರಿಮಾಣ (buf));
      ಯದಿ (l3 < ಪರಿಮಾಣ (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ಯದಿ (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ಯದಿ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ಯದಿ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ಪ್ರತ್ಯಾಗಮ res;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
