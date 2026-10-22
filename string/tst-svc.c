/* Test for strverscmp() */

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#define  MAX_STRINGS      256
#define  MAX_ଧାଡ଼ି_SIZE    32

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
compare (ଅଚଳ ଶୂନ୍ୟ *p1, ଅଚଳ ଶୂନ୍ୟ *p2)
{
  ଫେରନ୍ତୁ strverscmp (*((ଅକ୍ଷର **) p1), *((ଅକ୍ଷର **) p2));
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ଅକ୍ଷର ଧାଡ଼ି[MAX_ଧାଡ଼ି_SIZE + 1];
  ଅକ୍ଷର *str[MAX_STRINGS];
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା  ଗଣନା_2 = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା  i, n;

  ଯେତେବେଳେ (ଗଣନା_2 < MAX_STRINGS && fgets (ଧାଡ଼ି, MAX_ଧାଡ଼ି_SIZE, stdin) != ଖାଲି)
    {
      n = strlen (ଧାଡ଼ି) - 1;

      ଯଦି (ଧାଡ଼ି[n] == '\n')
        ଧାଡ଼ି[n] = '\0';

      str[ଗଣନା_2] = strdup (ଧାଡ଼ି);

      ଯଦି (str[ଗଣନା_2] == ଖାଲି)
        exit (EXIT_FAILURE);

      ++ଗଣନା_2;
    }

  qsort (str, ଗଣନା_2, ଆକାର (ଅକ୍ଷର *), compare);

  ପାଇଁ (i = 0; i < ଗଣନା_2; ++i)
    puts (str[i]);

  ଫେରନ୍ତୁ EXIT_SUCCESS;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
