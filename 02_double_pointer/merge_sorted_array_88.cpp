#include <gtest/gtest.h>
#include <vector>
#include <iostream>


void merge_sorted_array(std::vector<int>& arr_a, size_t size_a, const std::vector<int>& arr_b, size_t size_b) {
    size_t merge_p = size_a + size_b;
    while(size_a > 0 && merge_p > size_a) {
        // if (arr_a[size_a - 1] >= arr_b[size_b - 1]) {
        //     arr_a[--merge_p] = arr_a[--size_a];
        // } else {
        //     arr_a[--merge_p] = arr_b[--size_b];
        // }
        arr_a[--merge_p] = arr_a[size_a - 1] >= arr_b[size_b - 1] ? arr_a[--size_a] : arr_b[--size_b];
    }
    while(size_b > 0) {
        arr_a[--merge_p] = arr_b[--size_b];
    }
}

template<typename T>
bool is_equal(const std::vector<T>& arr1, const std::vector<T>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }
    for (size_t i = 0; i < arr1.size(); ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

TEST(is_equal, a) {
    auto a = std::vector<int> {1, 2, 3};
    auto b = std::vector<int> {1, 2, 3};
    // EXPECT_TRUE(is_equal<int>(a, b));
    EXPECT_TRUE(is_equal(a, b));
}

TEST(is_equal, b) {
    auto a = std::vector<int> {1, 2};
    auto b = std::vector<int> {1, 2, 3};
    // EXPECT_FALSE(is_equal<int>(a, b));
    EXPECT_FALSE(is_equal(a, b));
}

TEST(merge_sort, a) {
    auto array_a = std::vector<int>{1, 2, 3, 0, 0, 0};
    size_t size_a = 3;
    auto array_b = std::vector<int>{2,4,5};
    size_t size_b = 3;
    auto expect_out = std::vector<int>{1, 2, 2, 3, 4, 5};
    merge_sorted_array(array_a, size_a, array_b, size_b);
    EXPECT_TRUE(is_equal(array_a, expect_out));
}

TEST(merge_sort, b) {
    auto array_a = std::vector<int>{0, 0, 0};
    size_t size_a = 0;
    auto array_b = std::vector<int>{2,4,5};
    size_t size_b = 3;
    auto expect_out = std::vector<int>{2, 4, 5};
    merge_sorted_array(array_a, size_a, array_b, size_b);
    EXPECT_TRUE(is_equal(array_a, expect_out));
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}