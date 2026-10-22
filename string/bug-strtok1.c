/* See BZ #2126.  */
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ str[] = "axaaba";
  ಅಕ್ಷರ *token;
  ಅಕ್ಷರ *cp;
  ಅಕ್ಷರ *l;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  puts ("test strtok");
  cp = strdupa (str);
  ಬರೆ ("cp = %p, len = %zu\n", cp, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (cp));
  token = strtok (cp, "ab");
  ಫಲಿತಾಂಶ |= token == ಖಾಲಿ || strcmp (token, "x");
  ಬರೆ ("token: %s (%d)\n", token ? token : "NULL", ಫಲಿತಾಂಶ);
  token = strtok(0, "ab");
  ಫಲಿತಾಂಶ |= token != ಖಾಲಿ;
  ಬರೆ ("token: %s (%d)\n", token ? token : "NULL", ಫಲಿತಾಂಶ);
  token = strtok(0, "a");
  ಫಲಿತಾಂಶ |= token != ಖಾಲಿ;
  ಬರೆ ("token: %s (%d)\n", token ? token : "NULL", ಫಲಿತಾಂಶ);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (cp);
  ಬರೆ ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  ಫಲಿತಾಂಶ |= token == ಖಾಲಿ || strcmp (token, "x");
  ಬರೆ ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ಫಲಿತಾಂಶ);
  token = strtok_r(0, "ab", &l);
  ಫಲಿತಾಂಶ |= token != ಖಾಲಿ || l != cp + len;
  ಬರೆ ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ಫಲಿತಾಂಶ);
  token = strtok_r(0, "a", &l);
  ಫಲಿತಾಂಶ |= token != ಖಾಲಿ || l != cp + len;
  ಬರೆ ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, ಫಲಿತಾಂಶ);

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
