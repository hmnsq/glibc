/* See BZ #2126.  */
#include <string.h>
#include <stdio.h>

puur_naa_nka
do_test (void)
{
  const var_na str[] = "axaaba";
  var_na *token;
  var_na *cp;
  var_na *l;
  puur_naa_nka result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == NULL || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != NULL;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != NULL;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == NULL || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != NULL || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != NULL || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  ပွၵ်ႈ result;
}

#include <support/test-driver.c>
