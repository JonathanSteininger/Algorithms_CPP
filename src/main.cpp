#define ENABLE_LOGGING
//#define ENABLE_LOGGING_TREE
#define PRINT_TESTS
#include "includes/fibonacci.h"
#include "includes/treeSort.h"
#include "includes/logging.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>

bool testFibo() {
    return true;
}
void testLog(std::string title, bool success) {
#ifdef PRINT_TESTS
    std::cout << title
              << ": tested, output: " << (success ? "SUCCESS" : "FAILED")
              << "\n";
#endif
}
bool testTreeSort() {
    std::vector<int> nums;
    TreeMap<int> map;
    for(int i = 0; i < 200; i++){
        nums.push_back(i);
    }
    auto rng = std::default_random_engine{};
    std::shuffle(nums.begin(), nums.end(), rng);
    treeSortLog::LOG("\n\n\n --------------------------- \n\n");
    for(int i = 0; i < nums.size(); i++){
        treeSortLog::LOG_VARS("loop: ",i + 1);
        map.add(&nums[i]);
    }
    for(int i = 0; i < 200; i++){
        treeSortLog::LOG_VARS("loop: ",i + 1);
        treeSortLog::LOG(std::to_string(map.get(i)));
        treeSortLog::LOG_VARS("loopEnd: ",i + 1);
    }
    std::sort(nums.begin(), nums.end());
    for(int i = 0; i < 200; i++){
        if(map.get(i) != nums[i]){
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    testLog("Fibbonacci", testFibo());
    testLog("TreeSort", testTreeSort());
    return 0;
}
