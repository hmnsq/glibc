#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <libc-diag.h>

পূর্ণাঙ্ক
main (শূন্য)
{
  ধ্রুৱ ৱর্ণ *a = "abc";
  ধ্রুৱ ৱর্ণ *b = a;

  DIAG_ঠেলো_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  যদি (b != a + 1)
    ঘূৰাই 1;

  ঘূৰাই 0;
}
