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
  صحيح پایله = 0;

  puts ("test strtok");
  cp = strdupa (str);
  چاپ_کړه ("cp = %p, len = %zu\n", cp, مزي_اوږدوالی (cp));
  token = strtok (cp, "ab");
  پایله |= token == عدم || strcmp (token, "x");
  چاپ_کړه ("token: %s (%d)\n", token ? token : "NULL", پایله);
  token = strtok(0, "ab");
  پایله |= token != عدم;
  چاپ_کړه ("token: %s (%d)\n", token ? token : "NULL", پایله);
  token = strtok(0, "a");
  پایله |= token != عدم;
  چاپ_کړه ("token: %s (%d)\n", token ? token : "NULL", پایله);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = مزي_اوږدوالی (cp);
  چاپ_کړه ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  پایله |= token == عدم || strcmp (token, "x");
  چاپ_کړه ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, پایله);
  token = strtok_r(0, "ab", &l);
  پایله |= token != عدم || l != cp + len;
  چاپ_کړه ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, پایله);
  token = strtok_r(0, "a", &l);
  پایله |= token != عدم || l != cp + len;
  چاپ_کړه ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, پایله);

  أرجع پایله;
}

#ضمن <support/test-driver.c>
