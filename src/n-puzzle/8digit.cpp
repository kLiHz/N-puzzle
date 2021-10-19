#include "NPuzzleStatus.hpp"
#include <iostream>
#include <queue>
#include <set>

template<int N>
class NPuzzleSearchMap {
    std::vector<int> former_of; // parent status code
public:
    NPuzzleSearchMap() {
        former_of.resize(fact(N*N));
        for (auto & v : former_of) { v = -1; }
    }
    auto visited(NPuzzleStatus<N> const & s) {
        return former_of[s.hash()] != -1;
    }
    auto add(NPuzzleStatus<N> const & s, NPuzzleStatus<N> const & parent) {
        former_of[s.hash()] = parent.hash();
    }
    auto get_parent(NPuzzleStatus<N> const & s) {
        if (former_of[s.hash()] != -1)
            return NPuzzleStatus<N>::unhash(former_of[s.hash()]);
        else return NPuzzleStatus<N>({-1});
    }
};

// 宽度优先搜索

template<int N>
auto BFS(NPuzzleStatus<N> const & init, NPuzzleStatus<N> const & target) {
    std::queue<NPuzzleStatus<N>> open;
    NPuzzleSearchMap<N> map;
    open.push(init);
    while (!open.empty()) {
        auto current = open.front();
        if (current == target) { break; }
        for (auto const & s : current.possible_moves()) {
            if (map.visited(s)) continue;
            open.push(s);
            map.add(s, current);
        }
        open.pop();
    }
    std::vector<NPuzzleStatus<N>> v;
    auto current = open.front();
    v.push_back(current);
    while (current != init) {
        auto parent = map.get_parent(current);
        v.push_back(parent);
        current = parent;
    }
    return v;
}

int main() {
    NPuzzleStatus<3> init({
        2,8,3,
        1,0,4,
        7,6,5});
    NPuzzleStatus<3> target({
        1,2,3,
        8,0,4,
        7,6,5});
    std::cout << "Initial status: \n" << to_string(init) << "\n";
    std::cout << "Target status: \n" << to_string(target) << "\n";
    std::cout << "Backtrace path: \n";
    std::cout << BFS(init, target);
}
