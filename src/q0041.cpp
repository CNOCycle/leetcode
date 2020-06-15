#include <gtest/gtest.h>

/************************************************
QUSTION: (First Missing Positive)[https://leetcode.com/problems/first-missing-positive/]

Description:

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3

Example 2:

Input: [3,4,-1,1]
Output: 2

Example 3:

Input: [7,8,9,11,12]
Output: 1

Note:

Your algorithm should run in O(n) time and uses constant extra space.


*************************************************/

/*************************************************
  This section is code for preparing testing data.
***************************************************/
#include <chrono>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;


void stardard_data(vector<int>& wordlist, int &ans, int t_case)
{
    ASSERT_LT(t_case, 9);

    if(t_case == 0)
    {
        vector<int> a = {1,2,0};
        wordlist.swap(a);
        ans = 3;
    }
    
    if (t_case == 1)
    {
        vector<int> a = {3,4,-1,1};
        wordlist.swap(a);
        ans = 2;
    }

    if (t_case == 2)
    {
        vector<int> a = {6,7,8,9,11,12};
        wordlist.swap(a);
        ans = 1;
    }

    if (t_case == 3)
    {
        vector<int> a = {3,1};
        wordlist.swap(a);
        ans = 2;
    }


    if (t_case == 4)
    {
        vector<int> a = {1,2,3};
        wordlist.swap(a);
        ans = 4;
    }

    if (t_case == 5)
    {
        vector<int> a = {0,1,2};
        wordlist.swap(a);
        ans = 3;
    }

    if (t_case == 6)
    {
        vector<int> a = {2,1};
        wordlist.swap(a);
        ans = 3;
    }

    if (t_case == 7)
    {
        vector<int> a = {999,500,1};
        wordlist.swap(a);
        ans = 2;
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
        stardard_data(t5_list, t5_ans, 4);
        stardard_data(t6_list, t6_ans, 5);
        stardard_data(t7_list, t7_ans, 6);
        stardard_data(t8_list, t8_ans, 7);

    }

    vector<int> t1_list, t2_list, t3_list, t4_list, t5_list, t6_list, t7_list, t8_list;
    int t1_ans, t2_ans, t3_ans, t4_ans, t5_ans, t6_ans, t7_ans, t8_ans;
};

/*************************************************
  This section is baseline code.
***************************************************/

int solution(vector<int>& nums)
{
    int Lidx = 0;
    int Uidx = 0;

    int Lvalue = 1;
    int Uvalue = nums.size() + 1;

    bool Lflag = false;
    bool Uflag = false;

    while (true)
    {
        Lflag = false;
        Uflag = false;

        int ii = 0;
        while(ii < Uvalue - 1)
        {
            if(nums[ii] == Lvalue)
            {
                Lvalue = Lvalue + 1;
                Lflag = true;
            }

            if(nums[ii] > Uvalue)
            {
                Uvalue = Uvalue - 1;
                int tmp = nums[ii];
                nums[ii] = nums[Uvalue-1];
                nums[Uvalue-1] = tmp;
                Uflag = true;
            }

            ii = ii + 1;
        }

        if (Uflag == true)
        {
            continue;
        }

        if(Lflag == false)
        {
            break;
        }

    }
    
    return Lvalue;

};

TEST_F(StandardCase, baseline_func)
{

    int ans;

    // case 1
    ans = solution(t1_list);
    EXPECT_EQ (ans, t1_ans);

    // case 2
    ans = solution(t2_list);
    EXPECT_EQ (ans, t2_ans);

    // case 3
    ans = solution(t3_list);
    EXPECT_EQ (ans, t3_ans);

    // case 4
    ans = solution(t4_list);
    EXPECT_EQ (ans, t4_ans);

    // case 5
    ans = solution(t5_list);
    EXPECT_EQ (ans, t5_ans);

    // case 6
    ans = solution(t6_list);
    EXPECT_EQ (ans, t6_ans);

    // case 7
    ans = solution(t7_list);
    EXPECT_EQ (ans, t7_ans);

    // case 8
    ans = solution(t8_list);
    EXPECT_EQ (ans, t8_ans);

}

/*************************************************
  This section is implemnetion of leetcode
***************************************************/

int adv_solution(vector<int>& nums)
{
    int MaxLen = nums.size();

    int Lvalue = 1;
    int Uvalue = nums.size() + 1;

    bool Lflag = false;
    bool Uflag = false;

    while (true)
    {
        // forward
        {
            Lflag = false;
            Uflag = false;
            int ii = 0;
            while(ii < MaxLen)
            {
                if(nums[ii] < Lvalue)
                {
                    MaxLen = MaxLen - 1;
                    int tmp = nums[ii];
                    nums[ii] = nums[MaxLen];
                    nums[MaxLen] = tmp;
                }

                if(nums[ii] == Lvalue)
                {
                    Lvalue = Lvalue + 1;
                    Lflag = true;
                }

                if(nums[ii] > Uvalue + 1)
                {
                    Uvalue = Uvalue - 1;
                    MaxLen = MaxLen - 1;
                    int tmp = nums[ii];
                    nums[ii] = nums[MaxLen];
                    nums[MaxLen] = tmp;
                    Uflag = true;
                }

                ii = ii + 1;
            }

            if(Lflag == false && Uflag == false)
            {
                break;
            }
        }

        //backward
        {
            Lflag = false;
            Uflag = false;
            int ii = MaxLen - 1;
            while(ii >= 0)
            {
                if(nums[ii] < Lvalue)
                {
                    MaxLen = MaxLen - 1;
                    int tmp = nums[ii];
                    nums[ii] = nums[MaxLen];
                    nums[MaxLen] = tmp;
                }

                if(nums[ii] == Lvalue)
                {
                    Lvalue = Lvalue + 1;
                    Lflag = true;
                }

                if(nums[ii] > Uvalue + 1)
                {
                    Uvalue = Uvalue - 1;
                    MaxLen = MaxLen - 1;
                    int tmp = nums[ii];
                    nums[ii] = nums[MaxLen];
                    nums[MaxLen] = tmp;
                    Uflag = true;
                }

                ii = ii - 1;
            }

            if (Uflag == true)
            {
                continue;
            }

            if(Lflag == false)
            {
                break;
            }
        }

    }
    
    return Lvalue;

};

TEST_F(StandardCase, adv_func)
{

    int ans;

    // case 1
    ans = adv_solution(t1_list);
    EXPECT_EQ (ans, t1_ans);

    // case 2
    ans = adv_solution(t2_list);
    EXPECT_EQ (ans, t2_ans);

    // case 3
    ans = adv_solution(t3_list);
    EXPECT_EQ (ans, t3_ans);

    // case 4
    ans = adv_solution(t4_list);
    EXPECT_EQ (ans, t4_ans);

    // case 5
    ans = adv_solution(t5_list);
    EXPECT_EQ (ans, t5_ans);

    // case 6
    ans = adv_solution(t6_list);
    EXPECT_EQ (ans, t6_ans);

    // case 7
    ans = adv_solution(t7_list);
    EXPECT_EQ (ans, t7_ans);

    // case 8
    ans = adv_solution(t8_list);
    EXPECT_EQ (ans, t8_ans);

}