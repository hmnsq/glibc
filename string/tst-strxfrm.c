/* Based on a test case by Paul Eggert.  */
#شامل <locale.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>


نویسه ثابت string[] = "";


ایستا صحیح
test (ثابت نویسه *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  نویسه *buf;
  locale_t loc;
  صحیح result = 0;

  اگر (setlocale (LC_COLLATE, locale) == پوچ)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      بازگشت 1;
    }
  bufsize = strxfrm (پوچ, string, 0) + 1;
  buf = malloc (bufsize);
  اگر (buf == پوچ)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      بازگشت 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  اگر (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, پوچ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  اگر (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  آزاد (buf);

  بازگشت result;
}


صحیح
do_test (تهی)
{
  صحیح result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  بازگشت result;
}

#شامل <support/test-driver.c>
