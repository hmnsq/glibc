#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __USE_STRING_INLINES
#ವ್ಯಾಖ್ಯಾನಿಸು __USE_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

ಪೂರ್ಣಾಂಕ
ಮುಖ್ಯ (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a = "abc";
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *b = a;

  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  ಆದರೆ (b != a + 1)
    ಹಿಂತಿರುಗಿ 1;

  ಹಿಂತಿರುಗಿ 0;
}
