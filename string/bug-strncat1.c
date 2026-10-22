#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#അന്തര്ഭാവ <sys/cdefs.h>
#അന്തര്ഭാവ <libc-diag.h>
#എങ്കിൽ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

അക്ഷരം d[3] = "\0\1\2";

പൂർണ്ണസംഖ്യ
പ്രധാന (ശൂന്യം)
{
  DIAG_തള്ളുക_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  എങ്കിൽ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  എങ്കിൽ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  എങ്കിൽ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  തിരികെ 0;
}
