#include <gtest/gtest.h>

/************************************************
QUSTION: (Maximum Points You Can Obtain from Cards)[https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/]

Description:

There are several cards arranged in a row, and each card has an associated number of points The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Example:

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1.
             However, choosing the rightmost card first will maximize your total score.
             The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

*************************************************/

/*************************************************
  This section is code for preparing testing data.
***************************************************/
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

struct Input
{
    vector<int> cardPoints;
    int k;
    int ans;
};


class StandardCase : public ::testing::Test
{
private:

    Input std_test1()
    {
        vector<int> arr{1,2,3,4,5,6,1};

        Input data;
        data.cardPoints.swap(arr);
        data.k = 3;
        data.ans = 12;
        return data;
    }

    Input std_test2()
    {
        vector<int> arr{2,2,2};

        Input data;
        data.cardPoints.swap(arr);
        data.k = 2;
        data.ans = 4;
        return data;
    }

    Input std_test3()
    {
        vector<int> arr{9,7,7,9,7,7,9};

        Input data;
        data.cardPoints.swap(arr);
        data.k = 7;
        data.ans = 55;
        return data;
    }

    Input std_test4()
    {
        vector<int> arr{1,1000,1};

        Input data;
        data.cardPoints.swap(arr);
        data.k = 1;
        data.ans = 1;
        return data;
    }

    Input std_test5()
    {
        vector<int> arr{1,79,80,1,1,1,200,1};

        Input data;
        data.cardPoints.swap(arr);
        data.k = 3;
        data.ans = 202;
        return data;
    }

protected:
    void SetUp() override
    {
        candidates.push_back(std_test1());
        candidates.push_back(std_test2());
        candidates.push_back(std_test3());
        candidates.push_back(std_test4());
        candidates.push_back(std_test5());
    }

    vector<Input> candidates;
};


/*************************************************
  This section is baseline code.
***************************************************/
int maxScore(vector<int>& cardPoints, int k)
{
    int sum = 0;
    for(int ii=1;ii<=k;ii=ii+1)
    {
        sum = sum + cardPoints[ii-1];
    }


    int max = sum;
    for(int ii=1;ii<=k;ii=ii+1)
    {
        sum = sum - cardPoints[k-ii] + cardPoints[cardPoints.size()-ii];
        if(sum > max)
        {
            max = sum;
        }

    }

    return max;
};

TEST_F(StandardCase, baseline_func)
{
    for(int ii = 0; ii < candidates.size(); ii = ii + 1)
    {
        Input input = candidates[ii];
        int result = maxScore(input.cardPoints, input.k);
        EXPECT_EQ (result, input.ans);
    }

}