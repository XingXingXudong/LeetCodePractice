//
// 常见排序算法的基本实现
//

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> rand_nums(size_t size) {
    srand(time(nullptr));
    auto rtn = vector<int>{};
    while(--size > 0) {
        rtn.push_back(rand() / ((RAND_MAX + 1u) / size));
    }
    return rtn;
}

bool is_ordered(const vector<int>& nums) {
    auto rtn = true;
    size_t p = 0;
    while (p < nums.size() - 1) {
        rtn = rtn && nums[p] <= nums[p + 1];
        ++p;
    }
    return rtn;
}

void print_num(const vector<int>& nums) {
    for (auto x: nums) {
        std::cout << x << " "; 
    }
    std::cout << std::endl;
}

// 三数取中
void thr_mid_quick_sort_(vector<int>& nums, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t mid = (left + right) / 2;
    if (nums[left] > nums[mid]) {
        swap(nums[left], nums[mid]);
    }
    if (nums[mid] > nums[right]) {
        swap(nums[mid], nums[right]);
    }
    if (nums[left] > nums[mid]) {
        swap(nums[left], nums[mid]);
    }
    swap(nums[mid], nums[right - 1]);

    size_t i = left, j = right-1;
    while (true) {
        while (i < right && nums[++i] < nums[right - 1]){}
        while (j > left && nums[--j] > nums[right - 1]) {}
        if (i < j) {
            swap(nums[i], nums[j]);
        } else {
            break;
        }
    }
    if (i < right) {
        swap(nums[i], nums[right - 1]);
    }
    if (left < i - 1) {
        thr_mid_quick_sort_(nums, left, i - 1);
    }
    if (i + 1 < right) {
        thr_mid_quick_sort_(nums, i + 1, right);
    }
}

void thr_mid_quick_sort(vector<int>& nums) {
    size_t left = 0, right = nums.size() - 1;
    thr_mid_quick_sort_(nums, left, right);
}

void quick_sort_(vector<int>& nums, size_t left, size_t right) {
    // std::cout << "left: " << left << ", right: " << right << std::endl;
    // print_num("input", nums);
    if (left >= right) {
        return; 
    }
    // 使用第一个位置作为pivato
    size_t i = left + 1, j = right;
    while(i < j) {
        // std::cout << "i: " << i << ", j: " << j << std::endl;
        while(j > i && nums[j] > nums[left]) {
            --j;
        }
        while(i < j && nums[i] <= nums[left]) {
            ++i;
        }
        // std::cout << "i: " << i << ", j: " << j << std::endl;
        if (i < j) {
            swap(nums[i], nums[j]);
        } else {
            break;
        }
        // print_num("swap ", nums);
    }
    if (nums[left] > nums[i]) {
        swap(nums[left], nums[i]);
    }
    // print_num("parti", nums);
    quick_sort_(nums, left, i - 1);
    quick_sort_(nums, i, right);
}

void quick_sort(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    quick_sort_(nums, left, right);
}


int partition(vector<int>& nums, int left, int right) {
    int pivot_key = nums[left];
    while(left < right) {
        while(left < right && nums[right] >= pivot_key) {
            --right;
        }
        nums[left] = nums[right]; // 只需赋值即可，无需交换
        while(left < right && nums[left] <= pivot_key) {
            ++left;
        }
        nums[right] = nums[left]; // 只需赋值即可，无需交换
    }
    nums[left] = pivot_key;
    return left;
}

void quick_sort_std_(vector<int>& nums, int left, int right) {
    if (left < right) {
        int pivot = partition(nums, left, right);
        // 下面两行代码中，如果left, right, pivot使用sizt_t的话，pivot - 1会发生下溢出，
        // 从而使得left < right不成立，导致死循环、越界访问
        // 使用size_t类型作为索引指针，一定要注意--/左移操作导致的下溢出，使得，>0等判断失效；
        quick_sort_std_(nums, left, pivot - 1);  
        quick_sort_std_(nums, pivot + 1, right);
    }
}

// 标准版快排
void quick_sort_std(vector<int>& nums) {
    print_num(nums);
    quick_sort_std_(nums, 0, nums.size() - 1);
    print_num(nums);
}

/**
 * 插入排序：将一个记录插入到有序表中，从而得到一个新的，记录数增一的有序表；
 * 复杂度为O(n^2)
 * 改进方法：
 *  1，折半查找，插入排序，减少了比较次数，没有减少移动次数，复杂度没有变化；
 *  2，2-路插入排序，需要辅助空间;
 */
void insert_sort(vector<int>& nums) {
    if (nums.size() < 2) {
        return;
    }
    for (size_t i = 1; i < nums.size(); ++i) {
        // print_num(nums);
        int temp = nums[i];
        size_t j = i;
        for (; j > 0 && nums[j - 1] > temp; --j) {
            nums[j] = nums[j - 1];
        }
        nums[j] = temp;
    }
    // print_num(nums);
}

