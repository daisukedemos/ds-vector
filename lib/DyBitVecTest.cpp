#include <gtest/gtest.h>
#include "DyBitVec.hpp"

using namespace std;
using namespace ds_vector;

TEST(DyBitVec, trivial){
  DyBitVec dbv;
  ASSERT_EQ(0, dbv.Size());
  ASSERT_EQ(0, dbv.OneNum());
  ASSERT_EQ(0, dbv.Rank(0, 0));
  ASSERT_EQ(0, dbv.Rank(10, 0));
  dbv.Clear();
  
  dbv.Insert(0, 0);
  dbv.Insert(0, 1);
  dbv.Insert(0, 1);

  ASSERT_EQ(3, dbv.Size());
  ASSERT_EQ(2, dbv.OneNum());
  
  ASSERT_EQ(1, dbv.Lookup(0));
  ASSERT_EQ(1, dbv.Lookup(1));
  ASSERT_EQ(0, dbv.Lookup(2));

  ASSERT_EQ(0, dbv.Rank(0, 1));
  ASSERT_EQ(1, dbv.Rank(1, 1));
  ASSERT_EQ(2, dbv.Rank(2, 1));
  ASSERT_EQ(2, dbv.Rank(3, 1));

  ASSERT_EQ(1, dbv.Rank(3, 0));
}

TEST(DyBitVec, zeros){
  DyBitVec dbv;
  uint64_t N = 3000;
  for (uint64_t i = 0; i < N; ++i){
    dbv.Insert(0, 0);
    ASSERT_EQ(0, dbv.Lookup(i));
  }
  ASSERT_EQ(N, dbv.Size());
  ASSERT_EQ(0, dbv.OneNum());
  for (uint64_t i = 0; i < N; ++i){
    ASSERT_EQ(0, dbv.Lookup(i));
    ASSERT_EQ(0, dbv.Rank(i, 1));
  }

  dbv.Clear();
  ASSERT_EQ(0, dbv.Size());
  ASSERT_EQ(0, dbv.OneNum());
}

TEST(DyBitVec, ones){
  DyBitVec dbv;
  uint64_t N = 10000;
  for (uint64_t i = 0; i < N; ++i){
    dbv.Insert(0, 1);
  }
  ASSERT_EQ(N, dbv.Size());
  ASSERT_EQ(N, dbv.OneNum());
  for (uint64_t i = 0; i < N; ++i){
    ASSERT_EQ(1, dbv.Lookup(i));
    ASSERT_EQ(i, dbv.Rank(i, 1));
  }

  dbv.Clear();
  ASSERT_EQ(0, dbv.Size());
  ASSERT_EQ(0, dbv.OneNum());
}

TEST(DyBitVec, random){
  DyBitVec dbv;
  vector<uint8_t> bits;
  uint64_t N = 10000;
  for (uint64_t i = 0; i < N; ++i){
    uint64_t pos = rand() % (i+1);
    uint64_t bit = rand() % 2;
    dbv.Insert(pos, bit);
    bits.insert(bits.begin() + pos, bit);
  }

  ASSERT_EQ(bits.size(), dbv.Size());
  uint64_t one_num = 0;
  for (uint64_t i = 0; i < bits.size(); ++i){
    ASSERT_EQ(bits[i], dbv.Lookup(i)) << " i=" << i;
    ASSERT_EQ(one_num, dbv.Rank(i, 1)) << " i=" << i;
    one_num += bits[i];
  }
  ASSERT_EQ(one_num, dbv.OneNum());
}


