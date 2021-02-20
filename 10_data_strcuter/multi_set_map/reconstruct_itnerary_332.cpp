// https://leetcode.com/problems/reconstruct-itinerary/
#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <set>
#include <stack>
#include <algorithm>

std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets) {
    auto ans = std::vector<std::string>{};
    
    if (tickets.empty()) {
        return ans;
    }
    std::unordered_map<std::string, std::multiset<std::string>> hash;
    for (const auto& ticket: tickets) {
        hash[ticket[0]].insert(ticket[1]);
    }
    std::stack<std::string> s;
    s.push("JFK");
    while (!s.empty()) {
        std::string next = s.top();
        if (hash[next].empty()) {
            ans.push_back(next);
            s.pop();
        } else {
            s.push(*hash[next].begin());
            hash[next].erase(hash[next].begin());
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

TEST(findItinerary, a) {
    auto inputs = std::vector<std::vector<std::string>>{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    auto output = std::vector<std::string>{"JFK", "MUC", "LHR", "SFO", "SJC"};
    EXPECT_TRUE(output == findItinerary(inputs));

}
TEST(findItinerary, b) {
    auto inputs = std::vector<std::vector<std::string>>{{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    auto output = std::vector<std::string>{"JFK","ATL","JFK","SFO","ATL","SFO"};
    EXPECT_TRUE(output == findItinerary(inputs));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}