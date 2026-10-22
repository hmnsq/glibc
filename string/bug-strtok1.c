/* See BZ #2126.  */
#ضمن <string.h>
#ضمن <stdio.h>

صحيح
do_test (فراغ)
{
  ثابت حرف str[] = "axaaba";
  حرف *token;
  حرف *cp;
  حرف *l;
  صحيح نتيجو = 0;

  puts ("test strtok");
  cp = strdupa (str);
  لکو ("cp = %p, len = %zu\n", cp, لڙي_ڊيگهه (cp));
  token = strtok (cp, "ab");
  نتيجو |= token == عدم || strcmp (token, "x");
  لکو ("token: %s (%d)\n", token ? token : "NULL", نتيجو);
  token = strtok(0, "ab");
  نتيجو |= token != عدم;
  لکو ("token: %s (%d)\n", token ? token : "NULL", نتيجو);
  token = strtok(0, "a");
  نتيجو |= token != عدم;
  لکو ("token: %s (%d)\n", token ? token : "NULL", نتيجو);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = لڙي_ڊيگهه (cp);
  لکو ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  نتيجو |= token == عدم || strcmp (token, "x");
  لکو ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتيجو);
  token = strtok_r(0, "ab", &l);
  نتيجو |= token != عدم || l != cp + len;
  لکو ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتيجو);
  token = strtok_r(0, "a", &l);
  نتيجو |= token != عدم || l != cp + len;
  لکو ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, نتيجو);

  أرجع نتيجو;
}

#ضمن <support/test-driver.c>
