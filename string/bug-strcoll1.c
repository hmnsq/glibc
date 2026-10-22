#include <stdio.h>
#include <string.h>
#include <locale.h>

số_nguyên
main (void)
{
  const char t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  const char t2[] = "00000-00000.COM";
  số_nguyên res1;
  số_nguyên res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  trả_về ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
