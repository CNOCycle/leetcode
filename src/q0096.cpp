#include <gtest/gtest.h>

/************************************************
QUSTION: (Unique Binary Search Trees)[https://leetcode.com/problems/unique-binary-search-trees/]

Description:

Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3


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

void stardard_data(int &intput, int &count)
{
    intput = 3;
    count = 5;
}

class StandardCase : public ::testing::Test 
{
protected:
    void SetUp() override
    {
        stardard_data(input, count);
    }

    int input;
    int count;
};


/*************************************************
  This section is baseline code.
***************************************************/
int baseline_func(int n)
{

    if(n == 1)
    {
        return 1;
    }

    if(n == 2)
    {
        return 2;
    }

    // reset table
    int *table = new int[n+1];
    for(int ii = 0; ii < n; ii = ii + 1)
    {
        table[ii] = 0;
    }
    table[0] = 1;   // case n = 0
    table[1] = 1;   // case n = 1
    table[2] = 2;   // case n = 2

    for(int ii = 3; ii <= n; ii = ii + 1)
    {
        int count = 0;
        for(int jj = 0; jj < ii; jj = jj + 1)
        {
            int LH = jj;
            int RH = (ii - 1) - jj;
            count = count + table[LH] * table[RH];
        }
        table[ii] = count;
    }
    int ans = table[n];
    delete [] table;

    return ans;
};

TEST_F(StandardCase, baseline_func)
{
    int ans;
    ans = baseline_func(input);
    EXPECT_EQ (ans, count);
}
