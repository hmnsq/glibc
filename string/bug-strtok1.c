/* See BZ #2126.  */
#شامل <string.h>
#شامل <stdio.h>

صحیح
do_test (خالی)
{
  ثابت حرف str[] = "axaaba";
  حرف *token;
  حرف *cp;
  حرف *l;
  صحیح نتیجہ = 0;

  puts ("test strtok");
  cp = strdupa (str);
  لکھو ("cp = %p, len = %zu\n", cp, لڑی_لمبائی (cp));
  token = strtok (cp, "ab");
  نتیجہ |= token == تہی || strcmp (token, "x");
  لکھو ("token: %s (%d)\n", token ? token : "NULL", نتیجہ);
  token = strtok(0, "ab");
  نتیجہ |= token != تہی;
  لکھو ("token: %s (%d)\n", token ? token : "NULL", نتیجہ);
  token = strtok(0, "a");
  نتیجہ |= token != تہی;
  لکھو ("token: %s (%d)\n", token ? token : "NULL", نتیجہ);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = لڑی_لمبائی (cp);
  لکھو ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  نتیجہ |= token == تہی || strcmp (token, "x");
  لکھو ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتیجہ);
  token = strtok_r(0, "ab", &l);
  نتیجہ |= token != تہی || l != cp + len;
  لکھو ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, نتیجہ);
  token = strtok_r(0, "a", &l);
  نتیجہ |= token != تہی || l != cp + len;
  لکھو ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, نتیجہ);

  واپس نتیجہ;
}

#شامل <support/test-driver.c>
