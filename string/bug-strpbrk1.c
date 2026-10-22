#अघोषित __USE_STRING_INLINES
#घोषणा __USE_STRING_INLINES
#समावेश <string.h>
#समावेश <stdlib.h>
#समावेश <stdio.h>
#समावेश <libc-diag.h>

पूर्णांक
मुख्य (व्योम)
{
  स्थिर अक्षर *a = "abc";
  स्थिर अक्षर *b = a;

  DIAG_धकेलो_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_निकालो_NEEDS_COMMENT;
  अगर (b != a + 1)
    वापस 1;

  वापस 0;
}
