/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#وصف_ڪريو  MAX_لڙيون      256
#وصف_ڪريو  MAX_سٽ_سائيز    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف سٽ[MAX_سٽ_سائيز + 1];
  حرف *str[MAX_لڙيون];
  صحيح  ڳڻپ = 0;
  صحيح  i, n;

  طالما (ڳڻپ < MAX_لڙيون && fgets (سٽ, MAX_سٽ_سائيز, stdin) != عدم)
    {
      n = لڙي_ڊيگهه (سٽ) - 1;

      إذا (سٽ[n] == '\n')
        سٽ[n] = '\0';

      str[ڳڻپ] = strdup (سٽ);

      إذا (str[ڳڻپ] == عدم)
        ٻاهر_نڪرو (EXIT_FAILURE);

      ++ڳڻپ;
    }

  qsort (str, ڳڻپ, حجم (حرف *), compare);

  لكل (i = 0; i < ڳڻپ; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
