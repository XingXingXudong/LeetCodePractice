#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>

std::string min_sub_string(const std::string& S, const std::string& T) {
    if (S.empty() || T.empty()) {
        return std::string{};
    }
    // S中找到全部T所需要的字符数，考虑到重复问题，一个字符可能被需要多次；
    auto need_char_nums = std::vector<int>(128, 0);
    // 标识T中出现的字符
    auto is_in_sub = std::vector<bool>(128, false);
    // 统计T中字符的情况
    for(const auto& c: T) {
        is_in_sub[int(c)] = true;    // 标识字符c在T中出现
        ++need_char_nums[int(c)];    // 记录字符c在T中出现的次数
    }
    size_t l = 0, count = 0; 
    size_t min_l = 0, min_r = 0;
    size_t min_len = S.size() + 1;
    for (size_t r = 0; r < S.size(); ++r) {
        if (is_in_sub[S[r]]) {                          // S[r]是T中出现的字符
            if (--need_char_nums[S[r]] >= 0) {          // 找到了一个S[r]，被需要的次数减小，减小以后，被需要的次数>=0，
                ++count;                                // 说明确实找到了需要的字符，count记录增1，用于判断是否找到了所有T中的字符
            }   // 注意：每次执行这个if时，先会更新need_char_nums[S[r]]，该值小于零时，其绝对值表示，在S中找到了多余的S[r]字符，如S=AAAAAABC, T=ABC，S中前面的A是多余数目的A字符

            while(count == T.size()) {   // need_char_nums的计数机制，保证该条件成立时，l,r窗口中已经包括了T所需的字符，进一步调整窗口，获取最小长度
                if (r - l + 1 < min_len) {
                    min_l = l;
                    min_len = r - l + 1;
                }
                if (is_in_sub[S[l]] && ++need_char_nums[S[l]] > 0) {  // 如果S[l]是被需要的字符，l增1，需要增加S[l]被需要的次数，如果被需要的次数大于零，则破坏了找的的子串，
                    --count;                                          // 即count要减小，导致退出while，并继续向右搜索。
                }
                ++l;
            }
        }
    }
    return min_len > S.size() ? "" : S.substr(min_l, min_len);
}

TEST(min, a) {
    auto S = "ADOBECODEBANC";
    auto T = "ABC";
    auto rtn = min_sub_string(S, T);
    EXPECT_EQ(rtn, "BANC");
}

TEST(min, b) {
    auto S = "";
    auto T = "ABC";
    auto rtn = min_sub_string(S, T);
    EXPECT_EQ(rtn, "");
}

TEST(min, c) {
    auto S = "ADOBECODEBANC";
    auto T = "";
    auto rtn = min_sub_string(S, T);
    EXPECT_EQ(rtn, "");
}

TEST(min, d) {
    auto S = "ABC";
    auto T = "ADOBECODEBANC";
    auto rtn = min_sub_string(S, T);
    EXPECT_EQ(rtn, "");
}

TEST(min, e) {
    auto S = "ABC";
    auto T = "ABC";
    auto rtn = min_sub_string(S, T);
    EXPECT_EQ(rtn, "ABC");
}

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}