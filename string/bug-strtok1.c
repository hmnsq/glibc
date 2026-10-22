/* See BZ #2126.  */
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <stdio.h>

পূর্ণাঙ্ক
do_test (শূন্য)
{
  ধ্রুৱ ৱর্ণ str[] = "axaaba";
  ৱর্ণ *token;
  ৱর্ণ *cp;
  ৱর্ণ *l;
  পূর্ণাঙ্ক result = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  result |= token == রিক্ত || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "ab");
  result |= token != রিক্ত;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);
  token = strtok(0, "a");
  result |= token != রিক্ত;
  printf ("token: %s (%d)\n", token ? token : "NULL", result);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == রিক্ত || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != রিক্ত || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != রিক্ত || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  ঘূৰাই result;
}

#অন্তর্ভাৱ <support/test-driver.c>
