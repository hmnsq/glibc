#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <libc-diag.h>

പൂർണ്ണസംഖ്യ
പ്രധാന (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം *a = "abc";
  സ്ഥിരം അക്ഷരം *b = a;

  DIAG_തള്ളുക_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  എങ്കിൽ (b != a + 1)
    തിരികെ 1;

  തിരികെ 0;
}
