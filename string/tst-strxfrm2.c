#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

முழு
do_test (வெறுமை)
{
  நிலையான மாறிலி எழுத்து test_locale[] = "de_DE.UTF-8";

  முழு res = 0;

  எழுத்து buf[20];
  size_t l1 = strxfrm (வெற்று, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", அளவு (buf));
  எனில் (l3 < அளவு (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  எனில் (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  எனில் (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  எனில் (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  எனில் (setlocale (LC_ALL, test_locale) == வெற்று)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  இல்லையெனில்
    {
      l1 = strxfrm (வெற்று, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", அளவு (buf));
      எனில் (l3 < அளவு (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      எனில் (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      எனில் (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      எனில் (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  திரும்பு res;
}

#அந்தர்பாவ <support/test-driver.c>
