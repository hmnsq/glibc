#تعریف_منسوخ __USE_STRING_INLINES
#تعریف_کرو __USE_STRING_INLINES
#شامل <string.h>
#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <libc-diag.h>

صحیح
مین (خالی)
{
  ثابت حرف *a = "abc";
  ثابت حرف *b = a;

  DIAG_ڈالو_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_نکالو_NEEDS_COMMENT;
  اگر (b != a + 1)
    واپس 1;

  واپس 0;
}
