/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

પૂર્ણાંક
do_test (શૂન્ય)
{
  અક્ષર buf[1] = { 0 };
  પૂર્ણાંક result = 0;

  જો (strtok (buf, " ") != ખાલી)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  નહીંતર જો (strtok (ખાલી, " ") != ખાલી)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  પાછા result;
}

#અન્તર્ભાવ <support/test-driver.c>
