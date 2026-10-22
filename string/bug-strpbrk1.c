#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libc-diag.h>

puur_naa_nka
main (void)
{
  const var_na *a = "abc";
  const var_na *b = a;

  DIAG_PUSH_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_POP_NEEDS_COMMENT;
  ပေႃး (b != a + 1)
    ပွၵ်ႈ 1;

  ပွၵ်ႈ 0;
}
