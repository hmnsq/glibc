/* See BZ #2126.  */
#అన్తర్భావ <string.h>
#అన్తర్భావ <stdio.h>

పూర్ణాంకం
do_test (శూన్య)
{
  స్థిరరాశి అక్షరం str[] = "axaaba";
  అక్షరం *token;
  అక్షరం *cp;
  అక్షరం *l;
  పూర్ణాంకం ఫలితం = 0;

  puts ("test strtok");
  cp = strdupa (str);
  రాయి ("cp = %p, len = %zu\n", cp, అక్షరశ్రేణి_పొడవు (cp));
  token = strtok (cp, "ab");
  ఫలితం |= token == ఖాళీ || strcmp (token, "x");
  రాయి ("token: %s (%d)\n", token ? token : "NULL", ఫలితం);
  token = strtok(0, "ab");
  ఫలితం |= token != ఖాళీ;
  రాయి ("token: %s (%d)\n", token ? token : "NULL", ఫలితం);
  token = strtok(0, "a");
  ఫలితం |= token != ఖాళీ;
  రాయి ("token: %s (%d)\n", token ? token : "NULL", ఫలితం);

  puts ("test strtok_r");
  cp = strdupa (str);
  size_t len = అక్షరశ్రేణి_పొడవు (cp);
  రాయి ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  ఫలితం |= token == ఖాళీ || strcmp (token, "x");
  రాయి ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ఫలితం);
  token = strtok_r(0, "ab", &l);
  ఫలితం |= token != ఖాళీ || l != cp + len;
  రాయి ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, ఫలితం);
  token = strtok_r(0, "a", &l);
  ఫలితం |= token != ఖాళీ || l != cp + len;
  రాయి ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, ఫలితం);

  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
