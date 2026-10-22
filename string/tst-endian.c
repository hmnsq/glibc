#అన్తర్భావ <byteswap.h>
#అన్తర్భావ <endian.h>
#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <libc-diag.h>

#ఒకవేళ __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#లేకపోతే
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#అయితే_ముగింపు

పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం ఫలితం = 0;

  కొరకు (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      ఒకవేళ (i < UINT64_C (65536))
	{
	  DIAG_నెట్టు_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ఒకవేళ (htobe16 (be16toh (i)) != i)
	    {
	      రాయి ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      ఫలితం = 1;
	    }
	  ఒకవేళ (htole16 (le16toh (i)) != i)
	    {
	      రాయి ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      ఫలితం = 1;
	    }
	  DIAG_తీయి_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ఒకవేళ (htole16 (i) != n[0])
	    {
	      రాయి ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      ఫలితం = 1;
	    }
	  ఒకవేళ (htobe16 (i) != n[1])
	    {
	      రాయి ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      ఫలితం = 1;
	    }
	}

      ఒకవేళ (i < UINT64_C (4294967296))
	{
	  DIAG_నెట్టు_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ఒకవేళ (htobe32 (be32toh (i)) != i)
	    {
	      రాయి ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      ఫలితం = 1;
	    }
	  ఒకవేళ (htole32 (le32toh (i)) != i)
	    {
	      రాయి ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      ఫలితం = 1;
	    }
	  DIAG_తీయి_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ఒకవేళ (htole32 (i) != n[0])
	    {
	      రాయి ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      ఫలితం = 1;
	    }
	  ఒకవేళ (htobe32 (i) != n[1])
	    {
	      రాయి ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      ఫలితం = 1;
	    }
	}

      DIAG_నెట్టు_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      ఒకవేళ (htobe64 (be64toh (i)) != i)
	{
	  రాయి ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  ఫలితం = 1;
	}
      ఒకవేళ (htole64 (le64toh (i)) != i)
	{
	  రాయి ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  ఫలితం = 1;
	}
      DIAG_తీయి_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      ఒకవేళ (htole64 (i) != n[0])
	{
	  రాయి ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  ఫలితం = 1;
	}
      ఒకవేళ (htobe64 (i) != n[1])
	{
	  రాయి ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  ఫలితం = 1;
	}
    }

  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
