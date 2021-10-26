#include "NPuzzleStatus.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <set>

template<typename StatusType>
class SearchMap {
    StatusType root;
    std::map<StatusType, StatusType> former_of; // parent status code
public:
    SearchMap(StatusType const & s) : root(s) {}
    auto depth_of(StatusType const & a) {
        auto current = a;
        auto cnt = 0;
        while (current != root) {
            auto parent = this->get_parent(current);
            cnt += 1;
            current = parent;
        }
        return cnt;
    }
    auto visited(StatusType const & s) const {
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

// 深度优先搜索

#include <functional>

template<typename StatusType>
auto DFS(StatusType const & init, StatusType const & target, int max_depth) {

    SearchMap<StatusType> map(init);

    std::function<void(StatusType const &, int)> foo;

    foo = [&](StatusType const & current, int depth) {
        if (current == target || depth == max_depth) return;
        for (auto const & s : current.possible_moves()) {
            if (map.visited(s)) { // 如果已经访问过
                if (depth < map.depth_of(s)) { // 如果现在的路径更近
                    map.add(s, current); // 更新该状态的前驱
                }
            } else { // 如果未访问过
                map.add(s, current); // 记录路径
                foo(s, depth + 1);
            }
        }
    };

    foo(init, 1);

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
    
    auto dfs_search_map = DFS<Status>(init, target, 10);

    auto dfs_found = dfs_search_map.visited(target);
    std::cout << "DFS found: " << std::boolalpha << dfs_found << "\n";
    
    if (dfs_found) {
        std::cout << "Backtrace path: \n" << back_trace(target, init, dfs_search_map);
    }
}
