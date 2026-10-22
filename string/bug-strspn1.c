#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <libc-diag.h>

पूर्णाङ्क
main (शून्य)
{
  अचर वर्ण *a = "abc";
  अचर वर्ण *b = a;

  DIAG_थप_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  म_अखोज (b++, "");
  DIAG_झिक_NEEDS_COMMENT;
  यदि (b != a + 1)
    फर्काऊ 1;

  फर्काऊ 0;
}
