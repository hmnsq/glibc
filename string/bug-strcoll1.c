#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <locale.h>

પૂર્ણાંક
મુખ્ય (શૂન્ય)
{
  અચલ અક્ષર t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  અચલ અક્ષર t2[] = "00000-00000.COM";
  પૂર્ણાંક res1;
  પૂર્ણાંક res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  પાછા ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
