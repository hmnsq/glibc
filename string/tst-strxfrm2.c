#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ test_locale[] = "de_DE.UTF-8";

  ಪೂರ್ಣಾಂಕ res = 0;

  ಅಕ್ಷರ buf[20];
  size_t l1 = strxfrm (ಖಾಲಿ, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", ಗಾತ್ರ (buf));
  ಆದರೆ (l3 < ಗಾತ್ರ (buf) && ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  ಆದರೆ (l4 < l1 + 1 && ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  ಆದರೆ (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  ಆದರೆ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  ಆದರೆ (setlocale (LC_ALL, test_locale) == ಖಾಲಿ)
    {
      ಬರೆ ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      l1 = strxfrm (ಖಾಲಿ, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", ಗಾತ್ರ (buf));
      ಆದರೆ (l3 < ಗಾತ್ರ (buf) && ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      ಆದರೆ (l4 < l1 + 1 && ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      ಆದರೆ (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      ಆದರೆ (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  ಹಿಂತಿರುಗಿ res;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
