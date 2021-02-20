// https://leetcode.com/problems/max-points-on-a-line/

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>

std::pair<int, int> gcd(int a, int b) {
    int s = 0, r = 0;
    s = a / b;
    r = a - s * b;
    return {s, r};
}

int gcd1(int a, int b) {
    while (b) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

struct pair_hash{
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

int maxPoints(const std::vector<std::vector<int>>& points) {
    // auto map = std::unordered_map<double, int>{};   // 斜率，点的个数
    // auto map = std::unordered_map<std::pair<int, int>, int, pair_hash>{};   // 斜率，点的个数
    auto map = std::unordered_map<std::string, int>{};   // 斜率，点的个数
    int max_count = 0, same = 0, same_y = 0, same_x = 0;
    for (int i = 0; i < (int)points.size(); ++i) {
        same = 1; 
        same_y = 1;
        same_x = 1;
        for (int j = i + 1; j < (int)points.size(); ++j) {
            if (points[i][1] == points[j][1]) {
                ++same_y;
                if (points[i][0] == points[j][0]) {
                    ++same;
                }
            } else if (points[i][0] == points[j][0]) {
                ++same_x;
            } else {
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                // ++map[dy / dx];
                // ++map[gcd(dy, dx)];
                int g = gcd1(dx, dy);
                ++map[std::to_string(dx / g) + "_" + std::to_string(dy / g)];
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

TEST(maxPoints, f) {
    auto points = std::vector<std::vector<int>>{{3,1},{12,3},{3,1},{-6,-1}};
    int output = 4;
    EXPECT_EQ(maxPoints(points), output);
}


TEST(maxPoints, e) {
    auto points = std::vector<std::vector<int>>{{0,0},{94911151,94911150},{94911152,94911151}};
    // auto points = std::vector<std::vector<int>>{{94911150,94911150},{94911151,94911150},{94911152,94911151}};
    // std::cout << "94911151 / 94911150 = " << 94911151.0 / 94911150.0 << std::endl;
    // std::cout << "94911152 / 94911151 = " << 94911152.0 / 94911151.0 << std::endl;
    // auto sr = gcd(94911152, 94911151);
    // std::cout << "first: " << sr.first << ", second: " << sr.second << std::endl;
    // sr = gcd(94911151, 94911150);
    // std::cout << "first: " << sr.first << ", second: " << sr.second << std::endl;
    int output = 2;
    EXPECT_EQ(maxPoints(points), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}