/* Test strcspn functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#నిర్వచించు STRPBRK_ఫలితం(s, pos) (pos)
#నిర్వచించు RES_TYPE size_t
#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "strcspn"
#లేకపోతే
# define TEST_NAME "wcscspn"
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRCSPN strcspn
# define CHAR అక్షరం
# define SIMPLE_STRCSPN simple_strcspn
# define STUPID_STRCSPN stupid_strcspn
# define STRLEN అక్షరశ్రేణి_పొడవు
#లేకపోతే
# include <wchar.h>
# define STRCSPN wcscspn
# define CHAR wchar_t
# define SIMPLE_STRCSPN simple_wcscspn
# define STUPID_STRCSPN stupid_wcscspn
# define STRLEN wcslen
#అయితే_ముగింపు /* WIDE */

రకనిర్వచనం size_t (*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);
size_t SIMPLE_STRCSPN (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);
size_t STUPID_STRCSPN (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);

IMPL (STUPID_STRCSPN, 0)
IMPL (SIMPLE_STRCSPN, 0)
IMPL (STRCSPN, 1)

size_t
SIMPLE_STRCSPN (స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *rej)
{
  స్థిరరాశి CHAR *r, *str = s;
  CHAR c;

  అయితే ((c = *s++) != '\0')
    కొరకు (r = rej; *r != '\0'; ++r)
      ఒకవేళ (*r == c)
	తిరిగి s - str - 1;
  తిరిగి s - str - 1;
}

size_t
STUPID_STRCSPN (స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *rej)
{
  size_t ns = STRLEN (s), nrej = STRLEN (rej);
  size_t i, j;

  కొరకు (i = 0; i < ns; ++i)
    కొరకు (j = 0; j < nrej; ++j)
      ఒకవేళ (s[i] == rej[j])
	తిరిగి i;
  తిరిగి i;
}

#నిర్వచనం_రద్దు CHAR
#నిర్వచనం_రద్దు STRLEN
#అన్తర్భావ "test-strpbrk.c"
