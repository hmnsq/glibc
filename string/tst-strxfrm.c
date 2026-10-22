/* Based on a test case by Paul Eggert.  */
#شامل <locale.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>


حرف ثابت string[] = "";


ساکن صحیح
test (ثابت حرف *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  حرف *buf;
  locale_t loc;
  صحیح نتیجہ = 0;

  اگر (setlocale (LC_COLLATE, locale) == تہی)
    {
      لکھو ("cannot set locale \"%s\"\n", locale);
      واپس 1;
    }
  bufsize = strxfrm (تہی, string, 0) + 1;
  buf = حافظہ_دو (bufsize);
  اگر (buf == تہی)
    {
      لکھو ("cannot allocate %zd bytes\n", bufsize);
      واپس 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = لڑی_لمبائی (buf);
  اگر (r != l)
    {
       لکھو ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجہ = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, تہی);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = لڑی_لمبائی (buf);
  اگر (r != l)
    {
       لکھو ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجہ = 1;
    }

  freelocale (loc);

  آزاد (buf);

  واپس نتیجہ;
}


صحیح
do_test (خالی)
{
  صحیح نتیجہ = 0;

  نتیجہ |= test ("C");
  نتیجہ |= test ("en_US.ISO-8859-1");
  نتیجہ |= test ("de_DE.UTF-8");

  واپس نتیجہ;
}

#شامل <support/test-driver.c>
