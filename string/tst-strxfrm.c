/* Based on a test case by Paul Eggert.  */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


var_na const string[] = "";


static จำนวนเต็ม
test (const var_na *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  var_na *buf;
  locale_t loc;
  จำนวนเต็ม result = 0;

  ถ้า (setlocale (LC_COLLATE, locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      คืน 1;
    }
  bufsize = strxfrm (NULL, string, 0) + 1;
  buf = malloc (bufsize);
  ถ้า (buf == NULL)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      คืน 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  ถ้า (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, NULL);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  ถ้า (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  free (buf);

  คืน result;
}


จำนวนเต็ม
do_test (void)
{
  จำนวนเต็ม result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  คืน result;
}

#include <support/test-driver.c>
