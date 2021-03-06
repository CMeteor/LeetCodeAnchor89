/*
 Author:     cshony
 Date:       May 19, 2015
 Problem:    Sort List
 Difficulty: Medium
 Source:     https://leetcode.com/problems/sort-list/
 Notes:
 Sort a linked list in O(nlogn) time using constant space complexity.
 Solution: merge sort without recursion.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */ 
class Solution {
public:
	ListNode* mergeList(ListNode *pre, ListNode *head1, ListNode *head2) {
		while(head1 || head2) {
			if(!head1) pre->next = head2, head2 = head2->next;
			else if(!head2) pre->next = head1, head1 = head1->next;
			else if(head1->val > head2->val) pre->next = head2, head2 = head2->next;
			else pre->next = head1, head1 = head1->next;
			pre = pre->next;
		}
		return pre;
	}
	ListNode* sortList(ListNode *head) {
		ListNode fakeHead(0);
		fakeHead.next = head;
		int mergeLen = 1, mergeCount = 2;
		while(mergeCount > 1) {
			ListNode *cur = fakeHead.next, *pre = &fakeHead;
			mergeCount = 0;
			while(cur) {
				mergeCount++;
				if(!cur->next) { pre->next = cur; cur = NULL; continue; }
				ListNode *leftEnd = cur, *rightEnd = cur->next;
				int p = mergeLen;
				while(--p && leftEnd->next) {
					leftEnd = leftEnd->next;
					rightEnd = rightEnd->next ? rightEnd->next : rightEnd;
					rightEnd = rightEnd->next ? rightEnd->next : rightEnd;
				}
				ListNode *head1 = cur, *head2 = leftEnd->next;
				cur = rightEnd->next;
				leftEnd->next = rightEnd->next = NULL;
				pre = mergeList(pre, head1, head2);
			}
			mergeLen*=2;
		}
		return fakeHead.next;
	}
};



// Author: Anchor89
// Time: O(nlgn)
// Space: O(lgn)

class Solution {
public:
  ListNode *sortList(ListNode *head) {
    if (head == NULL) return NULL;
    ListNode h1(0), h2(0), h3(0), *t1=&h1, *t2=&h2, *t3=&h3;
    int val = head->val;
    while(head != NULL) {
      if (head->val < val) {
        t1 = t1->next = head;
      } else if (head->val == val) {
        t2 = t2->next = head;
      } else {
        t3 = t3->next = head;
      }
      head = head->next;
    }
    t1->next = t2->next = t3->next = NULL;
    h1.next = sortList(h1.next);
    for(t1=&h1; t1->next; t1=t1->next);
    t1->next = h2.next;
    t2->next = sortList(h3.next);
    return h1.next;
  }
}
