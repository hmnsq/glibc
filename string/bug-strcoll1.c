#include <stdio.h>
#include <string.h>
#include <locale.h>

ចំនួនគត់
main (void)
{
  const var_na t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  const var_na t2[] = "00000-00000.COM";
  ចំនួនគត់ res1;
  ចំនួនគត់ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ត្រឡប់ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
