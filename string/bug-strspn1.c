#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __USE_STRING_INLINES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __USE_STRING_INLINES
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

ਪੂਰਨ
ਮੁੱਖ (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ *a = "abc";
  ਅਚਲ ਅੱਖਰ *b = a;

  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strspn is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strspn (b++, "");
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  ਜੇ (b != a + 1)
    ਵਾਪਸ 1;

  ਵਾਪਸ 0;
}
