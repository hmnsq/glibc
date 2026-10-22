/* Based on a test case by Paul Eggert.  */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


var_na const string[] = "";


static puur_naa_nka
test (const var_na *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  var_na *buf;
  locale_t loc;
  puur_naa_nka result = 0;

  ᨀᨘ (setlocale (LC_COLLATE, locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      ᨀᨘᨒ 1;
    }
  bufsize = strxfrm (NULL, string, 0) + 1;
  buf = malloc (bufsize);
  ᨀᨘ (buf == NULL)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      ᨀᨘᨒ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  ᨀᨘ (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, NULL);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  ᨀᨘ (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  free (buf);

  ᨀᨘᨒ result;
}


puur_naa_nka
do_test (void)
{
  puur_naa_nka result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  ᨀᨘᨒ result;
}

#include <support/test-driver.c>
