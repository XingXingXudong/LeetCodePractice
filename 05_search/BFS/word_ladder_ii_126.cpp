// https://leetcode.com/problems/word-ladder-ii/
#include <gtest/gtest.h>
#include <queue>
#include <string>
#include <iostream>
#include <set>
#include <unordered_map>

bool is_equal(const std::vector<std::vector<std::string>>& a, const std::vector<std::vector<std::string>>& b) {
    if (a.empty() && b.empty()) {
        return true;
    }
    auto set_a = std::set<std::vector<std::string>>(a.begin(), a.end());
    auto set_b = std::set<std::vector<std::string>>(b.begin(), b.end());
    return set_a == set_b;
}

std::set<std::string> nexts1(std::set<std::string>& all_words, const std::vector<std::string>& words) {
    auto word = words.back();
    auto word_set = std::set<std::string>(words.begin(), words.end());
    auto ans = std::set<std::string>{};
    for (size_t i = 0; i < word.size(); ++i) {
        word = words.back();
        for (char c = 'a'; c <= 'z'; ++c) {
            word[i] = c;
            // std::cout << word << std::endl;
            if (all_words.find(word) != all_words.end() && word_set.find(word) == word_set.end() && ans.find(word) == ans.end()) {
                ans.insert(word);
            }
        }
    }
    return ans;
}

std::set<std::string> nexts(std::vector<std::string>& word_list, const std::vector<std::string>& words) {
    // auto ans = std::vector<std::string>{};
    auto word = words.back();
    auto word_set = std::set<std::string>(words.begin(), words.end());
    auto ans = std::set<std::string>{};
    for (auto iter = word_list.begin(); iter != word_list.end(); ++iter) {
        int count = 0;
        for(size_t i = 0; i < word.size(); ++i) {
            if ((*iter)[i] != word[i]) {
                ++count;
                if (count > 1) {
                    break;
                }
            }
        }
        if (count == 1 && word_set.find(*iter) == word_set.end()) {
            // ans.push_back(*iter);
            ans.insert(*iter);
        }
    }
    return ans;
}

std::vector<std::vector<std::string>> findLadders(std::string& start_word, std::string& end_word, std::vector<std::string>& word_list) {
    auto word_set = std::set<std::string>(word_list.begin(), word_list.end());
    auto ladders = std::vector<std::vector<std::string>>{};
    auto routings = std::queue<std::vector<std::string>>{};
    routings.push(std::vector<std::string>{start_word});
    size_t max_length = word_list.size() + 1;
    while (!routings.empty()) {
        auto front = routings.front();
        if (front.size() == max_length) {
            break;
        }
        std::cout << "size: " << front.size() << ", back: " << front.back() << std::endl;
        // auto next_words = nexts(word_list, front.back());
        auto next_words = nexts1(word_set, front);
        if (next_words.find(end_word) != next_words.end()) {
            front.push_back(end_word);
            max_length = front.size();
            ladders.push_back(front);
        } else {
            for (const auto & w: next_words) {
                routings.push(front);
                routings.back().push_back(w);
            }
        } 
        routings.pop();
    }
    return ladders;
}

void 
backtransing(const std::string& start_word, const std::string& end_word, 
             std::unordered_map<std::string, std::vector<std::string>>& next, 
             std::vector<std::string>& path, std::vector<std::vector<std::string>>& ans) {

    if (end_word == start_word) {
        ans.push_back(path);
        return;
    }
    for (const auto& s: next[start_word]) {
        path.push_back(s);
        backtransing(s, end_word, next, path, ans);
        path.pop_back();
    }
}

