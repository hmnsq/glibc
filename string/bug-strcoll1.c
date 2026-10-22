#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <locale.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
ମୁଖ୍ୟ (ଶୂନ୍ୟ)
{
  ଅଚଳ ଅକ୍ଷର t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ଅଚଳ ଅକ୍ଷର t2[] = "00000-00000.COM";
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା res1;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  ଫେରନ୍ତୁ ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
