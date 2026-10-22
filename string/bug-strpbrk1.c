#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
ମୁଖ୍ୟ (ଶୂନ୍ୟ)
{
  ଅଚଳ ଅକ୍ଷର *a = "abc";
  ଅଚଳ ଅକ୍ଷର *b = a;

  DIAG_ଠେଲ_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_କାଢ଼_NEEDS_COMMENT;
  ଯଦି (b != a + 1)
    ଫେରନ୍ତୁ 1;

  ଫେରନ୍ତୁ 0;
}
