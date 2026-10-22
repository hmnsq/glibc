/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#تعریف_کړه  MAX_مزي_ګانې      256
#تعریف_کړه  MAX_کرښه_اندازه    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف کرښه[MAX_کرښه_اندازه + 1];
  حرف *str[MAX_مزي_ګانې];
  صحيح  شمېر = 0;
  صحيح  i, n;

  طالما (شمېر < MAX_مزي_ګانې && fgets (کرښه, MAX_کرښه_اندازه, stdin) != عدم)
    {
      n = مزي_اوږدوالی (کرښه) - 1;

      إذا (کرښه[n] == '\n')
        کرښه[n] = '\0';

      str[شمېر] = strdup (کرښه);

      إذا (str[شمېر] == عدم)
        وتل (EXIT_FAILURE);

      ++شمېر;
    }

  qsort (str, شمېر, حجم (حرف *), compare);

  لكل (i = 0; i < شمېر; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
