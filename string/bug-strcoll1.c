#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <locale.h>

পূর্ণসংখ্যা
প্রধান (শূন্য)
{
  ধ্রুবক অক্ষর t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ধ্রুবক অক্ষর t2[] = "00000-00000.COM";
  পূর্ণসংখ্যা res1;
  পূর্ণসংখ্যা res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ফেরত ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
