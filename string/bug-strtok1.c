/* See BZ #2126.  */
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ str[] = "axaaba";
  ವರ್ಣ *token;
  ವರ್ಣ *cp;
  ವರ್ಣ *l;
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == ರಿಕ್ತ || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != ರಿಕ್ತ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != ರಿಕ್ತ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == ರಿಕ್ತ || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != ರಿಕ್ತ || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != ರಿಕ್ತ || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  ಪ್ರತ್ಯಾಗಮ result;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
