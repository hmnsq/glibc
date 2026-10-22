/* Based on a test case by Paul Eggert.  */
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>


ವರ್ಣ ಧ್ರುವ string[] = "";


ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
test (ಧ್ರುವ ವರ್ಣ *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  ವರ್ಣ *buf;
  locale_t loc;
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  ಯದಿ (setlocale (LC_COLLATE, locale) == ರಿಕ್ತ)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      ಪ್ರತ್ಯಾಗಮ 1;
    }
  bufsize = strxfrm (ರಿಕ್ತ, string, 0) + 1;
  buf = malloc (bufsize);
  ಯದಿ (buf == ರಿಕ್ತ)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      ಪ್ರತ್ಯಾಗಮ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  ಯದಿ (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ರಿಕ್ತ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  ಯದಿ (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  ಮುಕ್ತ (buf);

  ಪ್ರತ್ಯಾಗಮ result;
}


ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  result |= test ("C");
  result |= test ("en_US.ISO-8859-1");
  result |= test ("de_DE.UTF-8");

  ಪ್ರತ್ಯಾಗಮ result;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
