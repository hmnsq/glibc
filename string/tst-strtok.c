/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

முழு
do_test (வெறுமை)
{
  எழுத்து buf[1] = { 0 };
  முழு result = 0;

  எனில் (strtok (buf, " ") != வெற்று)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  இல்லையெனில் எனில் (strtok (வெற்று, " ") != வெற்று)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  திரும்பு result;
}

#அந்தர்பாவ <support/test-driver.c>
