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
  صحيح نتیجه = 0;

  إذا (setlocale (LC_COLLATE, locale) == عدم)
    {
      چاپ_کن ("cannot set locale \"%s\"\n", locale);
      أرجع 1;
    }
  bufsize = strxfrm (عدم, string, 0) + 1;
  buf = حافظه_بده (bufsize);
  إذا (buf == عدم)
    {
      چاپ_کن ("cannot allocate %zd bytes\n", bufsize);
      أرجع 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = طول_رشته (buf);
  إذا (r != l)
    {
       چاپ_کن ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجه = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, عدم);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = طول_رشته (buf);
  إذا (r != l)
    {
       چاپ_کن ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتیجه = 1;
    }

  freelocale (loc);

  حرر (buf);

  أرجع نتیجه;
}


صحيح
do_test (فراغ)
{
  صحيح نتیجه = 0;

  نتیجه |= test ("C");
  نتیجه |= test ("en_US.ISO-8859-1");
  نتیجه |= test ("de_DE.UTF-8");

  أرجع نتیجه;
}

#ضمن <support/test-driver.c>
