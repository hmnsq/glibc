/* Based on a test case by Paul Eggert.  */
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>


ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ string[] = "";


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  ಅಕ್ಷರ *buf;
  locale_t loc;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  ಆದರೆ (setlocale (LC_COLLATE, locale) == ಖಾಲಿ)
    {
      ಬರೆ ("cannot set locale \"%s\"\n", locale);
      ಹಿಂತಿರುಗಿ 1;
    }
  bufsize = strxfrm (ಖಾಲಿ, string, 0) + 1;
  buf = ಸ್ಮರಣೆ_ಕೊಡು (bufsize);
  ಆದರೆ (buf == ಖಾಲಿ)
    {
      ಬರೆ ("cannot allocate %zd bytes\n", bufsize);
      ಹಿಂತಿರುಗಿ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf);
  ಆದರೆ (r != l)
    {
       ಬರೆ ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ಫಲಿತಾಂಶ = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ಖಾಲಿ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf);
  ಆದರೆ (r != l)
    {
       ಬರೆ ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ಫಲಿತಾಂಶ = 1;
    }

  freelocale (loc);

  ಬಿಡುಗಡೆ (buf);

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}


ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  ಫಲಿತಾಂಶ |= test ("C");
  ಫಲಿತಾಂಶ |= test ("en_US.ISO-8859-1");
  ಫಲಿತಾಂಶ |= test ("de_DE.UTF-8");

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
