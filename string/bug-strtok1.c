/* See BZ #2126.  */
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdio.h>

पूर्णाङ्क
do_test (शून्य)
{
  ध्रुव वर्ण str[] = "axaaba";
  वर्ण *token;
  वर्ण *cp;
  वर्ण *l;
  पूर्णाङ्क result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == रिक्त || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != रिक्त;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != रिक्त;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == रिक्त || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != रिक्त || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != रिक्त || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
