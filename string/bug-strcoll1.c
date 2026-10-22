#include <stdio.h>
#include <string.h>
#include <locale.h>

ຈຳນວນເຕັມ
main (void)
{
  const var_na t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  const var_na t2[] = "00000-00000.COM";
  ຈຳນວນເຕັມ res1;
  ຈຳນວນເຕັມ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ສົ່ງຄືນ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
