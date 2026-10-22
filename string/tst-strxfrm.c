/* Based on a test case by Paul Eggert.  */
#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>


ଅକ୍ଷର ଅଚଳ string[] = "";


ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test (ଅଚଳ ଅକ୍ଷର *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  ଅକ୍ଷର *buf;
  locale_t loc;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;

  ଯଦି (setlocale (LC_COLLATE, locale) == ଖାଲି)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      ଫେରନ୍ତୁ 1;
    }
  bufsize = strxfrm (ଖାଲି, string, 0) + 1;
  buf = malloc (bufsize);
  ଯଦି (buf == ଖାଲି)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      ଫେରନ୍ତୁ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  ଯଦି (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ଖାଲି);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  ଯଦି (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  ମୁକ୍ତ (buf);

  ଫେରନ୍ତୁ result;
}


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  ଫେରନ୍ତୁ result;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
