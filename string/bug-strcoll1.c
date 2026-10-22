#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <locale.h>

പൂർണ്ണസംഖ്യ
പ്രധാന (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  സ്ഥിരം അക്ഷരം t2[] = "00000-00000.COM";
  പൂർണ്ണസംഖ്യ res1;
  പൂർണ്ണസംഖ്യ res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  തിരികെ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
