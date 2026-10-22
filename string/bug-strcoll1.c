#include <stdio.h>
#include <string.h>
#include <locale.h>

puur_naa_nka
main (void)
{
  const var_na t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  const var_na t2[] = "00000-00000.COM";
  puur_naa_nka res1;
  puur_naa_nka res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ᬯᬮᬶ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
