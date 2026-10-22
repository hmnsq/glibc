/* Based on a test case by Paul Eggert.  */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


var_na const string[] = "";


static ကိန်းပြည့်
test (const var_na *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  var_na *buf;
  locale_t loc;
  ကိန်းပြည့် result = 0;

  အကယ်၍ (setlocale (LC_COLLATE, locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      ပြန်ပေး 1;
    }
  bufsize = strxfrm (NULL, string, 0) + 1;
  buf = malloc (bufsize);
  အကယ်၍ (buf == NULL)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      ပြန်ပေး 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  အကယ်၍ (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, NULL);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  အကယ်၍ (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  free (buf);

  ပြန်ပေး result;
}


ကိန်းပြည့်
do_test (void)
{
  ကိန်းပြည့် result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  ပြန်ပေး result;
}

#include <support/test-driver.c>
