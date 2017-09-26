#include <vector>
#include <tuple>
#include <iostream>

std::tuple<int, int, int> // <left, right, max_sum>
max_crossing_subarray(std::vector<int> const& v, int left, int middle, int right) {
    int max_sum = v[middle];
    int max_left = middle;
    int max_right = middle;
    int cur_sum = max_sum;
    for(auto i = middle - 1; i >= left; --i) {
        cur_sum += v[i];
        if (max_sum < cur_sum) {
            max_sum = cur_sum;
            max_left = i;
        }
    }
    cur_sum = max_sum;
    for(auto j = middle + 1; j <= right; ++j) {
        cur_sum += v[j];
        if (max_sum < cur_sum) {
            max_sum = cur_sum;
            max_right = j;
        }
    }
    return std::make_tuple(max_left, max_right, max_sum);
}

std::tuple<int, int, int> // <left, right, max_sum>
max_subarray(std::vector<int> const& v, int left, int right) {
    if (left == right) {
        return std::make_tuple(left, right, v[left]);
    }
    auto middle = (left + right) / 2;
    auto r1 = max_subarray(v, left, middle);
    auto r2 = max_subarray(v, middle + 1, right);
    auto r3 = max_crossing_subarray(v, left, middle, right);

    if (std::get<2>(r1) >= std::get<2>(r2)) {
        return std::get<2>(r1) >= std::get<2>(r3) ? r1 : r3;
    } else if (std::get<2>(r2) >= std::get<2>(r3)) {
        return r2;
    } else {
        return r3;
    }
}

// nlogn
void f1(std::vector<int> const& v) {
    if (v.size()) {
        auto result = max_subarray(v, 0, v.size() - 1);
        auto left       = std::get<0>(result);
        auto right      = std::get<1>(result);
        auto max_sum    = std::get<2>(result);

        std::cout << "output_1 (max_sum == " << max_sum << "):" << std::endl;
        for(auto i = left; i <= right; ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
}

// n
void f2(std::vector<int> const& v) {
    int size = v.size();
    if (size) {
        int max_sum = v[0];
        int cur_sum = v[0];
        int max_left = 0;
        int cur_left = 0;
        int max_right = 0;

        for(int i = 1; i < size; ++i) {
            if (v[i] < 0 && max_sum < cur_sum) {
                max_sum = cur_sum;
                max_left = cur_left;
                max_right = i - 1;
            }
            if (cur_sum < 0) {
                cur_sum = 0;
                cur_left = i;
            }
            cur_sum += v[i];
        }

        if (max_sum < cur_sum) {
            max_sum = cur_sum;
            max_left = cur_left;
            max_right = size - 1;
        }

        std::cout << "output_2 (max_sum == " << max_sum << "):" << std::endl;
        for(auto i = max_left; i <= max_right; ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> v = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    std::cout << "input:" << std::endl;
    for(auto x: v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    f1(v);
    f2(v);
}
