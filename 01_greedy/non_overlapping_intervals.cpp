#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void print_intervals(const vector<vector<int>>& intervals) {
    cout << "{" << endl;
    for (const auto& interval: intervals) {
        cout << "[" << interval[0] << ", " << interval[1] << "]" << endl;
    }
    cout << "}" << endl;
}

size_t no_overlapping(const vector<vector<int>>& intervals) {
    if (intervals.size() < 2) {
        return 0;
    }

    auto intervals_copy = vector<vector<int>>(intervals);
    sort(intervals_copy.begin(), intervals_copy.end(), 
         [](const vector<int>& interval_a, const vector<int>& interval_b){
             return interval_a[1] < interval_b[1];
         }
    );

    print_intervals(intervals_copy);

    size_t idx = 0;
    size_t count = 0;
    for (size_t i = 1; i < intervals_copy.size(); ++i) {
        if (intervals_copy[idx][1] > intervals_copy[i][0]) {
            ++count;
        } else {
            idx = i;
        }
    }

    return count;
}


TEST(baidu, no_overlapping1) {
    auto inputs = vector<vector<int>>{{2, 4}, {1, 2}, {1, 3}};
    EXPECT_EQ(no_overlapping(inputs), 1);
}

TEST(baidu, no_overlapping2) {
    auto inputs = vector<vector<int>>{};
    EXPECT_EQ(no_overlapping(inputs), 0);
}

TEST(baidu, no_overlapping3) {
    auto inputs = vector<vector<int>>{{1, 2}};
    EXPECT_EQ(no_overlapping(inputs), 0);
}

TEST(baidu, no_overlapping4) {
    auto inputs = vector<vector<int>>{{1, 3}, {1, 2}, {2, 4}, {2, 3}, {3, 4}};
    EXPECT_EQ(no_overlapping(inputs), 2);
}

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}