std::vector<std::vector<std::string>>
findLadders1(std::string& start_word, std::string& end_word, std::vector<std::string>& word_list) {
    std::vector<std::vector<std::string>> ans;
    std::set<std::string> dict(word_list.begin(), word_list.end());
    if (!dict.count(end_word)) {
        return ans;
    }
    dict.erase(end_word);
    dict.erase(start_word);
    std::set<std::string> starts{std::string(start_word)}, ends{std::string(end_word)};
    std::unordered_map<std::string, std::vector<std::string>> next;
    bool reversed = false, found = false;
    while (!starts.empty()) {
        std::set<std::string> currents;
        for (const auto &w: starts) {
            std::string s = w;
            for (size_t i = 0; i < s.size(); ++i) {
                char ch = s[i];
                for (int j = 0; j <= 26; ++j) {
                    s[i] = 'a' + j;
                    if (ends.count(s)) {   // 再另一端存在，说明找到了最短路径
                        reversed? next[s].push_back(w) : next[w].push_back(s);
                        found = true;
                    }
                    if (dict.count(s)) {  // 否则，增假节点，继续搜索
                        reversed? next[s].push_back(w) : next[w].push_back(s);
                        currents.insert(s);
                    }
                }
                s[i] = ch;
            }
        }
        if (found) {
            break;
        }
        for (const auto& w: currents) {   // 当前层的节点已经保留在左或右的一端，接下来的层中，不必要进一步搜索
            dict.erase(w);
        }
        if (currents.size() <= ends.size()) {   // 选择节点数最少的，进行下一层的遍历
            starts = currents;
        } else {
            reversed = !reversed;
            starts = ends;
            ends = currents;
        }
    }
    if (found) {
        std::vector<std::string> path{std::string{start_word}};
        backtransing(start_word, end_word, next, path, ans);
    }
    return ans;
}


TEST(id_equal, a) {
    auto output = std::vector<std::vector<std::string>>{
        {"hit","hot","dot","dog","cog"},
        {"hit","hot","lot","log","cog"} 
    };
    auto output1 = std::vector<std::vector<std::string>>{
        {"hit","hot","lot","log","cog"} ,
        {"hit","hot","dot","dog","cog"}
    };

    auto output2 = std::vector<std::vector<std::string>>{
        {"hit","hot","lot","log","cog"} ,
        {"hat","hot","dot","dog","cog"}
    };

    EXPECT_TRUE(is_equal(output, output1));
    EXPECT_FALSE(is_equal(output, output2));
}

TEST(findLadders1, a) {
    std::string begin_word{"hit"};
    std::string end_word{"cog"};
    auto word_list = std::vector<std::string>{"hot","dot","dog","lot","log","cog"};
    auto output = std::vector<std::vector<std::string>>{
        {"hit","hot","dot","dog","cog"},
        {"hit","hot","lot","log","cog"} 
    };
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}

TEST(findLadders1, b) {
    std::string begin_word{"hit"};
    std::string end_word{"cog"};
    auto word_list = std::vector<std::string>{"hot","dot","dog","lot","log"};
    auto output = std::vector<std::vector<std::string>>{};
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}

TEST(findLadders1, c) {
    std::string begin_word{"a"};
    std::string end_word{"c"};
    auto word_list = std::vector<std::string>{"b","c"};
    auto output = std::vector<std::vector<std::string>>{{"a", "c"}};
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}

TEST(findLadders1, d) {
    std::string begin_word{"abcd"};
    std::string end_word{"efgh"};
    auto word_list = std::vector<std::string>{"abcd","ebcd", "efcd", "efgd", "efgh"};
    auto output = std::vector<std::vector<std::string>>{{"abcd","ebcd", "efcd", "efgd", "efgh"}};
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}

TEST(findLadders1, e) {
    std::string begin_word{"red"};
    std::string end_word{"tax"};
    auto word_list = std::vector<std::string>{"ted","tex","red","tax","tad","den","rex","pee"};
    auto output = std::vector<std::vector<std::string>>{{"red","ted","tad","tax"},{"red","ted","tex","tax"},{"red","rex","tex","tax"}};
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}

// /*
TEST(findLadders1, f) {
    std::string begin_word{"cet"};
    std::string end_word{"ism"};
    auto word_list = std::vector<std::string>{"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};
    auto output = std::vector<std::vector<std::string>>{{"red","ted","tad","tax"},{"red","ted","tex","tax"},{"red","rex","tex","tax"}};
    EXPECT_TRUE(is_equal(findLadders1(begin_word, end_word, word_list), output));
}
// */

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

