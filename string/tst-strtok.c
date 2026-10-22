/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  അക്ഷരം buf[1] = { 0 };
  പൂർണ്ണസംഖ്യ result = 0;

  എങ്കിൽ (strtok (buf, " ") != ശൂന്യ)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (strtok (ശൂന്യ, " ") != ശൂന്യ)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  തിരികെ result;
}

#അന്തര്ഭാവ <support/test-driver.c>
