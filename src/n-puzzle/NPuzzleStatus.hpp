
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <algorithm>

inline constexpr int fact(int n) {
    if (n == 0 || n == 1) return 1;
    else return n * fact(n - 1);
};

template<int N = 3>
class NPuzzleStatus {
private:
    int data[N*N];
public:
    NPuzzleStatus() {
        for (int i = 0; i < N*N; ++i) {
            data[i] = 0;
        }
    };
    NPuzzleStatus(std::initializer_list<int> l) {
        int i = 0;
        for (auto const & v : l) {
            data[i] = v;
            ++i;
            if (i == N*N) break;
        }
    }
    NPuzzleStatus(std::vector<int> l) {
        int i = 0;
        for (auto const & v : l) {
            data[i] = v;
            ++i;
            if (i == N*N) break;
        }
    }
    NPuzzleStatus(std::array<int, N*N> const & a) {
        for (int i = 0; i < N*N; ++i) { data[i] = a[i]; }
    }
    NPuzzleStatus(int d[N*N]) {
        for (int i = 0; i < N*N; ++i) { data[i] = d[i]; }
    }
    NPuzzleStatus(NPuzzleStatus const & other) {
        for (int i = 0; i < N*N; ++i) { data[i] = other.data[i]; }
    }
    NPuzzleStatus & operator=(NPuzzleStatus const & other) {
        for (int i = 0; i < N*N; ++i) { data[i] = other.data[i]; }
        return *this;
    }
    auto possible_moves() const {
        auto blank_pos = 0;
        for (auto c : data) {
            if (c == 0) break;
            blank_pos++;
        }
        int d[N*N];
        for (int i = 0; i < N*N; ++i) { d[i] = this->data[i]; }
        std::vector<NPuzzleStatus<N>> s;
        if (blank_pos + N <= N * N) { // 能够向上移动
            std::swap(d[blank_pos], d[blank_pos + N]);
            s.push_back({d});
            std::swap(d[blank_pos], d[blank_pos + N]);
        }
        if (blank_pos - N >= 0) { // 能够向下移动
            std::swap(d[blank_pos], d[blank_pos - N]);
            s.push_back({d});
            std::swap(d[blank_pos], d[blank_pos - N]);
        }
        if (blank_pos % N != 0) { // 能够向左移动
            std::swap(d[blank_pos], d[blank_pos - 1]);
            s.push_back({d});
            std::swap(d[blank_pos], d[blank_pos - 1]);
        }
        if (blank_pos % N != N - 1) { // 能够向右移动
            std::swap(d[blank_pos], d[blank_pos + 1]);
            s.push_back({d});
            std::swap(d[blank_pos], d[blank_pos + 1]);
        }
        return s;
    }
    friend std::string to_string(const NPuzzleStatus<N> & s) {
        std::string out;
        // 3 x 3: "[{} {} {} \n {} {} {} \n {} {} {}]\n"
        for (int i = 0; i < N*N; ++i) {
            out += " " + std::to_string(s.data[i]);
            if ((i + 1) % 3 == 0) out += " \n";
        }
        out.pop_back();
        *(begin(out)) = '[';
        *(rbegin(out)) = ']';
        return out;
    }
    bool operator== (const NPuzzleStatus<N> & other) const {
        for (int i = 0; i < N*N; ++i) {
            if (this->data[i] != other.data[i]) return false;
        }
        return true;
    }
    bool operator!= (const NPuzzleStatus<N> & other) const { return !(*this == other); }
    bool operator< (const NPuzzleStatus<N> & other) const {
        for (int i = 0; i < N*N; ++i) {
            if (this->data[i] != other.data[i]) 
                return this->data[i] < other.data[i];
        }
        return false;
    }
    auto hash() const {
        // Assume that data is an arrangement of natural numbers from 0 to N*N
        std::array<bool, N*N> appeared;
        appeared.fill(false);
        auto X = 0;
        auto m = N*N - 1;
        for (auto c : data) {
            appeared[c] = true;
            auto cnt = 0;
            for (auto i = 0; i < c; i++) {
                if (!appeared[i]) cnt += 1;
            }
            X += cnt * fact(m);
            m--;
        }
        return X;
    }
    static auto unhash(int X) {
        std::array<bool, N*N> appeared;
        appeared.fill(false);
        std::array<int, N*N> nums;
        for (int i = 0; i < N * N; ++i) {
            auto m = N * N - i - 1;
            auto t = X / fact(m);
            for (int j = 0; j <= t; j++) {
                if (appeared[j]) t++;
            }
            appeared[t] = true;
            nums[i] = t;
            if (fact(m) != 0) X %= fact(m);
        }
        return NPuzzleStatus<N>{nums};
    }
};

#include <sstream>
#include <iosfwd>
#include <algorithm>

template<int N>
inline std::ostream& operator<< (std::ostream& os, const std::vector<NPuzzleStatus<N>> & v) {
    std::array<std::string, 3> lines;
    std::for_each(begin(v), end(v), [&](auto const & s){
        std::istringstream ss(to_string(s));
        for (auto & l : lines) {
            std::string t;
            std::getline(ss, t); 
            l += t + " ";
        }
    });
    for (auto const & l : lines) { os << l << "\n"; }
    return os;
}
