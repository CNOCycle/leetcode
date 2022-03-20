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
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

struct Input
{
    vector<int> nums;
    int target;
    int idx1;
    int idx2;
};


class StandardCase : public ::testing::Test 
{
private:

    Input std_test1()
    {
        vector<int> arr{2,7,11,15};
        Input data = {arr, 9, 0, 1};
        return data;
    }

    Input std_test2()
    {
        vector<int> arr{3,2,4};
        Input data = {arr, 6, 1, 2};
        return data;
    }

    Input std_test3()
    {
        vector<int> arr{3,3};
        Input data = {arr, 6, 0, 1};
        return data;
    }

protected:
    void SetUp() override
    {
        candidates.push_back(std_test1());
        candidates.push_back(std_test2());
        candidates.push_back(std_test3());
    }

    vector<Input> candidates;
};


class RandomCase : public ::testing::Test 
{
private:

    void random_data(vector<int>& nums, int &target, int &idx1, int &idx2)
    {
        int MIN_VAL = -1e9;
        int MAX_VAL = 1e9;
        int MAX_LEN = 100000;

        // random generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(MIN_VAL, MAX_VAL);

        // set target
        int comp1 = dis(gen);
        int comp2 = dis(gen);
        target = comp1 + comp2;
        while(target < -1e9 || 1e9 < target )
        {
            comp1 = dis(gen);
            comp2 = dis(gen);
            target = comp1 + comp2;
        }
        
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
            if(next_comp2 < -1e9 || 1e9 < next_comp2)
            {
                continue;
            }
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
    vector<int> ans(2);
    for(int ii = 0; ii < nums.size(); ii = ii + 1)
    {
        for(int jj = ii + 1; jj < nums.size(); jj = jj + 1)
        {
            if (nums[ii] + nums[jj] == target)
            {
                ans[0] = ii;
                ans[1] = jj;
                break;
            }
        }

    }

    return ans;
};

TEST_F(StandardCase, baseline_func)
{
    for(int ii = 0; ii < candidates.size(); ii = ii + 1)
    {
        Input input = candidates[ii];
        vector<int> result;
        result = baseline_func(input.nums, input.target);
        EXPECT_EQ (result[0], input.idx1);
        EXPECT_EQ (result[1], input.idx2);
    }

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
vector<int> map_func(vector<int>& nums, int &target)
{
    vector<int> ans(2);
    // the first element is val,
    // the second element is idx
    unordered_map<int, int> candidate;
    for(int ii = 0; ii < nums.size(); ii = ii + 1)
    {
        int comp1 = nums[ii];
        int comp2 = target - comp1;

        // if we find two elements
        if (candidate.find(comp2) != candidate.end())
        {
            int idx1 = ii;
            int idx2 = candidate[comp2];
            if(idx1 > idx2)
            {
                ans[0] = idx2;
                ans[1] = idx1;
            }
            else
            {
                ans[0] = idx1;
                ans[1] = idx2;
            }
            break;
        }
        else // otherwise, insert candidate
        {
            candidate.insert( pair<int, int>(comp1, ii) );
        }
        
    }

    return ans;
};


TEST_F(StandardCase, map_func)
{
    for(int ii = 0; ii < candidates.size(); ii = ii + 1)
    {
        Input input = candidates[ii];
        vector<int> result;
        result = map_func(input.nums, input.target);
        EXPECT_EQ (result[0], input.idx1);
        EXPECT_EQ (result[1], input.idx2);
    }

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