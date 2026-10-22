/* Based on a test case by Paul Eggert.  */
#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>


অক্ষর ধ্রুবক string[] = "";


স্থির পূর্ণসংখ্যা
test (ধ্রুবক অক্ষর *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  অক্ষর *buf;
  locale_t loc;
  পূর্ণসংখ্যা ফলাফল = 0;

  যদি (setlocale (LC_COLLATE, locale) == ফাঁকা)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      ফেরত 1;
    }
  bufsize = strxfrm (ফাঁকা, string, 0) + 1;
  buf = malloc (bufsize);
  যদি (buf == ফাঁকা)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      ফেরত 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  যদি (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ফলাফল = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ফাঁকা);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  যদি (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ফলাফল = 1;
    }

  freelocale (loc);

  মুক্ত (buf);

  ফেরত ফলাফল;
}


পূর্ণসংখ্যা
do_test (শূন্য)
{
  পূর্ণসংখ্যা ফলাফল = 0;

  ফলাফল |= test ("C");
  ফলাফল |= test ("en_US.ISO-8859-1");
  ফলাফল |= test ("de_DE.UTF-8");

  ফেরত ফলাফল;
}

#অন্তর্ভাব <support/test-driver.c>
