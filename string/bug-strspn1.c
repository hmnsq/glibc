#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <libc-diag.h>

પૂર્ણાંક
મુખ્ય (શૂન્ય)
{
  અચલ અક્ષર *a = "abc";
  અચલ અક્ષર *b = a;

  DIAG_ધકેલો_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_કાઢો_NEEDS_COMMENT;
  જો (b != a + 1)
    પાછા 1;

  પાછા 0;
}
