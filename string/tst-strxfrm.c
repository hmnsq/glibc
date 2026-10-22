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
  صحيح result = 0;

  𐡄𐡍 (setlocale (LC_COLLATE, locale) == عدم)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      أرجع 1;
    }
  bufsize = strxfrm (عدم, string, 0) + 1;
  buf = malloc (bufsize);
  𐡄𐡍 (buf == عدم)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      أرجع 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  𐡄𐡍 (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, عدم);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  𐡄𐡍 (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  حرر (buf);

  أرجع result;
}


صحيح
do_test (فراغ)
{
  صحيح result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  أرجع result;
}

#ضمن <support/test-driver.c>
