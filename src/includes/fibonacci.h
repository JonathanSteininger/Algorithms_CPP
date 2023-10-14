#include <climits>
#include <vector>
#include <limits>

std::vector<unsigned int> fibonacci(int distance){
    if(distance <= 0){
        std::vector<unsigned int> temp;
        temp.push_back(0);
        return temp; 
    }
    std::vector<unsigned int> previous = fibonacci(distance - 1);

    unsigned int size = previous.size();
    if(size == 1){
        previous.push_back(1);
        return previous;
    }
    unsigned int last1 = previous[size - 1];
    unsigned int last2 = previous[size - 2];
    unsigned int max = UINT_MAX / 2;
    if(last1 >= max){
        previous.push_back(UINT_MAX);
        return previous;
    }
    previous.push_back(last1 + last2);
    return previous;
}
