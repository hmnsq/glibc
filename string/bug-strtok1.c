/* See BZ #2126.  */
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ str[] = "axaaba";
  ਅੱਖਰ *token;
  ਅੱਖਰ *cp;
  ਅੱਖਰ *l;
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  puts ("test strtok");
  cp = strdupa (str);
  ਲਿਖੋ ("cp = %p, len = %zu\n", cp, ਲੜੀ_ਲੰਬਾਈ (cp));
  token = strtok (cp, "ab");
  ਨਤੀਜਾ |= token == ਨਿਰਾ || strcmp (token, "x");
  ਲਿਖੋ ("token: %s (%d)\n", token ? token : "NULL", ਨਤੀਜਾ);
  token = strtok(0, "ab");
  ਨਤੀਜਾ |= token != ਨਿਰਾ;
  ਲਿਖੋ ("token: %s (%d)\n", token ? token : "NULL", ਨਤੀਜਾ);
  token = strtok(0, "a");
  ਨਤੀਜਾ |= token != ਨਿਰਾ;
  ਲਿਖੋ ("token: %s (%d)\n", token ? token : "NULL", ਨਤੀਜਾ);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = ਲੜੀ_ਲੰਬਾਈ (cp);
  ਲਿਖੋ ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  ਨਤੀਜਾ |= token == ਨਿਰਾ || strcmp (token, "x");
  ਲਿਖੋ ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ਨਤੀਜਾ);
  token = strtok_r(0, "ab", &l);
  ਨਤੀਜਾ |= token != ਨਿਰਾ || l != cp + len;
  ਲਿਖੋ ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ਨਤੀਜਾ);
  token = strtok_r(0, "a", &l);
  ਨਤੀਜਾ |= token != ਨਿਰਾ || l != cp + len;
  ਲਿਖੋ ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, ਨਤੀਜਾ);

  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
