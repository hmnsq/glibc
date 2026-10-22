#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <locale.h>

পূর্ণাঙ্ক
main (শূন্য)
{
  ধ্রুব বর্ণ t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ধ্রুব বর্ণ t2[] = "00000-00000.COM";
  পূর্ণাঙ্ক res1;
  পূর্ণাঙ্ক res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  প্রত্যাগম ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
