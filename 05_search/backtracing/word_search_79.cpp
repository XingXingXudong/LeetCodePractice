// https://leetcode.com/problems/word-search/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <string>

template<typename T>
void print(const std::vector<std::vector<T>>& arr) {
    std::cout << "[";
    bool flag = false;
    for (const auto& row: arr) {
        for (const auto& x: row) {
            if (flag) {
                std::cout << " " << x;
            } else {
                std::cout << x << " ";
            }
        }
        std::cout << std::endl;
        flag = true;
    }
    std::cout << "]" << std::endl;
}

auto directions = std::vector<int>{-1, 0, 1, 0, -1};

void word_search_(bool& rtn, std::vector<std::vector<bool>>& has_trans, std::vector<std::vector<char>>& board, 
    std::string& word, int i, int j, int k) {
    std::cout << "i=" << i << ", j=" << j << ", k=" << k << std::endl;
    print(has_trans);
    std::cout << "==================================================" << std::endl;
    if (rtn || i < 0 || j < 0 || i >= (int)board.size() || j >= (int)board[0].size() || k < 0 || k >= (int)word.length() || has_trans[i][j] == true) {
        return;
    }
    if (word[k] == board[i][j]) {
        if (k == (int)(word.length() - 1)) {
            rtn = true;
            return;
        }
        // 注意这里的k，以及与其关联的注释掉的三行代码，这里的k虽然也是与递归会回溯有关的状态，可以先增1，然后回溯时再自减，
        // 相当与直接传递k+1，调用完毕后，k的状态没有改变，相当与完成了自增，回溯，自减的操作
        // ++k;
        has_trans[i][j] = true;
        for (size_t idx = 0; idx < 4; ++idx) {
            // word_search_(rtn, has_trans, board, word, i + directions[idx], j + directions[idx + 1], k);
            word_search_(rtn, has_trans, board, word, i + directions[idx], j + directions[idx + 1], k + 1);
        }
        has_trans[i][j] = false;
        // --k;
    }
}

bool word_search(std::vector<std::vector<char>>& board, std::string& word) {
    if (board.empty() || board[0].empty()) {
        return false;
    }
    int k = 0;
    bool rtn = false;
    auto has_trans = std::vector<std::vector<bool>>(board.size(), std::vector<bool>(board[0].size(), false));
    print(has_trans);
    for (int i = 0; i < (int)board.size(); ++i) {
        for (int j = 0; j < (int)board[i].size(); ++j) {
            rtn = false;
            k = 0;
            word_search_(rtn, has_trans, board, word, i, j, k);
            if (rtn) {
                return rtn;
            }
        }
    }
    return rtn;
}

// void backtracing(int i, int j, std::vector<std::vector<char>>& board, std::string& word, bool& find, std::vector<std::vector<bool>>& visited, int pos) {
//     if (i < 0 || j < 0 || i >= board.size() || j >= board[i].size();
// }

TEST(word_search, a) {
    auto board = std::vector<std::vector<char>> {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    auto word = std::string("ABCCED");
    EXPECT_TRUE(word_search(board, word));
}

TEST(word_search, b) {
    auto board = std::vector<std::vector<char>> {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    auto word = std::string("SEE");
    EXPECT_TRUE(word_search(board, word));
}

TEST(word_search, c) {
    auto board = std::vector<std::vector<char>> {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    auto word = std::string("ABCD");
    EXPECT_FALSE(word_search(board, word));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
