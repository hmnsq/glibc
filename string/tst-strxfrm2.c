#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

પૂર્ણાંક
do_test (શૂન્ય)
{
  સ્થિર અચલ અક્ષર test_locale[] = "de_DE.UTF-8";

  પૂર્ણાંક res = 0;

  અક્ષર buf[20];
  size_t l1 = strxfrm (ખાલી, "ab", 0);
  size_t l2 = strxfrm (buf, "ab", 1);
  size_t l3 = strxfrm (buf, "ab", કદ (buf));
  જો (l3 < કદ (buf) && strlen (buf) != l3)
    {
      puts ("C locale l3 test failed");
      res = 1;
    }

  size_t l4 = strxfrm (buf, "ab", l1 + 1);
  જો (l4 < l1 + 1 && strlen (buf) != l4)
    {
      puts ("C locale l4 test failed");
      res = 1;
    }

  buf[l1] = 'Z';
  size_t l5 = strxfrm (buf, "ab", l1);
  જો (buf[l1] != 'Z')
    {
      puts ("C locale l5 test failed");
      res = 1;
    }

  જો (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
    {
      puts ("C locale retval test failed");
      res = 1;
    }

  જો (setlocale (LC_ALL, test_locale) == ખાલી)
    {
      printf ("cannot set locale \"%s\"\n", test_locale);
      res = 1;
    }
  નહીંતર
    {
      l1 = strxfrm (ખાલી, "ab", 0);
      l2 = strxfrm (buf, "ab", 1);
      l3 = strxfrm (buf, "ab", કદ (buf));
      જો (l3 < કદ (buf) && strlen (buf) != l3)
	{
	  puts ("UTF-8 locale l3 test failed");
	  res = 1;
	}

      l4 = strxfrm (buf, "ab", l1 + 1);
      જો (l4 < l1 + 1 && strlen (buf) != l4)
	{
	  puts ("UTF-8 locale l4 test failed");
	  res = 1;
	}

      buf[l1] = 'Z';
      l5 = strxfrm (buf, "ab", l1);
      જો (buf[l1] != 'Z')
	{
	  puts ("UTF-8 locale l5 test failed");
	  res = 1;
	}

      જો (l1 != l2 || l1 != l3 || l1 != l4 || l1 != l5)
	{
	  puts ("UTF-8 locale retval test failed");
	  res = 1;
	}
    }

  પાછા res;
}

#અન્તર્ભાવ <support/test-driver.c>
