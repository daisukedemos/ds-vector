#include <iostream>
#include "../lib/PrefixSumLeaf.hpp"

using namespace std;
using namespace ds_vector;

int main(){
  PrefixSumLeaf ps;
  ps.Init(64);
  for (uint64_t i = 0; i < 64; ++i){
    ps.Set(i, rand());
  }
  
  uint64_t sum = 0;
  for (uint64_t i = 0; i < 1000000; ++i){
    sum += ps.Find(rand());
  }
  if (sum == 777){
    cout << "lucky" << endl;
  }
  return 0;
}
