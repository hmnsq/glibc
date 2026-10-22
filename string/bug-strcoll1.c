#include <stdio.h>
#include <string.h>
#include <locale.h>

整数
主要 (void)
{
  const char t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  const char t2[] = "00000-00000.COM";
  整数 res1;
  整数 res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  返回 ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
