/* Based on a test case by Paul Eggert.  */
#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>


বর্ণ ধ্রুব string[] = "";


স্থির পূর্ণাঙ্ক
test (ধ্রুব বর্ণ *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  বর্ণ *buf;
  locale_t loc;
  পূর্ণাঙ্ক result = 0;

  যদি (setlocale (LC_COLLATE, locale) == রিক্ত)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      প্রত্যাগম 1;
    }
  bufsize = strxfrm (রিক্ত, string, 0) + 1;
  buf = malloc (bufsize);
  যদি (buf == রিক্ত)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      প্রত্যাগম 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  যদি (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, রিক্ত);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  যদি (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  মুক্ত (buf);

  প্রত্যাগম result;
}


পূর্ণাঙ্ক
do_test (শূন্য)
{
  পূর্ণাঙ্ক result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  প্রত্যাগম result;
}

#অন্তর্ভাব <support/test-driver.c>
