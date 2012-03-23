#include <iostream>
#include "../lib/DyBitVec.hpp"

using namespace std;

int main(){
  ds_vector::DyBitVec dbv;
  uint64_t N = 1000000;
  for (uint64_t i = 0; i < N; ++i){
    uint64_t pos = rand() % (i+1);
    uint64_t bit = rand() % 2;
    dbv.Insert(pos, bit);
  }

  uint64_t leaf_num = dbv.LeafNum();
  uint64_t node_num = leaf_num - 1;
  uint64_t byte_num = node_num * 8 * 4 
    + leaf_num * (8 * 64 + 64 * 2);
  cout << "ratio=" << (float)byte_num / (N / 8) << endl;
  cout << dbv.LeafNum() << endl;
  cout << dbv.Size() << endl;
  return 0;
}
