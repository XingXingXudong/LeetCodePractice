// https://leetcode.com/problems/add-strings/

#include <gtest/gtest.h>
#include <algorithm>
#include <string>

std::string addString(std::string strA, std::string strB) {
    size_t lenA = strA.length();
    size_t lenB = strB.length();
    if (lenA > lenB) {
        std::swap(lenA, lenB);
        std::swap(strA, strB);
    }
    std::reverse(strA.begin(), strA.end());
    std::reverse(strB.begin(), strB.end());
    int addDigit = 0;
    std::string rtn = "";
    for (size_t i = 0; i < lenA; ++i) {
        int val = (strA[i] - '0') + (strB[i] - '0') + addDigit;
        rtn += std::to_string(val % 10);
        addDigit = val / 10;
    }
    for (size_t i = lenA; i < lenB; ++i) {
        int val = (strB[i] - '0') + addDigit;
        rtn += std::to_string(val % 10);
        addDigit = val / 10;
    }
    if (addDigit > 0) {
        rtn += std::to_string(addDigit);
    }
    std::reverse(rtn.begin(), rtn.end());
    return rtn;
}

TEST(addString, a1) {
    std::string strA = "12";
    std::string strB = "12";
    std::string sum = "24";
    EXPECT_EQ(addString(strA, strB), sum);
}

TEST(addString, a) {
    std::string strA = "123";
    std::string strB = "99";
    std::string sum = "222";
    EXPECT_EQ(addString(strA, strB), sum);
}

TEST(addString, b) {
    std::string strA = "123";
    std::string strB = "";
    std::string sum = "123";
    EXPECT_EQ(addString(strA, strB), sum);
}

TEST(addString, c) {
    std::string strA = "99";
    std::string strB = "99";
    std::string sum = "198";
    EXPECT_EQ(addString(strA, strB), sum);
}

TEST(addString, d) {
    std::string strA(5099, '9');
    std::string strB(5099, '9');
    std::string sum("1");
    sum += std::string(5098, '9');
    sum += "8";
    EXPECT_EQ(addString(strA, strB), sum);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}