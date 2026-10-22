/* See BZ #2126.  */
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <stdio.h>

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം str[] = "axaaba";
  അക്ഷരം *token;
  അക്ഷരം *cp;
  അക്ഷരം *l;
  പൂർണ്ണസംഖ്യ result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == ശൂന്യ || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != ശൂന്യ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != ശൂന്യ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == ശൂന്യ || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != ശൂന്യ || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != ശൂന്യ || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  തിരികെ result;
}

#അന്തര്ഭാവ <support/test-driver.c>
