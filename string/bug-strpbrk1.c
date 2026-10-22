#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

ಪೂರ್ಣಾಙ್ಕ
main (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ *a = "abc";
  ಧ್ರುವ ವರ್ಣ *b = a;

  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  ಯದಿ (b != a + 1)
    ಪ್ರತ್ಯಾಗಮ 1;

  ಪ್ರತ್ಯಾಗಮ 0;
}
