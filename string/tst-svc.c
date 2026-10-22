/* Test for strverscmp() */

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#define  MAX_STRINGS      256
#define  MAX_সারি_আকার    32

স্থির পূর্ণসংখ্যা
compare (ধ্রুবক শূন্য *p1, ধ্রুবক শূন্য *p2)
{
  ফেরত strverscmp (*((অক্ষর **) p1), *((অক্ষর **) p2));
}

পূর্ণসংখ্যা
do_test (শূন্য)
{
  অক্ষর সারি[MAX_সারি_আকার + 1];
  অক্ষর *str[MAX_STRINGS];
  পূর্ণসংখ্যা  গুনতি = 0;
  পূর্ণসংখ্যা  i, n;

  যখন (গুনতি < MAX_STRINGS && fgets (সারি, MAX_সারি_আকার, stdin) != ফাঁকা)
    {
      n = strlen (সারি) - 1;

      যদি (সারি[n] == '\n')
        সারি[n] = '\0';

      str[গুনতি] = strdup (সারি);

      যদি (str[গুনতি] == ফাঁকা)
        exit (EXIT_FAILURE);

      ++গুনতি;
    }

  qsort (str, গুনতি, আকার (অক্ষর *), compare);

  জন্য (i = 0; i < গুনতি; ++i)
    puts (str[i]);

  ফেরত EXIT_SUCCESS;
}

#অন্তর্ভাব <support/test-driver.c>
