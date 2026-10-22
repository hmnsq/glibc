#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <locale.h>

ಪೂರ್ಣಾಙ್ಕ
main (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ಧ್ರುವ ವರ್ಣ t2[] = "00000-00000.COM";
  ಪೂರ್ಣಾಙ್ಕ res1;
  ಪೂರ್ಣಾಙ್ಕ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ಪ್ರತ್ಯಾಗಮ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
