/* 
 *  Copyright (c) 2012 Daisuke Okanohara
  * 
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 * 
 *   1. Redistributions of source code must retain the above Copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above Copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 */


#include <vector>
#include <gtest/gtest.h>
#include "DyWaveletTree.hpp"
#include "Util.hpp"

using namespace std;
using namespace ds_vector;

TEST(DyWaveletTree, trivial){
  DyWaveletTree dwt;
  ASSERT_EQ(0, dwt.Size());
  ASSERT_EQ(0, dwt.Rank(0, 0));
  
  dwt.Clear();
  dwt.Insert(0, 0);
  dwt.Insert(1, 7);
  dwt.Insert(1, 77);
  dwt.Insert(0, 77);

  Util::PrintBit(dwt.Lookup(0));
  Util::PrintBit(77);
  
  ASSERT_EQ(77, dwt.Lookup(0));
  ASSERT_EQ(0,  dwt.Lookup(1));
  ASSERT_EQ(77, dwt.Lookup(2));
  ASSERT_EQ(7,  dwt.Lookup(3));

  ASSERT_EQ(0, dwt.Rank(0, 0));
  ASSERT_EQ(1, dwt.Rank(1, 77));
  ASSERT_EQ(1, dwt.Rank(2, 0));
  ASSERT_EQ(2, dwt.Rank(3, 77));
  ASSERT_EQ(1, dwt.Rank(4, 7));
  ASSERT_EQ(2, dwt.Rank(4, 77));
  ASSERT_EQ(0, dwt.Rank(4, 6));
  
  ASSERT_EQ(4, dwt.Size());
}

TEST(DyWaveletTree, zeros){
  uint64_t N = 10000;
  DyWaveletTree dwt;
  for (uint64_t i = 0; i < N; ++i){
    dwt.Insert(0, 0);
  }

  ASSERT_EQ(N, dwt.Size());
  for (uint64_t i = 0; i < N; ++i){
    ASSERT_EQ(0, dwt.Lookup(i));
  }

  for (uint64_t i = 0; i < N; ++i){
    ASSERT_EQ(i, dwt.Rank(i, 0));
  }
}

TEST(DyWaveletTree, random){
  uint64_t N = 10000;
  vector<uint8_t> T;
  DyWaveletTree dwt;
  for (uint64_t i = 0; i < N; ++i){
    uint64_t pos = rand() % (i+1);
    uint8_t x = rand() % 0x100;
    dwt.Insert(pos, x);
    T.insert(T.begin() + pos, x);
  }

  ASSERT_EQ(N, dwt.Size());

  for (uint64_t i = 0; i < N; ++i){
    ASSERT_EQ(T[i], dwt.Lookup(i));
  }

  vector<uint64_t> cums(0x100);
  for (uint64_t i = 0; i < N; ++i){
    if ((rand() % 20) == 0){
      for (uint64_t c = 0; c < 0x100; ++c){
        ASSERT_EQ(cums[c], dwt.Rank(i, c));
      }
    }
    cums[T[i]]++;
  }
}
