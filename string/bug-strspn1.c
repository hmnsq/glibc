#تعریف_رد __USE_STRING_INLINES
#تعریف_کرو __USE_STRING_INLINES
#ضمن <string.h>
#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <libc-diag.h>

صحيح
مکھ (فراغ)
{
  ثابت حرف *a = "abc";
  ثابت حرف *b = a;

  DIAG_ڈالو_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_نکالو_NEEDS_COMMENT;
  إذا (b != a + 1)
    أرجع 1;

  أرجع 0;
}
