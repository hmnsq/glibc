/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਅੱਖਰ buf[1] = { 0 };
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  ਜੇ (strtok (buf, " ") != ਨਿਰਾ)
    {
      puts ("first strtok call did not return NULL");
      ਨਤੀਜਾ = 1;
    }
  ਨਹੀਂਤਾਂ ਜੇ (strtok (ਨਿਰਾ, " ") != ਨਿਰਾ)
    {
      puts ("second strtok call did not return NULL");
      ਨਤੀਜਾ = 1;
    }

  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
