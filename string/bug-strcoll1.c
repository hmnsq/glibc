#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <locale.h>

ಪೂರ್ಣಾಂಕ
ಮುಖ್ಯ (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t2[] = "00000-00000.COM";
  ಪೂರ್ಣಾಂಕ res1;
  ಪೂರ್ಣಾಂಕ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ಹಿಂತಿರುಗಿ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
