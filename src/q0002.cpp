/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

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
            int val;
            if(val1 + val2 + carry >= 10)
            {
                val = val1 + val2 + carry - 10;
                carry = 1;
            }
            else
            {
                val = val1 + val2 + carry;
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

int main()
{

    ListNode* l1 = new ListNode(9);
    ListNode* l2 = new ListNode(9);
    ListNode* cur;
    ListNode* next;

    cur = l1;
    {
        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;
    }

    cur = l2;
    {
        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;

        next = new ListNode(9);
        cur->next = next;
        cur = cur->next;
    }

    cur = l1;
    std::cout << "------------L1------------" << std::endl;
    while(cur != nullptr)
    {
        std::cout << cur->val << std::endl;
        cur = cur->next;
    }

    cur = l2;
    std::cout << "------------L2------------" << std::endl;
    while(cur != nullptr)
    {
        std::cout << cur->val << std::endl;
        cur = cur->next;
    }

    std::cout << "------------algo------------" << std::endl;
    Solution Solution;
    cur = Solution.addTwoNumbers(l1, l2);
    while(cur != nullptr)
    {
        std::cout << cur->val << std::endl;
        cur = cur->next;
    }
}