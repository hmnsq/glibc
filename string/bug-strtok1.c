/* See BZ #2126.  */
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdio.h>

પૂર્ણાંક
do_test (શૂન્ય)
{
  અચલ અક્ષર str[] = "axaaba";
  અક્ષર *token;
  અક્ષર *cp;
  અક્ષર *l;
  પૂર્ણાંક result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == ખાલી || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != ખાલી;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != ખાલી;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == ખાલી || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != ખાલી || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != ખાલી || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  પાછા result;
}

#અન્તર્ભાવ <support/test-driver.c>
