#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int assign_cookies(const vector<int>& children, const vector<int>& cookies) {
    if (children.size() == 0 || cookies.size() == 0) {
        return 0;
    }

    int rtn = 0;
    auto children_ = vector<int>(children);
    auto cookies_ = vector<int>(cookies);
    sort(children_.begin(), children_.end());
    sort(cookies_.begin(), cookies_.end());

    size_t child_idx = 0, cook_idx = 0;
    while(child_idx < children_.size() && cook_idx < cookies_.size()) {
        if (children_[child_idx] <= cookies_[cook_idx]) {
            ++rtn;
            ++child_idx;
            ++cook_idx;
        } else {
            ++cook_idx;
        }
    }

    return rtn;
}


int main(int argc, char* argv[]) {
    auto children = vector<int>{1, 2};
    auto cookies = vector<int>{2, 3, 4};
    cout << assign_cookies(children, cookies) << endl;

    auto children1 = vector<int>{};
    auto cookies1 = vector<int>{2, 3, 4};
    cout << assign_cookies(children1, cookies1) << endl;

    auto children2 = vector<int>{1, 2};
    auto cookies2 = vector<int>{4};
    cout << assign_cookies(children2, cookies2) << endl;

    auto children3 = vector<int>{1, 2};
    auto cookies3 = vector<int>{};
    cout << assign_cookies(children3, cookies3) << endl;

    auto children4 = vector<int>{1, 2};
    auto cookies4 = vector<int>{1, 1, 1};
    cout << assign_cookies(children4, cookies4) << endl;
}