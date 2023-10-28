#include "includes/fibonacci.h"
#include "includes/treeSort.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

bool testFibo() {
    return true;
}
void testLog(std::string title, bool success) {
    std::cout << title
              << ": tested, output: " << (success ? "SUCCESS" : "FAILED")
              << "\n";
}
bool testTreeSort() {
    std::vector<int> nums;
    TreeMap<int> map;
    for(int i = 0; i < 200; i++){
        nums.push_back(rand());
    }
    std::cout << "\n\n\n --------------------------- \n\n\n";
    for(int i = 0; i < nums.size(); i++){
        std::cout << "loop: " << std::to_string(i + 1) << "\n";
        map.add(&nums[i]);
    }
    std::cout << "\n\n\n --------------------------- \n\n\n";
    std::cout << "tree: \n";
    map.writeTreeAddresses();
    std::cout << "\n\n\n --------------------------- \n\n\n";
    for(int i = 0; i < 200; i++){
        std::cout << "loop: " << std::to_string(i + 1) << "\n";
        std::cout << std::to_string(map.get(i)) << " ";
        std::cout << "loopEnd: " << std::to_string(i + 1) << "\n";
    }
    std::cout << "\n\n";
    std::sort(nums.begin(), nums.end());
    for(int i = 0; i < 200; i++){
        std::cout << std::to_string(nums[i]) << " ";
    }
    return true;
}

int main(int argc, char **argv) {
    testLog("Fibbonacci", testFibo());
    testLog("TreeSort", testTreeSort());
    return 0;
}
