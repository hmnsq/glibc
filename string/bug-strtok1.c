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
  पूर्णाङ्क परिणाम = 0;

  पङ्क्तिं_लिख ("test strtok");
  cp = strdupa (str);
  प्रारूप_लिख ("cp = %p, len = %zu\n", cp, वाक्यदैर्घ्यम् (cp));
  token = strtok (cp, "ab");
  परिणाम |= token == रिक्त || वाक्यं_तुलय (token, "x");
  प्रारूप_लिख ("token: %s (%d)\n", token ? token : "NULL", परिणाम);
  token = strtok(0, "ab");
  परिणाम |= token != रिक्त;
  प्रारूप_लिख ("token: %s (%d)\n", token ? token : "NULL", परिणाम);
  token = strtok(0, "a");
  परिणाम |= token != रिक्त;
  प्रारूप_लिख ("token: %s (%d)\n", token ? token : "NULL", परिणाम);

  पङ्क्तिं_लिख ("test strtok_r");
  cp = strdupa (str);
  size_t len = वाक्यदैर्घ्यम् (cp);
  प्रारूप_लिख ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  परिणाम |= token == रिक्त || वाक्यं_तुलय (token, "x");
  प्रारूप_लिख ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, परिणाम);
  token = strtok_r(0, "ab", &l);
  परिणाम |= token != रिक्त || l != cp + len;
  प्रारूप_लिख ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, परिणाम);
  token = strtok_r(0, "a", &l);
  परिणाम |= token != रिक्त || l != cp + len;
  प्रारूप_लिख ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, परिणाम);

  प्रत्यागम परिणाम;
}

#अन्तर्भाव <support/test-driver.c>
