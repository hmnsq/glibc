/* Test for strverscmp() */

#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#define  MAX_STRINGS      256
#define  MAX_લીટી_SIZE    32

સ્થિર પૂર્ણાંક
compare (અચલ શૂન્ય *p1, અચલ શૂન્ય *p2)
{
  પાછા strverscmp (*((અક્ષર **) p1), *((અક્ષર **) p2));
}

પૂર્ણાંક
do_test (શૂન્ય)
{
  અક્ષર લીટી[MAX_લીટી_SIZE + 1];
  અક્ષર *str[MAX_STRINGS];
  પૂર્ણાંક  ગણતરી = 0;
  પૂર્ણાંક  i, n;

  જ્યારે (ગણતરી < MAX_STRINGS && fgets (લીટી, MAX_લીટી_SIZE, stdin) != ખાલી)
    {
      n = strlen (લીટી) - 1;

      જો (લીટી[n] == '\n')
        લીટી[n] = '\0';

      str[ગણતરી] = strdup (લીટી);

      જો (str[ગણતરી] == ખાલી)
        exit (EXIT_FAILURE);

      ++ગણતરી;
    }

  qsort (str, ગણતરી, કદ (અક્ષર *), compare);

  માટે (i = 0; i < ગણતરી; ++i)
    puts (str[i]);

  પાછા EXIT_SUCCESS;
}

#અન્તર્ભાવ <support/test-driver.c>
