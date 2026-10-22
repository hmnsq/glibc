/* See BZ #2126.  */
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <stdio.h>

পূর্ণসংখ্যা
do_test (শূন্য)
{
  ধ্রুবক অক্ষর str[] = "axaaba";
  অক্ষর *token;
  অক্ষর *cp;
  অক্ষর *l;
  পূর্ণসংখ্যা ফলাফল = 0;

  puts ("test strtok");
  cp = strdupa (str);
  printf ("cp = %p, len = %zu\n", cp, strlen (cp));
  token = strtok (cp, "ab");
  ফলাফল |= token == ফাঁকা || strcmp (token, "x");
  printf ("token: %s (%d)\n", token ? token : "NULL", ফলাফল);
  token = strtok(0, "ab");
  ফলাফল |= token != ফাঁকা;
  printf ("token: %s (%d)\n", token ? token : "NULL", ফলাফল);
  token = strtok(0, "a");
  ফলাফল |= token != ফাঁকা;
  printf ("token: %s (%d)\n", token ? token : "NULL", ফলাফল);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = strlen (cp);
  printf ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  ফলাফল |= token == ফাঁকা || strcmp (token, "x");
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ফলাফল);
  token = strtok_r(0, "ab", &l);
  ফলাফল |= token != ফাঁকা || l != cp + len;
  printf ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ফলাফল);
  token = strtok_r(0, "a", &l);
  ফলাফল |= token != ফাঁকা || l != cp + len;
  printf ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, ফলাফল);

  ফেরত ফলাফল;
}

#অন্তর্ভাব <support/test-driver.c>
