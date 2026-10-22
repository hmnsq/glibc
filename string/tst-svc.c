/* Test for strverscmp() */

#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>

#define  MAX_STRINGS      256
#define  MAX_সাৰি_SIZE    32

স্থির পূর্ণাঙ্ক
compare (ধ্রুৱ শূন্য *p1, ধ্রুৱ শূন্য *p2)
{
  ঘূৰাই strverscmp (*((ৱর্ণ **) p1), *((ৱর্ণ **) p2));
}

পূর্ণাঙ্ক
do_test (শূন্য)
{
  ৱর্ণ সাৰি[MAX_সাৰি_SIZE + 1];
  ৱর্ণ *str[MAX_STRINGS];
  পূর্ণাঙ্ক  গুনতি = 0;
  পূর্ণাঙ্ক  i, n;

  যেতিয়ালৈ (গুনতি < MAX_STRINGS && fgets (সাৰি, MAX_সাৰি_SIZE, stdin) != রিক্ত)
    {
      n = strlen (সাৰি) - 1;

      যদি (সাৰি[n] == '\n')
        সাৰি[n] = '\0';

      str[গুনতি] = strdup (সাৰি);

      যদি (str[গুনতি] == রিক্ত)
        exit (EXIT_FAILURE);

      ++গুনতি;
    }

  qsort (str, গুনতি, পরিমাণ (ৱর্ণ *), compare);

  বাবে (i = 0; i < গুনতি; ++i)
    puts (str[i]);

  ঘূৰাই EXIT_SUCCESS;
}

#অন্তর্ভাৱ <support/test-driver.c>
