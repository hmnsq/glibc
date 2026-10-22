#شامل <stdio.h>
#شامل <string.h>
#شامل <locale.h>

صحیح
اصلی (تهی)
{
  ثابت نویسه t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ثابت نویسه t2[] = "00000-00000.COM";
  صحیح res1;
  صحیح res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  بازگشت ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
