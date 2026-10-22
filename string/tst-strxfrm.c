/* Based on a test case by Paul Eggert.  */
#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>


અક્ષર અચલ string[] = "";


સ્થિર પૂર્ણાંક
test (અચલ અક્ષર *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  અક્ષર *buf;
  locale_t loc;
  પૂર્ણાંક result = 0;

  જો (setlocale (LC_COLLATE, locale) == ખાલી)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      પાછા 1;
    }
  bufsize = strxfrm (ખાલી, string, 0) + 1;
  buf = malloc (bufsize);
  જો (buf == ખાલી)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      પાછા 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  જો (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ખાલી);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  જો (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  મુક્ત (buf);

  પાછા result;
}


પૂર્ણાંક
do_test (શૂન્ય)
{
  પૂર્ણાંક result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  પાછા result;
}

#અન્તર્ભાવ <support/test-driver.c>
