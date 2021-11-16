#include <map>

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
