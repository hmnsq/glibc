#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <libc-diag.h>

पूर्णांक
main (शून्य)
{
  स्थिरांक अक्षर *a = "abc";
  स्थिरांक अक्षर *b = a;

  DIAG_ढकला_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_काढा_NEEDS_COMMENT;
  जर (b != a + 1)
    परत 1;

  परत 0;
}
