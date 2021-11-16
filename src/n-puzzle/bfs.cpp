#include <iostream>
#include <queue>
#include "NPuzzleStatus.hpp"
#include "SearchMap.hpp"

// 宽度优先搜索

template<typename StatusType>
auto BFS(StatusType const & init, StatusType const & target) {
    std::queue<StatusType> open;
    SearchMap<StatusType> map(init);
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
    
    auto back_trace = [](Status const & t, Status const & s, SearchMap<Status> & m) {
        std::vector<Status> v;
        auto current = t;
        v.push_back(current);
        while (current != s) {
            auto parent = m.get_parent(current);
            v.push_back(parent);
            current = parent;
        }
        return v;
    };

    auto bfs_search_map = BFS<Status>(init, target);

    auto bfs_found = bfs_search_map.visited(target);
    std::cout << "BFS found: " << std::boolalpha << bfs_found << "\n";

    if (bfs_found) {
        std::cout << "Backtrace path: \n" << back_trace(target, init, bfs_search_map);
    }
}
