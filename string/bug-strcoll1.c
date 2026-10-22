#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <locale.h>

पूर्णाङ्क
main (शून्य)
{
  ध्रुव वर्ण t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  ध्रुव वर्ण t2[] = "00000-00000.COM";
  पूर्णाङ्क res1;
  पूर्णाङ्क res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  पटिनिवत्त ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
