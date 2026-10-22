/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  החזר strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف line[MAX_LINE_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  count = 0;
  صحيح  i, n;

  כלעוד (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != عدم)
    {
      n = strlen (line) - 1;

      אם (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      אם (str[count] == عدم)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, حجم (حرف *), compare);

  עבור (i = 0; i < count; ++i)
    puts (str[i]);

  החזר EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
