/* Test for strverscmp() */

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#define  MAX_STRINGS      256
#define  MAX_সারি_SIZE    32

স্থির পূর্ণাঙ্ক
compare (ধ্রুব শূন্য *p1, ধ্রুব শূন্য *p2)
{
  প্রত্যাগম strverscmp (*((বর্ণ **) p1), *((বর্ণ **) p2));
}

পূর্ণাঙ্ক
do_test (শূন্য)
{
  বর্ণ সারি[MAX_সারি_SIZE + 1];
  বর্ণ *str[MAX_STRINGS];
  পূর্ণাঙ্ক  গুনতি = 0;
  পূর্ণাঙ্ক  i, n;

  যাবত্ (গুনতি < MAX_STRINGS && fgets (সারি, MAX_সারি_SIZE, stdin) != রিক্ত)
    {
      n = strlen (সারি) - 1;

      যদি (সারি[n] == '\n')
        সারি[n] = '\0';

      str[গুনতি] = strdup (সারি);

      যদি (str[গুনতি] == রিক্ত)
        exit (EXIT_FAILURE);

      ++গুনতি;
    }

  qsort (str, গুনতি, পরিমাণ (বর্ণ *), compare);

  প্রতি (i = 0; i < গুনতি; ++i)
    puts (str[i]);

  প্রত্যাগম EXIT_SUCCESS;
}

#অন্তর্ভাব <support/test-driver.c>
