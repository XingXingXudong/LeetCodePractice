#include <gtest/gtest.h>
#include <vector>

// iter 
std::vector<int> findFirstLast1(const std::vector<int>& inputs, int target) {
    if (inputs.empty()) {
        return std::vector<int>{-1, -1};
    }
    int left = 0, right = inputs.size();
    while(left <= right && inputs[left] < target) {
        ++left;
    }
    while(left <= right && inputs[right] > target) {
        --right;
    }
    if (left > right) {
        return std::vector<int>{-1, -1};
    } else {
        return std::vector<int>{left, right};
    }
}

int lower(const std::vector<int>& inputs, int target) {
    size_t left = 0, right = inputs.size(), mid=0;
    // if (inputs[left] > target) {  //不存在满足要求的最小界
    //     return -1;
    // }
    while(left < right) {    // 左闭右开的搜索
        mid = (left + right) / 2;
        if (inputs[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    } 
    // 退出循环的条件一定是left == right，需要注意的是，停止搜索的时候，可能是没有命中的
    // 如：inputs = {5, 7, 7, 10}, target = 8;
    if (left == inputs.size() || inputs[left] != target) {
        return -1;
    } else {
        return static_cast<int>(left);
    }
}

int upper(const std::vector<int>& inputs, int target) {
    if (inputs.empty()) {
        return -1;
    }
    size_t left = 0, right = inputs.size(), mid=0;
    // if (inputs[right-1] < target) {
    //     return -1;
    // }
    while(left < right) {    // 左闭右开的搜索
        mid = (left + right) / 2;
        if (inputs[mid] > target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    if (right - 1 >= 0 && inputs[right - 1] == target) {
        return right - 1;   // 左闭右开的搜索，取到右边，所以要减1
    } else {
        return -1;
    }

}

std::vector<int> findFirstLast(const std::vector<int>& inputs, int target) { 
    if (inputs.empty()) {
        return std::vector<int>{-1, -1};
    }
    int low_idx = lower(inputs, target);
    if (low_idx == -1) {
        return {-1, -1};
    }
    int up_idx = upper(inputs, target);
    return std::vector<int>{low_idx, up_idx};
}

/*
std::vector<int> findFirstLast(const std::vector<int>& inputs, int target) { 
    if (inputs.empty()) {
        return std::vector<int>{-1, -1};
    }
    int left = 0, right = inputs.size() - 1, mid = 0;
    while (left < right && inputs[left] < target) {
        mid = (left + right) / 2 ;
        if (inputs[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int tar_left = left;
    left = 0;
    right = inputs.size() - 1;
    while (left < right && inputs[right] > target) {
        mid = (left + right) / 2 + 1;
        if (inputs[mid] > target) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    if (tar_left <= right) {
        return std::vector<int>{tar_left, right};
    } else {
        return std::vector<int>{-1, -1};
    }
}

*/

TEST(findFirstLas, a) {
    auto inputs = std::vector<int>{5, 7, 7, 8, 8, 10};
    auto target = 8;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], 3);
    EXPECT_EQ(rtn[1], 4);
}

TEST(findFirstLas, b) {
    auto inputs = std::vector<int>{5, 7, 7, 8, 10};
    auto target = 8;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], 3);
    EXPECT_EQ(rtn[1], 3);
}

TEST(findFirstLas, c) {
    auto inputs = std::vector<int>{5, 7, 7, 7, 10};
    auto target = 8;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], -1);
    EXPECT_EQ(rtn[1], -1);
}

TEST(findFirstLas, d) {
    auto inputs = std::vector<int>{};
    auto target = 8;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], -1);
    EXPECT_EQ(rtn[1], -1);
}

TEST(findFirstLas, e) {
    auto inputs = std::vector<int>{5,5,5,5,5};
    auto target = 5;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], 0);
    EXPECT_EQ(rtn[1], 4);
}

TEST(findFirstLas, f) {
    auto inputs = std::vector<int>{5,5,5,5,5};
    auto target = 6;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], -1);
    EXPECT_EQ(rtn[1], -1);
}

TEST(findFirstLas, g) {
    auto inputs = std::vector<int>{5,5,5,5,5};
    auto target = 4;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], -1);
    EXPECT_EQ(rtn[1], -1);
}

TEST(findFirstlas, a1) {
    auto inputs = std::vector<int>{1};
    auto target = 1;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], 0);
    EXPECT_EQ(rtn[0], 0);
}

TEST(findFirstlas, a2) {
    auto inputs = std::vector<int>{1};
    auto target = 0;
    auto rtn = findFirstLast(inputs, target);
    EXPECT_EQ(rtn[0], -1);
    EXPECT_EQ(rtn[0], -1);
}

TEST(lower, a) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(lower(inputs, 2), 1);
}

TEST(lower, b) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(lower(inputs, 1), 0);
}

TEST(lower, c) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(lower(inputs, 3), 3);
}

TEST(lower, d) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(lower(inputs, 4), -1);
}

TEST(lower, e) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(lower(inputs, 0), -1);
}

TEST(upper, a) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(upper(inputs, 2), 2);
}

TEST(upper, b) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(upper(inputs, 1), 0);
}

TEST(upper, c) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(upper(inputs, 3), 3);
}

TEST(upper, d) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(upper(inputs, 4), -1);
}

TEST(upper, e) {
    auto inputs = std::vector<int>{1, 2, 2, 3};
    EXPECT_EQ(upper(inputs, 0), -1);
}

TEST(upper, f) {
    auto inputs = std::vector<int>{1};
    EXPECT_EQ(upper(inputs, 1), 0);
}

TEST(upper, g) {
    auto inputs = std::vector<int>{1};
    EXPECT_EQ(upper(inputs, 0), -1);
}

TEST(upper, c1) {
    auto inputs = std::vector<int>{5, 7, 7, 7, 10};
    auto target = 8;
    auto rtn = upper(inputs, target);
    EXPECT_EQ(rtn, -1);
}

TEST(lower, c1) {
    auto inputs = std::vector<int>{5, 7, 7, 7, 10};
    auto target = 8;
    auto rtn = lower(inputs, target);
    EXPECT_EQ(rtn, -1);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}