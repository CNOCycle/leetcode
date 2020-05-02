#include <gtest/gtest.h>

/************************************************
QUSTION: (two-sum)[https://leetcode.com/problems/two-sum/]

Description:

Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.

You may assume that each input would have **exactly** one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

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

void stardard_data(vector<int>& nums, int &target, int &idx1, int &idx2)
{
    vector<int> arr{2,7,11,15};
    nums.swap(arr);
    target = 9;
    idx1 = 0;
    idx2 = 1;
}

class StandardCase : public ::testing::Test 
{
protected:
    void SetUp() override
    {
        stardard_data(input_arr, target, idx1, idx2);
    }

    vector<int> input_arr;
    int target;
    int idx1;
    int idx2;
};

void random_data(vector<int>& nums, int &target, int &idx1, int &idx2)
{
    int MIN_VAL = 0;
    int MAX_VAL = 500000;
    int MAX_LEN = 100000;

    // random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN_VAL, MAX_VAL);

    // set target
    int comp1 = dis(gen);
    int comp2 = dis(gen);
    while(comp1 == comp2)
    {
        comp1 = dis(gen);
        comp2 = dis(gen);
    }
    target = comp1 + comp2;

    // generate target vector: nums
    unordered_map<int, int> forbidden_set;
    forbidden_set.insert( pair<int, int>(comp1, comp2) );
    forbidden_set.insert( pair<int, int>(comp2, comp1) );
    nums.push_back(comp1);
    nums.push_back(comp2);
    
    int ARRAY_LEN = 2;
    {
        std::uniform_int_distribution<> dis(2, MAX_LEN);
        ARRAY_LEN = dis(gen);
    }
    
    while(nums.size() < ARRAY_LEN)
    {
        int next_comp1 = dis(gen);
        int next_comp2 = target - next_comp1;
        if (forbidden_set.find(next_comp1) == forbidden_set.end() &&
            forbidden_set.find(next_comp2) == forbidden_set.end())
        {
            forbidden_set.insert( pair<int, int>(next_comp1, next_comp2) );
            forbidden_set.insert( pair<int, int>(next_comp2, next_comp1) );
            nums.push_back(next_comp1);
        }

    }

    // random suffle
    std::mt19937 g(rd());
    std::shuffle(nums.begin(), nums.end(), g);

    // get indices
    for(int ii = 0; ii < nums.size(); ii = ii + 1)
    {
        if (nums[ii] == comp1)
        {
            idx1 = ii;
        }

        if (nums[ii] == comp2)
        {
            idx2 = ii;
        }
    }

    if(idx1 > idx2)
    {
        int tmp = idx1;
        idx1 = idx2;
        idx2 = tmp;
    }

}

class RandomCase : public ::testing::Test 
{
protected:
    void SetUp() override
    {
        random_data(input_arr, target, idx1, idx2);
    }

    vector<int> input_arr;
    int target;
    int idx1;
    int idx2;
};


/*************************************************
  This section is baseline code.
***************************************************/
vector<int> baseline_func(vector<int>& nums, int &target)
{
    vector<int> ans;
    for(int ii = 0; ii < nums.size(); ii = ii + 1)
    {
        for(int jj = ii + 1; jj < nums.size(); jj = jj + 1)
        {
            if (nums[ii] + nums[jj] == target)
            {
                ans.push_back(ii);
                ans.push_back(jj);
                break;
            }
        }

    }

    return ans;
};

TEST_F(StandardCase, baseline_func)
{
    vector<int> result;
    result = baseline_func(input_arr, target);
    EXPECT_EQ (result[0], idx1);
    EXPECT_EQ (result[1], idx2);
}

TEST_F(RandomCase, baseline_func)
{
    vector<int> result;
    result = baseline_func(input_arr, target);
    EXPECT_EQ (result[0], idx1);
    EXPECT_EQ (result[1], idx2);
}

/*************************************************
  This section is implemnetion of leetcode
***************************************************/

struct VAL
{
    int idx;
    int val;
};

vector<int> map_func(vector<int>& nums, int &target)
{
    vector<int> ans;
    unordered_map<int,VAL> candidate;
    for(int ii = 0; ii < nums.size(); ii = ii + 1)
    {
        int comp1 = nums[ii];
        int comp2 = target - comp1;
        unordered_map<int,VAL>::iterator it;

        // if we find two elements
        if (candidate.find(comp2) != candidate.end())
        {
            VAL data = candidate[comp2];
            int idx1 = ii;
            int idx2 = data.idx;
            if(idx1 > idx2)
            {
                int tmp = idx1;
                idx1 = idx2;
                idx2 = tmp;
                ans.push_back(idx1);
                ans.push_back(idx2);
                break;
            }
        }
        else // otherwise, insert candidate
        {
            VAL data;
            data.idx = ii;
            data.val = comp1;
            candidate.insert( pair<int, VAL>(data.val, data) );
        }
        
    }

    return ans;
};

TEST_F(StandardCase, map_func)
{
    vector<int> result;
    result = map_func(input_arr, target);
    EXPECT_EQ (result[0], idx1);
    EXPECT_EQ (result[1], idx2);
}

TEST_F(RandomCase, map_func)
{
    vector<int> result;
    result = map_func(input_arr, target);
    EXPECT_EQ (result[0], idx1);
    EXPECT_EQ (result[1], idx2);
}

/*************************************************
  Benchmark:
***************************************************/

TEST_F(RandomCase, benchmark)
{
    std::cout << "size(array):" << input_arr.size() << std::endl;
    {
        vector<int> result;
        auto start = chrono::steady_clock::now();
        result = baseline_func(input_arr, target);
        auto end = chrono::steady_clock::now();
        cout << "[baseline_func] Elapsed time: " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

        EXPECT_EQ (result[0], idx1);
        EXPECT_EQ (result[1], idx2);
        std::cout << "idx1:" << idx1 << std::endl;
        std::cout << "idx2:" << idx2 << std::endl;
    }
    
    {
        vector<int> result;
        auto start = chrono::steady_clock::now();
        result = map_func(input_arr, target);
        auto end = chrono::steady_clock::now();
        cout << "[map_func] Elapsed time: " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

        EXPECT_EQ (result[0], idx1);
        EXPECT_EQ (result[1], idx2);
        std::cout << "idx1:" << idx1 << std::endl;
        std::cout << "idx2:" << idx2 << std::endl;
    }
}