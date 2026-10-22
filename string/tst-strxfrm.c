/* Based on a test case by Paul Eggert.  */
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>


ਅੱਖਰ ਅਚਲ string[] = "";


ਸਥਿਰ ਪੂਰਨ
test (ਅਚਲ ਅੱਖਰ *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  ਅੱਖਰ *buf;
  locale_t loc;
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  ਜੇ (setlocale (LC_COLLATE, locale) == ਨਿਰਾ)
    {
      ਲਿਖੋ ("cannot set locale \"%s\"\n", locale);
      ਵਾਪਸ 1;
    }
  bufsize = strxfrm (ਨਿਰਾ, string, 0) + 1;
  buf = ਸਮ੍ਰਿਤੀ_ਦਿਓ (bufsize);
  ਜੇ (buf == ਨਿਰਾ)
    {
      ਲਿਖੋ ("cannot allocate %zd bytes\n", bufsize);
      ਵਾਪਸ 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = ਲੜੀ_ਲੰਬਾਈ (buf);
  ਜੇ (r != l)
    {
       ਲਿਖੋ ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ਨਤੀਜਾ = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, ਨਿਰਾ);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = ਲੜੀ_ਲੰਬਾਈ (buf);
  ਜੇ (r != l)
    {
       ਲਿਖੋ ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       ਨਤੀਜਾ = 1;
    }

  freelocale (loc);

  ਮੁਕਤ (buf);

  ਵਾਪਸ ਨਤੀਜਾ;
}


ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  ਨਤੀਜਾ |= test ("C");
  ਨਤੀਜਾ |= test ("en_US.ISO-8859-1");
  ਨਤੀਜਾ |= test ("de_DE.UTF-8");

  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
