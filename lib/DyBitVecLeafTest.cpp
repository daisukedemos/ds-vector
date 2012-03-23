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

#include <gtest/gtest.h>
#include "DyBitVecLeaf.hpp"

using namespace std;
using namespace ds_vector;

TEST(DyBitVecLeaf, trivial){
  DyBitVecLeaf leaf;
  ASSERT_EQ(0, leaf.Size());
  ASSERT_EQ(0, leaf.OneNum());
  ASSERT_FALSE(leaf.IsFull());
  ASSERT_EQ(0, leaf.Rank(0));
  ASSERT_EQ(0, leaf.Rank(10));
  leaf.Clear();
  
  leaf.Insert(0, 0);
  leaf.Insert(0, 1);
  leaf.Insert(0, 1);

  ASSERT_EQ(3, leaf.Size());
  ASSERT_EQ(2, leaf.OneNum());
  
  ASSERT_EQ(1, leaf.Lookup(0));
  ASSERT_EQ(1, leaf.Lookup(1));
  ASSERT_EQ(0, leaf.Lookup(2));

  ASSERT_EQ(0, leaf.Rank(0));
  ASSERT_EQ(1, leaf.Rank(1));
  ASSERT_EQ(2, leaf.Rank(2));
  ASSERT_EQ(2, leaf.Rank(3));
}

TEST(DyBitVecLeaf, zeros){
  DyBitVecLeaf leaf;
  uint64_t block_size = 64;
  for (uint64_t i = 0; i < block_size * block_size / 2; ++i){
    leaf.Insert(0, 0);
  }
  ASSERT_EQ(block_size * block_size / 2, leaf.Size());
  ASSERT_EQ(0, leaf.OneNum());
  for (uint64_t i = 0; i < block_size * block_size / 2; ++i){
    ASSERT_EQ(0, leaf.Lookup(i));
    ASSERT_EQ(0, leaf.Rank(i));
  }

  leaf.Clear();
  ASSERT_EQ(0, leaf.Size());
  ASSERT_EQ(0, leaf.OneNum());
}

TEST(DyBitVecLeaf, ones){
  DyBitVecLeaf leaf;
  uint64_t block_size = 64;
  for (uint64_t i = 0; i < block_size * block_size / 2; ++i){
    leaf.Insert(0, 1);
  }
  ASSERT_EQ(block_size * block_size / 2, leaf.Size());
  ASSERT_EQ(block_size * block_size / 2, leaf.OneNum());
  for (uint64_t i = 0; i < block_size * block_size / 2; ++i){
    ASSERT_EQ(1, leaf.Lookup(i));
    ASSERT_EQ(i, leaf.Rank(i));
  }

  leaf.Clear();
  ASSERT_EQ(0, leaf.Size());
  ASSERT_EQ(0, leaf.OneNum());
}

TEST(DyBitVecLeaf, random){
  DyBitVecLeaf leaf;
  vector<uint8_t> bits;
  for (uint64_t i = 0; !leaf.IsFull(); ++i){
    uint64_t pos = rand() % (i+1);
    uint64_t bit = rand() % 2;
    leaf.Insert(pos, bit);
    bits.insert(bits.begin() + pos, bit);
  }

  ASSERT_EQ(bits.size(), leaf.Size());
  uint64_t one_num = 0;
  for (uint64_t i = 0; i < bits.size(); ++i){
    ASSERT_EQ(bits[i], leaf.Lookup(i)) << " i=" << i;
    ASSERT_EQ(one_num, leaf.Rank(i)) << " i=" << i;
    one_num += bits[i];
  }
  ASSERT_EQ(one_num, leaf.OneNum());
}

