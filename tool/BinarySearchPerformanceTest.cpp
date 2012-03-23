#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(){
  vector<uint64_t> bs(64);
  for (uint64_t i = 0; i < 64; ++i){
    bs[i] = rand();
  }

  uint64_t sum = 0;
  for (uint64_t i = 0; i < 1000000; ++i){
    uint64_t x = rand();
    vector<uint64_t>::const_iterator it = lower_bound(bs.begin(), bs.end(), x);
    sum += it - bs.begin();
  }
  if (sum == 777){
    cout << "lucky" << endl;
  }
  return 0;
  

}

