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
  صحيح نتيجو = 0;

  إذا (setlocale (LC_COLLATE, locale) == عدم)
    {
      لکو ("cannot set locale \"%s\"\n", locale);
      أرجع 1;
    }
  bufsize = strxfrm (عدم, string, 0) + 1;
  buf = يادگيري_ڏيو (bufsize);
  إذا (buf == عدم)
    {
      لکو ("cannot allocate %zd bytes\n", bufsize);
      أرجع 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = لڙي_ڊيگهه (buf);
  إذا (r != l)
    {
       لکو ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتيجو = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, عدم);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = لڙي_ڊيگهه (buf);
  إذا (r != l)
    {
       لکو ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       نتيجو = 1;
    }

  freelocale (loc);

  حرر (buf);

  أرجع نتيجو;
}


صحيح
do_test (فراغ)
{
  صحيح نتيجو = 0;

  نتيجو |= test ("C");
  نتيجو |= test ("en_US.ISO-8859-1");
  نتيجو |= test ("de_DE.UTF-8");

  أرجع نتيجو;
}

#ضمن <support/test-driver.c>
