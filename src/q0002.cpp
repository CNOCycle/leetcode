#include <gtest/gtest.h>

/************************************************
QUSTION: (Add Two Numbers)[https://leetcode.com/problems/add-two-numbers/]

Description:

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example1:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

*************************************************/

/*************************************************
  This section is utility.
***************************************************/
/*
 * Definition for singly-linked list.
 */
#include <vector>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* delete_node(ListNode *node)
{
    while(node != nullptr)
    {
        ListNode* next = node->next;
        delete node;
        node = next;
    }
    return nullptr;
}


ListNode* vec_to_node(std::vector<int> &vec)
{
    ListNode* node;
    ListNode* cur_ptr;

    node = new ListNode(vec[0]);
    if(vec.size() > 1)
    {
        cur_ptr = node;
        for(int ii = 1; ii < vec.size(); ii = ii + 1)
        {
            ListNode* next = new ListNode(vec[ii]);
            cur_ptr->next = next;
            cur_ptr = cur_ptr->next;
        }
    }

    return node;
}


bool compare_ans(ListNode* ref, ListNode* pred)
{
    ListNode* ref_ptr = ref;
    ListNode* pred_ptr = pred;

    bool flag_failed = false;
    while(pred_ptr != nullptr)
    {
        // case for len(pred) > len(ref)
        if(ref_ptr == nullptr)
        {
            flag_failed = true;
            break;
        }

        // campare each element
        if(ref_ptr->val != pred_ptr->val)
        {
            flag_failed = true;
            break;
        }

        // get next node
        ref_ptr = ref_ptr->next;
        pred_ptr = pred_ptr->next;
    }

    // case for len(ref) > len(pred)
    if(ref_ptr != nullptr)
    {
        flag_failed = true;
    }

    return flag_failed;
}


/*************************************************
  This section is code for preparing testing data.
***************************************************/
#include <iostream>
#include <random>
#include <utility>
using namespace std;

// \TODO: random case


/*************************************************
  This section is baseline code.
***************************************************/
class Solution {

private:
    int get_value(ListNode* node)
    {
        int val = 0;
        if(node != nullptr)
        {
            val = node->val;
        }
        return val;
    }

    ListNode* get_next(ListNode* node)
    {
        ListNode* next = nullptr;
        if(node != nullptr)
        {
            next = node->next;
        }

        return next;
    }

public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* ans = nullptr;
        ListNode* cur = nullptr;

        int carry = 0;
        while(true)
        {
            int val1 = get_value(l1);
            int val2 = get_value(l2);
            int val = val1 + val2 + carry;
            if(val >= 10)
            {
                val = val - 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            // update ListNode
            ListNode *current = new ListNode(val);
            if(ans == nullptr)
            {
                ans = current;
                cur = ans;
            }
            else
            {
                cur->next = current;
                cur= cur->next;
            }

            l1 = get_next(l1);
            l2 = get_next(l2);

            if(l1 == nullptr && l2 == nullptr)
            {
                break;
            }

        }

        // check carry bit
        if(carry == 1)
        {
            ListNode* next = new ListNode(1);
            cur->next = next;
        }

        return ans;
    }
};

TEST(StandardCase, Case1)
{
    std::vector<int> vec_l1{2,4,3};
    std::vector<int> vec_l2{5,6,4};
    std::vector<int> vec_ref{7,0,8};

    ListNode* l1 = vec_to_node(vec_l1);
    ListNode* l2 = vec_to_node(vec_l2);
    ListNode* ref = vec_to_node(vec_ref);

    Solution Solution;
    ListNode* ans = Solution.addTwoNumbers(l1, l2);
    bool flag_failed = compare_ans(ref, ans);
    EXPECT_EQ(flag_failed, false);

    l1 = delete_node(l1);
    l2 = delete_node(l2);
    ref = delete_node(ref);
    ans = delete_node(ans);
}

TEST(StandardCase, Case2)
{
    std::vector<int> vec_l1{0};
    std::vector<int> vec_l2{0};
    std::vector<int> vec_ref{0};

    ListNode* l1 = vec_to_node(vec_l1);
    ListNode* l2 = vec_to_node(vec_l2);
    ListNode* ref = vec_to_node(vec_ref);

    Solution Solution;
    ListNode* ans = Solution.addTwoNumbers(l1, l2);
    bool flag_failed = compare_ans(ref, ans);
    EXPECT_EQ(flag_failed, false);

    l1 = delete_node(l1);
    l2 = delete_node(l2);
    ref = delete_node(ref);
    ans = delete_node(ans);
}

TEST(StandardCase, Case3)
{
    std::vector<int> vec_l1{9,9,9,9,9,9,9};
    std::vector<int> vec_l2{9,9,9,9};
    std::vector<int> vec_ref{8,9,9,9,0,0,0,1};

    ListNode* l1 = vec_to_node(vec_l1);
    ListNode* l2 = vec_to_node(vec_l2);
    ListNode* ref = vec_to_node(vec_ref);

    Solution Solution;
    ListNode* ans = Solution.addTwoNumbers(l1, l2);
    bool flag_failed = compare_ans(ref, ans);
    EXPECT_EQ(flag_failed, false);

    l1 = delete_node(l1);
    l2 = delete_node(l2);
    ref = delete_node(ref);
    ans = delete_node(ans);
}
