#include <iostream>
#include "includes/fibonacci.h"
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if(argc <= 1){
        std::cout << "No arguments inputed";
        return 0;
    }
    std::vector<unsigned int> fibo = fibonacci(std::stoi(argv[1]));
    for(int i = 0; i < fibo.size(); i++){
        std::cout << std::to_string(fibo[i]) << " ";
    }
    std::cout << "\n";
    return 0;
}
