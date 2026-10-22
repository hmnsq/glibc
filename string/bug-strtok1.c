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
  صحيح نتیجه = 0;

  puts ("test strtok");
  cp = strdupa (str);
  چاپ_کن ("cp = %p, len = %zu\n", cp, طول_رشته (cp));
  token = strtok (cp, "ab");
  نتیجه |= token == عدم || strcmp (token, "x");
  چاپ_کن ("token: %s (%d)\n", token ? token : "NULL", نتیجه);
  token = strtok(0, "ab");
  نتیجه |= token != عدم;
  چاپ_کن ("token: %s (%d)\n", token ? token : "NULL", نتیجه);
  token = strtok(0, "a");
  نتیجه |= token != عدم;
  چاپ_کن ("token: %s (%d)\n", token ? token : "NULL", نتیجه);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = طول_رشته (cp);
  چاپ_کن ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  نتیجه |= token == عدم || strcmp (token, "x");
  چاپ_کن ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتیجه);
  token = strtok_r(0, "ab", &l);
  نتیجه |= token != عدم || l != cp + len;
  چاپ_کن ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتیجه);
  token = strtok_r(0, "a", &l);
  نتیجه |= token != عدم || l != cp + len;
  چاپ_کن ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, نتیجه);

  أرجع نتیجه;
}

#ضمن <support/test-driver.c>
