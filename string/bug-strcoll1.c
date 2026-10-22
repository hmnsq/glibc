#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <locale.h>

صحيح
اصلی (فراغ)
{
  ثابت حرف t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ثابت حرف t2[] = "00000-00000.COM";
  صحيح res1;
  صحيح res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  أرجع ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
