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
  صحيح پایله = 0;

  إذا (setlocale (LC_COLLATE, locale) == عدم)
    {
      چاپ_کړه ("cannot set locale \"%s\"\n", locale);
      أرجع 1;
    }
  bufsize = strxfrm (عدم, string, 0) + 1;
  buf = حافظه_ورکړه (bufsize);
  إذا (buf == عدم)
    {
      چاپ_کړه ("cannot allocate %zd bytes\n", bufsize);
      أرجع 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = مزي_اوږدوالی (buf);
  إذا (r != l)
    {
       چاپ_کړه ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       پایله = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, عدم);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = مزي_اوږدوالی (buf);
  إذا (r != l)
    {
       چاپ_کړه ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       پایله = 1;
    }

  freelocale (loc);

  حرر (buf);

  أرجع پایله;
}


صحيح
do_test (فراغ)
{
  صحيح پایله = 0;

  پایله |= test ("C");
  پایله |= test ("en_US.ISO-8859-1");
  پایله |= test ("de_DE.UTF-8");

  أرجع پایله;
}

#ضمن <support/test-driver.c>
