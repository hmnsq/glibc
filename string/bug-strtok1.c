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

  माला_दो ("test strtok");
  cp = strdupa (str);
  म_लिखो ("cp = %p, len = %zu\n", cp, म_माप (cp));
  token = म_मोहर (cp, "ab");
  result |= token == रिक्त || म_भेद (token, "x");
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", result);
  token = म_मोहर(0, "ab");
  result |= token != रिक्त;
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", result);
  token = म_मोहर(0, "a");
  result |= token != रिक्त;
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", result);

  माला_दो ("test strtok_r");
  cp = strdupa (str);
  माप_प्रकार len = म_माप (cp);
  म_लिखो ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  result |= token == रिक्त || म_भेद (token, "x");
  म_लिखो ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "ab", &l);
  result |= token != रिक्त || l != cp + len;
  म_लिखो ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, result);
  token = strtok_r(0, "a", &l);
  result |= token != रिक्त || l != cp + len;
  म_लिखो ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, result);

  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
