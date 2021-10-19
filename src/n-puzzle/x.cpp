#include "NPuzzleStatus.hpp"
#include <iostream>

int main() {
    std::vector<int> a = {3, 5, 7, 4, 1, 2, 9, 6, 8};
    std::for_each(begin(a), end(a), [](int &v){ v -= 1; });
    NPuzzleStatus<3> sa{a};
    std::cout << to_string(sa) << " Hash: " << sa.hash() << "\n"; // Should be 98884
    std::cout << to_string(sa.unhash(sa.hash())) << "\n";

    std::array<int, 9> b = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    NPuzzleStatus<3> sb{b};
    std::cout << to_string(sb) << " Hash: " << sb.hash() << "\n";
    std::cout << to_string(sb.unhash(sb.hash())) << "\n";


    auto c = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    NPuzzleStatus<3> sc{c};
    std::cout << to_string(sc) << " Hash: " << sc.hash() << "\n";
    std::cout << to_string(sc.unhash(sc.hash())) << "\n";

    std::cout << to_string(sc.unhash(1)) << "\n";
}
