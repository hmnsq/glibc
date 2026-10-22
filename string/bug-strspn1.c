#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ضمن <string.h>
#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <libc-diag.h>

صحيح
main (فراغ)
{
  ثابت حرف *a = "abc";
  ثابت حرف *b = a;

  DIAG_PUSH_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_POP_NEEDS_COMMENT;
  𐤀𐤌 (b != a + 1)
    أرجع 1;

  أرجع 0;
}
