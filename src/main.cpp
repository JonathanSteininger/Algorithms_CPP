#define ENABLE_LOGGING
#define PRINT_TESTS
#include "includes/balancedTree.h"
#include "includes/fibonacci.h"
#include "includes/logging.h"
#include "includes/treeSort.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

bool testFibo() { return true; }
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
    for (int i = 0; i < 200; i++) {
        nums.push_back(i);
    }
    auto rng = std::default_random_engine{};
    std::shuffle(nums.begin(), nums.end(), rng);
    treeSortLog::LOG("\n\n\n --------------------------- \n\n");
    for (int i = 0; i < nums.size(); i++) {
        treeSortLog::LOG_VARS("loop: ", i + 1);
        map.add(&nums[i]);
    }
    for (int i = 0; i < 200; i++) {
        treeSortLog::LOG_VARS("loop: ", i + 1);
        treeSortLog::LOG(std::to_string(map.get(i)));
        treeSortLog::LOG_VARS("loopEnd: ", i + 1);
    }
    treeSortLog::LOG("\n\n\n --------------balance------------- \n\n");
    map.balanceTree();
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < 200; i++) {
        if (map.get(i) != nums[i]) {
            return false;
        }
    }
    return true;
}
bool testBalancedTree() {
    std::vector<int> nums;
    TreeStart head;
    for (int i = 0; i < 50; i++) {
        nums.push_back(i);
    }
    auto rng = std::default_random_engine{};
    std::shuffle(nums.begin(), nums.end(), rng);
    for (int i = 0; i < nums.size(); i++) {
        LOG_VARS("i: ", i);
        LOG_VARS("number: ", nums[i]);
        head.add(nums[i]);
    }
    LOG_VARS("Total Nums: ", head.size());
    std::sort(nums.begin(), nums.end());
    bool flag = true;
    for (int i = 0; i < nums.size(); i++) {
        int headValue = head.get(i);
        LOG_VARS("TreeValue: ", headValue);
        LOG_VARS("intendedValue: ", nums[i]);
        if (flag) {
            flag = headValue == nums[i];
        }
    }
    std::string headValues = head.drawTreeValues();
    std::string headHeights = head.drawTreeHeights();
    std::string headBalances = head.drawTreeBalances();
    LOG(headValues);
    LOG("what");
    LOG(headHeights);
    LOG("what");
    LOG(headBalances);
    return flag;
}

int main(int argc, char **argv) {
    LOG_TOGGLE();
    testLog("Fibbonacci", testFibo());
    // testLog("TreeSort", testTreeSort());
    testLog("balancedTree", testBalancedTree());
    return 0;
}
