/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_هێڵ_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف هێڵ[MAX_هێڵ_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  ژماردن = 0;
  صحيح  i, n;

  طالما (ژماردن < MAX_STRINGS && fgets (هێڵ, MAX_هێڵ_SIZE, stdin) != عدم)
    {
      n = strlen (هێڵ) - 1;

      إذا (هێڵ[n] == '\n')
        هێڵ[n] = '\0';

      str[ژماردن] = strdup (هێڵ);

      إذا (str[ژماردن] == عدم)
        exit (EXIT_FAILURE);

      ++ژماردن;
    }

  qsort (str, ژماردن, حجم (حرف *), compare);

  لكل (i = 0; i < ژماردن; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
