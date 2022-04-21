#include "Header.h"
#include <vector>
int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}
