#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>

ਪੂਰਨ
ਮੁੱਖ (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ਅਚਲ ਅੱਖਰ t2[] = "00000-00000.COM";
  ਪੂਰਨ res1;
  ਪੂਰਨ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ਵਾਪਸ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
