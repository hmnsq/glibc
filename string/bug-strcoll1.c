#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <locale.h>

முழு
முதன்மை (வெறுமை)
{
  மாறிலி எழுத்து t1[] = "0-0-0-0-0-0-0-0-0-0.COM";
  மாறிலி எழுத்து t2[] = "00000-00000.COM";
  முழு res1;
  முழு res2;

  setlocale (LC_ALL, "en_US.ISO-8859-1");

  res1 = strcoll (t1, t2);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, res1);
  res2 = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, res2);

  திரும்பு ((res1 == 0 && res2 != 0)
	  || (res1 != 0 && res2 == 0)
	  || (res1 < 0 && res2 < 0)
	  || (res1 > 0 && res2 > 0));
}
