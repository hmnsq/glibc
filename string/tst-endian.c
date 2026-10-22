#ضمن <byteswap.h>
#ضمن <endian.h>
#ضمن <inttypes.h>
#ضمن <stdio.h>
#ضمن <stdint.h>
#ضمن <libc-diag.h>

#إذا __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#وإلا
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#جے_انت

صحيح
do_test (فراغ)
{
  صحيح نتیجہ = 0;

  لكل (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      إذا (i < UINT64_C (65536))
	{
	  DIAG_ڈالو_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  إذا (htobe16 (be16toh (i)) != i)
	    {
	      لکھو ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      نتیجہ = 1;
	    }
	  إذا (htole16 (le16toh (i)) != i)
	    {
	      لکھو ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      نتیجہ = 1;
	    }
	  DIAG_نکالو_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  إذا (htole16 (i) != n[0])
	    {
	      لکھو ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      نتیجہ = 1;
	    }
	  إذا (htobe16 (i) != n[1])
	    {
	      لکھو ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      نتیجہ = 1;
	    }
	}

      إذا (i < UINT64_C (4294967296))
	{
	  DIAG_ڈالو_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  إذا (htobe32 (be32toh (i)) != i)
	    {
	      لکھو ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      نتیجہ = 1;
	    }
	  إذا (htole32 (le32toh (i)) != i)
	    {
	      لکھو ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      نتیجہ = 1;
	    }
	  DIAG_نکالو_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  إذا (htole32 (i) != n[0])
	    {
	      لکھو ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      نتیجہ = 1;
	    }
	  إذا (htobe32 (i) != n[1])
	    {
	      لکھو ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      نتیجہ = 1;
	    }
	}

      DIAG_ڈالو_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      إذا (htobe64 (be64toh (i)) != i)
	{
	  لکھو ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  نتیجہ = 1;
	}
      إذا (htole64 (le64toh (i)) != i)
	{
	  لکھو ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  نتیجہ = 1;
	}
      DIAG_نکالو_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      إذا (htole64 (i) != n[0])
	{
	  لکھو ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  نتیجہ = 1;
	}
      إذا (htobe64 (i) != n[1])
	{
	  لکھو ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  نتیجہ = 1;
	}
    }

  أرجع نتیجہ;
}

#ضمن <support/test-driver.c>