/**
 * 简单选择排序: 通过n-i次关键字比较，从n-i+1个记录中选出关键字最小的记录，并和第i(1<=i<=n)个记录交换之。
 */

size_t min_index(const vector<int>& nums, size_t start) {
    size_t idx = start;
    while (start < nums.size() - 1) {
        if (nums[++start] < nums[idx]) {
            idx = start;
        }
    }
    return idx;
}

void select_sort(vector<int>& nums) {
    size_t min_idx = 0;
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        min_idx = min_index(nums, i);
        if (min_idx != i) {
            swap(nums[i], nums[min_idx]);
        }
    }
}

TEST(is_ordered, a) {
    auto input1 = vector<int>{1, 2, 3, 4};
    EXPECT_TRUE(is_ordered(input1));
    auto input2 = vector<int>{1, 3, 2, 4};
    EXPECT_FALSE(is_ordered(input2));
}

TEST(thr_mid_quick_sort, a) {
    auto input = vector<int>{6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    thr_mid_quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(thr_mid_quick_sort, b) {
    auto input = vector<int>{6, 1};
    thr_mid_quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(thr_mid_quick_sort, c) {
    auto input = vector<int>{6};
    thr_mid_quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(thr_mid_quick_sort, d) {
    auto input = vector<int>{4, 3, 1, 0, 2, 1, 1, 1, 0};
    thr_mid_quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(thr_mid_quick_sort, e) {
    auto input = vector<int> {0, 4, 5, 3, 1, 3, 0, 0, 0};
    thr_mid_quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}

TEST(quick_sort, a) {
    auto input = vector<int>{6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort, b) {
    auto input = vector<int>{6, 1};
    quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort, c) {
    auto input = vector<int>{6};
    quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort, d) {
    auto input = vector<int>{4, 3, 1, 0, 2, 1, 1, 1, 0};
    quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort, e) {
    auto input = vector<int> {0, 4, 5, 3, 1, 3, 0, 0, 0};
    quick_sort(input);
    EXPECT_TRUE(is_ordered(input));
}

TEST(insert_sort, a) {
    auto input = vector<int>{6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    insert_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(insert_sort, b) {
    auto input = vector<int>{6, 1};
    insert_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(insert_sort, c) {
    auto input = vector<int>{6};
    insert_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(insert_sort, d) {
    auto input = vector<int>{4, 3, 1, 0, 2, 1, 1, 1, 0};
    insert_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(insert_sort, e) {
    auto input = vector<int> {0, 4, 5, 3, 1, 3, 0, 0, 0};
    insert_sort(input);
    EXPECT_TRUE(is_ordered(input));
}

TEST(quick_sort_std, a) {
    auto input = vector<int>{6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    quick_sort_std(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort_std, b) {
    auto input = vector<int>{6, 1};
    quick_sort_std(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort_std, c) {
    auto input = vector<int>{6};
    quick_sort_std(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort_std, d) {
    auto input = vector<int>{4, 3, 1, 0, 2, 1, 1, 1, 0};
    quick_sort_std(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(quick_sort_std, e) {
    auto input = vector<int> {0, 4, 5, 3, 1, 3, 0, 0, 0};
    quick_sort_std(input);
    EXPECT_TRUE(is_ordered(input));
}

TEST(select_sort, a) {
    auto input = vector<int>{6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    print_num(input);
    select_sort(input);
    print_num(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(select_sort, b) {
    auto input = vector<int>{6, 1};
    print_num(input);
    select_sort(input);
    print_num(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(select_sort, c) {
    auto input = vector<int>{6};
    select_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(select_sort, d) {
    auto input = vector<int>{4, 3, 1, 0, 2, 1, 1, 1, 0};
    select_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
TEST(select_sort, e) {
    auto input = vector<int> {0, 4, 5, 3, 1, 3, 0, 0, 0};
    select_sort(input);
    EXPECT_TRUE(is_ordered(input));
}
//效率测试
/*
TEST(thr_mid_quick_sort, A) {
    for (auto& x: vector<int>{1000, 100000, 50000, 500000}) {
        auto input = rand_nums(x);
        thr_mid_quick_sort(input);
        EXPECT_TRUE(is_ordered(input));
    }
}

TEST(quick_sort, A) {
    for (auto& x: vector<int>{10, 100000, 50000, 500000}) {
    // for (auto& x: vector<int>{10, 10, 10, 10}) {
        auto input = rand_nums(x);
        // print_num("input", input);
        quick_sort(input);
        // print_num("input", input);
        EXPECT_TRUE(is_ordered(input));
    }
}
*/

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}