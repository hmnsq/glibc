/* See BZ #2126.  */
#شامل <string.h>
#شامل <stdio.h>

صحیح
do_test (تهی)
{
  ثابت نویسه str[] = "axaaba";
  نویسه *token;
  نویسه *cp;
  نویسه *l;
  صحیح result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == پوچ || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != پوچ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != پوچ;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == پوچ || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != پوچ || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != پوچ || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  بازگشت result;
}

#شامل <support/test-driver.c>
