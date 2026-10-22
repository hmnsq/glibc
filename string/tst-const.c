/* Test <string.h> const-generic macros.
   Copyright (C) 2025-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <string.h>
#అన్తర్భావ <libc-diag.h>

శూన్య *vp;
స్థిరరాశి శూన్య *cvp;
పూర్ణాంకం *ip;
స్థిరరాశి పూర్ణాంకం *cip;
అక్షరం *cp;
స్థిరరాశి అక్షరం *ccp;
పూర్ణాంకం c;
size_t sz;

#నిర్వచించు CHECK_TYPE(సమాసం, TYPE)					\
  _Static_assert (_Generic (సమాసం, TYPE: 1), "type check")

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), శూన్య *);
  CHECK_TYPE (memchr (cvp, c, sz), స్థిరరాశి శూన్య *);
  CHECK_TYPE (memchr (ip, c, sz), శూన్య *);
  CHECK_TYPE (memchr (cip, c, sz), స్థిరరాశి శూన్య *);
  CHECK_TYPE (memchr (cp, c, sz), శూన్య *);
  CHECK_TYPE (memchr (ccp, c, sz), స్థిరరాశి శూన్య *);
  DIAG_నెట్టు_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), శూన్య *);
  CHECK_TYPE (memchr ((శూన్య *) 0, c, sz), శూన్య *);
  DIAG_తీయి_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), శూన్య *);
  CHECK_TYPE (strchr (vp, c), అక్షరం *);
  CHECK_TYPE (strchr (cvp, c), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (strchr (cp, c), అక్షరం *);
  CHECK_TYPE (strchr (ccp, c), స్థిరరాశి అక్షరం *);
  DIAG_నెట్టు_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), అక్షరం *);
  CHECK_TYPE (strchr ((శూన్య *) 0, c), అక్షరం *);
  DIAG_తీయి_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), అక్షరం *);
  CHECK_TYPE (strpbrk (vp, vp), అక్షరం *);
  CHECK_TYPE (strpbrk (vp, cvp), అక్షరం *);
  CHECK_TYPE (strpbrk (cvp, vp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (strpbrk (cvp, cvp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (strpbrk (cp, cp), అక్షరం *);
  CHECK_TYPE (strpbrk (cp, ccp), అక్షరం *);
  CHECK_TYPE (strpbrk (ccp, cp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (strpbrk (ccp, ccp), స్థిరరాశి అక్షరం *);
  DIAG_నెట్టు_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), అక్షరం *);
  CHECK_TYPE (strpbrk (0, ccp), అక్షరం *);
  CHECK_TYPE (strpbrk ((శూన్య *) 0, cp), అక్షరం *);
  CHECK_TYPE (strpbrk ((శూన్య *) 0, ccp), అక్షరం *);
  DIAG_తీయి_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), అక్షరం *);
  CHECK_TYPE (strrchr (vp, c), అక్షరం *);
  CHECK_TYPE (strrchr (cvp, c), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (strrchr (cp, c), అక్షరం *);
  CHECK_TYPE (strrchr (ccp, c), స్థిరరాశి అక్షరం *);
  DIAG_నెట్టు_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), అక్షరం *);
  CHECK_TYPE (strrchr ((శూన్య *) 0, c), అక్షరం *);
  DIAG_తీయి_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (vp, vp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (vp, cvp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (cvp, vp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (cvp, cvp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (cp, cp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (cp, ccp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (ccp, cp), స్థిరరాశి అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (ccp, ccp), స్థిరరాశి అక్షరం *);
  DIAG_నెట్టు_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (0, cp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన (0, ccp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన ((శూన్య *) 0, cp), అక్షరం *);
  CHECK_TYPE (అక్షరశ్రేణి_శోధన ((శూన్య *) 0, ccp), అక్షరం *);
  DIAG_తీయి_NEEDS_COMMENT;
  CHECK_TYPE ((అక్షరశ్రేణి_శోధన) (ccp, ccp), అక్షరం *);
  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
