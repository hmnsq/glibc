#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <libc-diag.h>

পূর্ণসংখ্যা
প্রধান (শূন্য)
{
  ধ্রুবক অক্ষর *a = "abc";
  ধ্রুবক অক্ষর *b = a;

  DIAG_ঠেলো_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_বের_করো_NEEDS_COMMENT;
  যদি (b != a + 1)
    ফেরত 1;

  ফেরত 0;
}
