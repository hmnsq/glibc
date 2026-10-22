#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __USE_STRING_INLINES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __USE_STRING_INLINES
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/cdefs.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>
#ਜੇ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਅੱਖਰ d[3] = "\0\1\2";

ਪੂਰਨ
ਮੁੱਖ (ਖਾਲੀ)
{
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  ਜੇ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      ਬਾਹਰ_ਨਿਕਲੋ (1);
    }
  ਜੇ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      ਬਾਹਰ_ਨਿਕਲੋ (1);
    }
  ਜੇ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      ਬਾਹਰ_ਨਿਕਲੋ (1);
    }

  ਵਾਪਸ 0;
}
