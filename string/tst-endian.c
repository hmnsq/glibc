#अन्तर्भाव <byteswap.h>
#अन्तर्भाव <endian.h>
#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <libc-diag.h>

#यदि __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#अन्यथा
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#endif

पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क result = 0;

  प्रति (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      यदि (i < UINT64_C (65536))
	{
	  DIAG_धकेलो_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  यदि (htobe16 (be16toh (i)) != i)
	    {
	      म_लिखो ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      result = 1;
	    }
	  यदि (htole16 (le16toh (i)) != i)
	    {
	      म_लिखो ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      result = 1;
	    }
	  DIAG_निकालो_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  यदि (htole16 (i) != n[0])
	    {
	      म_लिखो ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      result = 1;
	    }
	  यदि (htobe16 (i) != n[1])
	    {
	      म_लिखो ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      result = 1;
	    }
	}

      यदि (i < UINT64_C (4294967296))
	{
	  DIAG_धकेलो_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  यदि (htobe32 (be32toh (i)) != i)
	    {
	      म_लिखो ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      result = 1;
	    }
	  यदि (htole32 (le32toh (i)) != i)
	    {
	      म_लिखो ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      result = 1;
	    }
	  DIAG_निकालो_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  यदि (htole32 (i) != n[0])
	    {
	      म_लिखो ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      result = 1;
	    }
	  यदि (htobe32 (i) != n[1])
	    {
	      म_लिखो ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      result = 1;
	    }
	}

      DIAG_धकेलो_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      यदि (htobe64 (be64toh (i)) != i)
	{
	  म_लिखो ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  result = 1;
	}
      यदि (htole64 (le64toh (i)) != i)
	{
	  म_लिखो ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  result = 1;
	}
      DIAG_निकालो_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      यदि (htole64 (i) != n[0])
	{
	  म_लिखो ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  result = 1;
	}
      यदि (htobe64 (i) != n[1])
	{
	  म_लिखो ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  result = 1;
	}
    }

  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
