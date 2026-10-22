/* Based on a test case by Paul Eggert.  */
#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>


അക്ഷരം സ്ഥിരം string[] = "";


സ്ഥിതം പൂർണ്ണസംഖ്യ
test (സ്ഥിരം അക്ഷരം *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  അക്ഷരം *buf;
  locale_t loc;
  പൂർണ്ണസംഖ്യ result = 0;

  എങ്കിൽ (setlocale (LC_COLLATE, locale) == ശൂന്യ)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      തിരികെ 1;
    }
  bufsize = strxfrm (ശൂന്യ, string, 0) + 1;
  buf = malloc (bufsize);
  എങ്കിൽ (buf == ശൂന്യ)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      തിരികെ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  എങ്കിൽ (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ശൂന്യ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  എങ്കിൽ (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  സ്വതന്ത്രം (buf);

  തിരികെ result;
}


പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  തിരികെ result;
}

#അന്തര്ഭാവ <support/test-driver.c>
