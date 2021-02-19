// https://leetcode.com/problems/max-points-on-a-line/

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
#include <algorithm>


int maxPoints(const std::vector<std::vector<int>>& points) {
    auto map = std::unordered_map<double, int>{};   // 斜率，点的个数
    int max_count = 0, same = 0, same_y = 0, same_x = 0;
    for (int i = 0; i < points.size(); ++i) {
        same = 1; 
        same_y = 1;
        same_x = 1;
        for (int j = i + 1; j < points.size(); ++j) {
            if (points[i][1] == points[j][1]) {
                ++same_y;
                if (points[i][0] == points[j][0]) {
                    ++same;
                }
            } else if (points[i][0] == points[j][0]) {
                ++same_x;
            } else {
                double dx = points[i][0] - points[j][0];
                double dy = points[i][1] - points[j][1];
                ++map[dy / dx];
            }
        }
        max_count = std::max(max_count, same_y);     // 平行于x轴的直线上的点
        max_count = std::max(max_count, same_x);     // 平行于x轴的直线上的点
        for (auto item: map) {
            max_count = std::max(max_count, same + item.second);
        }
        map.clear();
    }
    return max_count;
}

TEST(maxPoints, a) {
    auto points = std::vector<std::vector<int>>{{1,1},{2,2},{3,3}};
    int output = 3;
    EXPECT_EQ(maxPoints(points), output);
}

TEST(maxPoints, b) {
    auto points = std::vector<std::vector<int>>{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    int output = 4;
    EXPECT_EQ(maxPoints(points), output);
}

TEST(maxPoints, c) {
    auto points = std::vector<std::vector<int>>{{4,0},{4,-1},{4,5}};
    int output = 3;
    EXPECT_EQ(maxPoints(points), output);
}

TEST(maxPoints, d) {
    auto points = std::vector<std::vector<int>>{{0, 4},{-1, 4}, {5, 4}, {1, 1}};
    int output = 3;
    EXPECT_EQ(maxPoints(points), output);
}


TEST(maxPoints, e) {
    auto points = std::vector<std::vector<int>>{{0,0},{94911151,94911150},{94911152,94911151}};
    int output = 2;
    EXPECT_EQ(maxPoints(points), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}