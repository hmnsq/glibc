/* Based on a test case by Paul Eggert.  */
#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>


எழுத்து மாறிலி string[] = "";


நிலையான முழு
test (மாறிலி எழுத்து *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  எழுத்து *buf;
  locale_t loc;
  முழு result = 0;

  எனில் (setlocale (LC_COLLATE, locale) == வெற்று)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      திரும்பு 1;
    }
  bufsize = strxfrm (வெற்று, string, 0) + 1;
  buf = malloc (bufsize);
  எனில் (buf == வெற்று)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      திரும்பு 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  எனில் (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, வெற்று);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  எனில் (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  விடுவி (buf);

  திரும்பு result;
}


முழு
do_test (வெறுமை)
{
  முழு result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  திரும்பு result;
}

#அந்தர்பாவ <support/test-driver.c>
