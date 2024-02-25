#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <array>
#include <tuple>

#include "../lib/array.hpp"


int main(int argc, char** argv) {

    std::tuple<std::vector<int>, int, int> tp>;
    //              data ^  init ^ result^

    std::cout << std::get<0>(tp) << std::endl;
    std::cout << std::get<1>(tp) << std::endl;
    std::cout << std::get<2>(tp) << std::endl;
    return 0;
}
