/* Test for strverscmp() */

#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#define  MAX_STRINGS      256
#define  MAX_வரி_SIZE    32

நிலையான முழு
compare (மாறிலி வெறுமை *p1, மாறிலி வெறுமை *p2)
{
  திரும்பு strverscmp (*((எழுத்து **) p1), *((எழுத்து **) p2));
}

முழு
do_test (வெறுமை)
{
  எழுத்து வரி[MAX_வரி_SIZE + 1];
  எழுத்து *str[MAX_STRINGS];
  முழு  மொத்தம் = 0;
  முழு  i, n;

  போது (மொத்தம் < MAX_STRINGS && fgets (வரி, MAX_வரி_SIZE, stdin) != வெற்று)
    {
      n = strlen (வரி) - 1;

      எனில் (வரி[n] == '\n')
        வரி[n] = '\0';

      str[மொத்தம்] = strdup (வரி);

      எனில் (str[மொத்தம்] == வெற்று)
        exit (EXIT_FAILURE);

      ++மொத்தம்;
    }

  qsort (str, மொத்தம், அளவு (எழுத்து *), compare);

  க்கு (i = 0; i < மொத்தம்; ++i)
    puts (str[i]);

  திரும்பு EXIT_SUCCESS;
}

#அந்தர்பாவ <support/test-driver.c>
