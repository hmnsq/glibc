/* Based on a test case by Paul Eggert.  */
#ضمن <locale.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>


حرف ثابت string[] = "";


ساكن صحيح
test (ثابت حرف *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  حرف *buf;
  locale_t loc;
  صحيح نتیجہ = 0;

  إذا (setlocale (LC_COLLATE, locale) == عدم)
    {
      لکھو ("cannot set locale \"%s\"\n", locale);
      أرجع 1;
    }
  bufsize = strxfrm (عدم, string, 0) + 1;
  buf = حافظہ_دیو (bufsize);
  إذا (buf == عدم)
    {
      لکھو ("cannot allocate %zd bytes\n", bufsize);
      أرجع 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = لڑی_لمبائی (buf);
  إذا (r != l)
    {
       لکھو ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجہ = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, عدم);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = لڑی_لمبائی (buf);
  إذا (r != l)
    {
       لکھو ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجہ = 1;
    }

  freelocale (loc);

  حرر (buf);

  أرجع نتیجہ;
}


صحيح
do_test (فراغ)
{
  صحيح نتیجہ = 0;

  نتیجہ |= test ("C");
  نتیجہ |= test ("en_US.ISO-8859-1");
  نتیجہ |= test ("de_DE.UTF-8");

  أرجع نتیجہ;
}

#ضمن <support/test-driver.c>
