
#include <gtest/gtest.h>

/************************************************
QUSTION: (Guess the Word)[https://leetcode.com/problems/guess-the-word/]

Description:

This problem is an interactive problem new to the LeetCode platform.

We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.

You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the original list with 6 lowercase letters.

This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.

For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.

Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.  The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.

Example 1:
Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]

Explanation:

master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.

We made 5 calls to master.guess and one of them was the secret, so we pass the test case.

Note:  Any solutions that attempt to circumvent the judge will result in disqualification.


*************************************************/

/*************************************************
  This section is code for preparing testing data.
***************************************************/
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <utility>
using namespace std;

void stardard_data(vector<string>& wordlist, string &ans, int t_case)
{
    ASSERT_LT(t_case, 4);

    if(t_case == 0)
    {
        vector<string> a = {"acckzz","ccbazz","eiowzz","abcczz"};
        wordlist.swap(a);
        ans = "acckzz";
    }
    
    if (t_case == 1)
    {
        vector<string> a = {"wichbx","oahwep","tpulot","eqznzs","vvmplb","eywinm","dqefpt","kmjmxr","ihkovg","trbzyb","xqulhc","bcsbfw","rwzslk","abpjhw","mpubps","viyzbc","kodlta","ckfzjh","phuepp","rokoro","nxcwmo","awvqlr","uooeon","hhfuzz","sajxgr","oxgaix","fnugyu","lkxwru","mhtrvb","xxonmg","tqxlbr","euxtzg","tjwvad","uslult","rtjosi","hsygda","vyuica","mbnagm","uinqur","pikenp","szgupv","qpxmsw","vunxdn","jahhfn","kmbeok","biywow","yvgwho","hwzodo","loffxk","xavzqd","vwzpfe","uairjw","itufkt","kaklud","jjinfa","kqbttl","zocgux","ucwjig","meesxb","uysfyc","kdfvtw","vizxrv","rpbdjh","wynohw","lhqxvx","kaadty","dxxwut","vjtskm","yrdswc","byzjxm","jeomdc","saevda","himevi","ydltnu","wrrpoc","khuopg","ooxarg","vcvfry","thaawc","bssybb","ccoyyo","ajcwbj","arwfnl","nafmtm","xoaumd","vbejda","kaefne","swcrkh","reeyhj","vmcwaf","chxitv","qkwjna","vklpkp","xfnayl","ktgmfn","xrmzzm","fgtuki","zcffuv","srxuus","pydgmq"};
        wordlist.swap(a);
        ans = "ccoyyo";
    }

    if (t_case == 2)
    {
        vector<string> a = { "gaxckt","trlccr","jxwhkz","ycbfps","peayuf","yiejjw","ldzccp","nqsjoa","qrjasy","pcldos","acrtag","buyeia","ubmtpj","drtclz","zqderp","snywek","caoztp","ibpghw","evtkhl","bhpfla","ymqhxk","qkvipb","tvmued","rvbass","axeasm","qolsjg","roswcb","vdjgxx","bugbyv","zipjpc","tamszl","osdifo","dvxlxm","iwmyfb","wmnwhe","hslnop","nkrfwn","puvgve","rqsqpq","jwoswl","tittgf","evqsqe","aishiv","pmwovj","sorbte","hbaczn","coifed","hrctvp","vkytbw","dizcxz","arabol","uywurk","ppywdo","resfls","tmoliy","etriev","oanvlx","wcsnzy","loufkw","onnwcy","novblw","mtxgwe","rgrdbt","ckolob","kxnflb","phonmg","egcdab","cykndr","lkzobv","ifwmwp","jqmbib","mypnvf","lnrgnj","clijwa","kiioqr","syzebr","rqsmhg","sczjmz","hsdjfp","mjcgvm","ajotcx","olgnfv","mjyjxj","wzgbmg","lpcnbj","yjjlwn","blrogv","bdplzs","oxblph","twejel","rupapy","euwrrz","apiqzu","ydcroj","ldvzgq","zailgu","xgqpsr","wxdyho","alrplq","brklfk"};
        wordlist.swap(a);
        ans = "hbaczn";
    }

    if (t_case == 3)
    {
        vector<string> a = {"mjpsce","giwiyk","slbnia","pullbr","ezvczd","dwkrmt","qgzebh","wvhhlm","kqbmny","zpvrkz","pdwxvy","gilywa","gmrrdc","vvqvla","rmjirt","qmvykq","mhbmuq","unplzn","qkcied","eignxg","fbfgng","xpizga","twubzr","nnfaxr","skknhe","twautl","nglrst","mibyks","qrbmpx","ukgjkq","mhxxfb","deggal","bwpvsp","uirtak","tqkzfk","hfzawa","jahjgn","mteyut","jzbqbv","ttddtf","auuwgn","untihn","gbhnog","zowaol","feitjl","omtiur","kwdsgx","tggcqq","qachdn","dixtat","hcsvbw","chduyy","gpdtft","bjxzky","uvvvko","jzcpiv","gtyjau","unsmok","vfcmhc","hvxnut","orlwku","ejllrv","jbrskt","xnxxdi","rfreiv","njbvwj","pkydxy","jksiwj","iaembk","pyqdip","exkykx","uxgecc","khzqgy","dehkbu","ahplng","jomiik","nmcsfe","bclcbp","xfiefi","soiwde","tcjkjp","wervlz","dcthgv","hwwghe","hdlkll","dpzoxb","mpiviy","cprcwo","molttv","dwjtdp","qiilsr","dbnaxs","dbozaw","webcyp","vftnkr","iurlzf","giqcfc","pcghoi","zupyzn","xckegy"};
        wordlist.swap(a);
        ans = "vftnkr";
    }

}

