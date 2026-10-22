/* See BZ #2126.  */
#समावेश <string.h>
#समावेश <stdio.h>

पूर्णांक
do_test (व्योम)
{
  स्थिर अक्षर str[] = "axaaba";
  अक्षर *token;
  अक्षर *cp;
  अक्षर *l;
  पूर्णांक परिणाम = 0;

  माला_दो ("test strtok");
  cp = strdupa (str);
  म_लिखो ("cp = %p, len = %zu\n", cp, म_माप (cp));
  token = म_मोहर (cp, "ab");
  परिणाम |= token == शून्य || म_भेद (token, "x");
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", परिणाम);
  token = म_मोहर(0, "ab");
  परिणाम |= token != शून्य;
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", परिणाम);
  token = म_मोहर(0, "a");
  परिणाम |= token != शून्य;
  म_लिखो ("token: %s (%d)\n", token ? token : "NULL", परिणाम);

  माला_दो ("test strtok_r");
  cp = strdupa (str);
  माप_प्रकार len = म_माप (cp);
  म_लिखो ("cp = %p, len = %zu\n", cp, len);
  token = strtok_r (cp, "ab", &l);
  परिणाम |= token == शून्य || म_भेद (token, "x");
  म_लिखो ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, परिणाम);
  token = strtok_r(0, "ab", &l);
  परिणाम |= token != शून्य || l != cp + len;
  म_लिखो ("token: %s, next = %p (%d)\n", token ? token : "NULL", l, परिणाम);
  token = strtok_r(0, "a", &l);
  परिणाम |= token != शून्य || l != cp + len;
  म_लिखो ("token: %s,  next = %p (%d)\n", token ? token : "NULL", l, परिणाम);

  वापस परिणाम;
}

#समावेश <support/test-driver.c>
