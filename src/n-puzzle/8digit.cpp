#include "NPuzzleStatus.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <set>

template<typename StatusType>
class SearchMap {
    std::map<StatusType, StatusType> former_of; // parent status code
public:
    SearchMap() {}
    auto visited(StatusType const & s) {
        return former_of.find(s) != former_of.end();
    }
    auto add(StatusType const & s, StatusType const & parent) {
        former_of[s] = parent;
    }
    auto get_parent(StatusType const & s) {
        if (former_of.find(s) != former_of.end())
            return former_of[s];
        else return StatusType({-1});
    }
};

// 宽度优先搜索

template<typename StatusType>
auto BFS(StatusType const & init, StatusType const & target) {
    std::queue<StatusType> open;
    SearchMap<StatusType> map;
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
    return map;
}

int main() {
    using Status = NPuzzleStatus<3>;
    Status init({
        2,8,3,
        1,0,4,
        7,6,5});
    Status target({
        1,2,3,
        8,0,4,
        7,6,5});
    std::cout << "Initial status: \n" << to_string(init) << "\n";
    std::cout << "Target status: \n" << to_string(target) << "\n";
    
    auto bfs_search_map = BFS<Status>(init, target);
    
    std::vector<Status> v;
    auto current = target;
    v.push_back(current);
    while (current != init) {
        auto parent = bfs_search_map.get_parent(current);
        v.push_back(parent);
        current = parent;
    }

    std::cout << "Backtrace path: \n" << v;
}