class StandardCase : public ::testing::Test 
{
protected:
    void SetUp() override
    {
        stardard_data(t1_list, t1_ans, 0);
        stardard_data(t2_list, t2_ans, 1);
        stardard_data(t3_list, t3_ans, 2);
        stardard_data(t4_list, t4_ans, 3);
    }

    vector<string> t1_list, t2_list, t3_list, t4_list;
    string t1_ans, t2_ans, t3_ans, t4_ans;
};


/*************************************************
  This section is baseline code.
***************************************************/

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

int get_next_id(vector<int> &status)
{

    int ans = -1;
    vector<int> candidate;
    for(int ii = 0; ii < status.size(); ii = ii + 1)
    {
        if(status[ii] == 0)
        {
            candidate.push_back(ii);
            if(ans == -1)
            {
                ans = ii;
            }
            
        }
        
    }

    // random generator
    //std::cout << "len(candidate): " << candidate.size() << "\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, candidate.size()-1);
    int id = dis(gen);
    ans = candidate[id];

    return ans;
    
};

int string_comp(string A, string B)
{
    int count = 0;
    for(int ii = 0; ii < 6; ii = ii + 1)
    {
        if(A[ii] == B[ii])
        {
            count = count + 1;
        }
        
    }
    
    return count;
};

void update_status(vector<int> &status, vector<string> &wordlist, string target, int ans)
{
    for(int ii = 0; ii < status.size(); ii = ii + 1)
    {
        if(status[ii] == -1)
        {
            continue;
        }
        
        int count = string_comp(wordlist[ii], target);
        if(count == 6)
        {
            status[ii] = -1;
        }
        else if (count != ans)
        {
            status[ii] = -1;
        }
        
    }
      
    
}

class Master {
   public:
     int guess(string word)
     {
         return string_comp(this->ans, word);

     };

     void set_ans(string _ans)
     {
         ans = _ans;
     }
     string ans;
 };

class Solution {
public:
    int findSecretWord(vector<string>& wordlist, Master& master) 
    {
        
        vector<int> status(wordlist.size());

        for(int ii = 0; ii < 11; ii = ii + 1)
        {
            //std::cout << ii << "----------------------\n";
            int next_id = get_next_id(status);
            string target = wordlist[next_id];
            int ans = master.guess(target);
            if(ans == 6)
            {
                //cout << "get it\n";
                //cout << next_id << endl;
                //cout << target << endl;
                //std::cout << "TODO list:\n";
                //for(int ii = 0; ii < status.size(); ii = ii + 1)
                //{
                //    if(status[ii] != -1)
                //    {
                //        std::cout << ii << endl;
                //    }
                //    
                //}
                return ii;
            }
            
            update_status(status, wordlist, target, ans);
            
        }
        
        return 11;
    }

    int count = 0;
};

TEST_F(StandardCase, baseline_func)
{
    int MAX_COUNT = 11;
    int count;
    Master m;
    Solution s;

    // case 1
    m.ans = t1_ans;
    count = s.findSecretWord(t1_list, m);
    ASSERT_LT (count, MAX_COUNT);

    // case 2
    m.ans = t2_ans;
    count = s.findSecretWord(t2_list, m);
    ASSERT_LT (count, MAX_COUNT);

    // case 3
    m.ans = t3_ans;
    count = s.findSecretWord(t3_list, m);
    ASSERT_LT (count, MAX_COUNT);

    // case 4
    m.ans = t4_ans;
    count = s.findSecretWord(t4_list, m);
    ASSERT_LT (count, MAX_COUNT);
}