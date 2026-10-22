#ਅਨ੍ਤਰ੍ਭਾਵ <byteswap.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <endian.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

#ਜੇ __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#ਨਹੀਂਤਾਂ
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#ਜੇ_ਅੰਤ

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ ਨਤੀਜਾ = 0;

  ਲਈ (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      ਜੇ (i < UINT64_C (65536))
	{
	  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ਜੇ (htobe16 (be16toh (i)) != i)
	    {
	      ਲਿਖੋ ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (htole16 (le16toh (i)) != i)
	    {
	      ਲਿਖੋ ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      ਨਤੀਜਾ = 1;
	    }
	  DIAG_ਕੱਢੋ_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ਜੇ (htole16 (i) != n[0])
	    {
	      ਲਿਖੋ ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (htobe16 (i) != n[1])
	    {
	      ਲਿਖੋ ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      ਨਤੀਜਾ = 1;
	    }
	}

      ਜੇ (i < UINT64_C (4294967296))
	{
	  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ਜੇ (htobe32 (be32toh (i)) != i)
	    {
	      ਲਿਖੋ ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (htole32 (le32toh (i)) != i)
	    {
	      ਲਿਖੋ ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      ਨਤੀਜਾ = 1;
	    }
	  DIAG_ਕੱਢੋ_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ਜੇ (htole32 (i) != n[0])
	    {
	      ਲਿਖੋ ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      ਨਤੀਜਾ = 1;
	    }
	  ਜੇ (htobe32 (i) != n[1])
	    {
	      ਲਿਖੋ ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      ਨਤੀਜਾ = 1;
	    }
	}

      DIAG_ਧੱਕੋ_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      ਜੇ (htobe64 (be64toh (i)) != i)
	{
	  ਲਿਖੋ ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  ਨਤੀਜਾ = 1;
	}
      ਜੇ (htole64 (le64toh (i)) != i)
	{
	  ਲਿਖੋ ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  ਨਤੀਜਾ = 1;
	}
      DIAG_ਕੱਢੋ_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      ਜੇ (htole64 (i) != n[0])
	{
	  ਲਿਖੋ ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  ਨਤੀਜਾ = 1;
	}
      ਜੇ (htobe64 (i) != n[1])
	{
	  ਲਿਖੋ ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  ਨਤੀਜਾ = 1;
	}
    }

  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
