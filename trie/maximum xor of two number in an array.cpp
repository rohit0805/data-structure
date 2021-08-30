https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

class TrieNode {
public:
    TrieNode* left;
    TrieNode* right;
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(int n) {
        TrieNode* temp = root;
        int bit;
        for (int i = 31; i >= 0; i--) {
            bit = (n >> i) & 1;

            if (bit == 0) {
                if (temp->left == NULL) {
                    temp->left = new TrieNode();
                }
                temp = temp->left;
            }
            else {
                if (temp->right == NULL) {
                    temp->right = new TrieNode();
                }
                temp = temp->right;
            }
        }
    }

    int max_xoring(int val) {
        TrieNode* temp = root;
        int bit;
        int number = 0;
        for (int i = 31; i >= 0; i--) {
            bit = (val >> i) & 1;
            if (bit == 0) {
                if (temp->right != NULL) {
                    temp = temp->right;
                    number += 1 << i;
                }
                else {
                    temp = temp->left;
                }

            }
            else {
                if (temp->left != NULL) {
                    temp = temp->left;
                    number += 1 << i;
                }
                else {
                    temp = temp->right;
                }
            }
        }
        return number;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        Trie ob;
        int maxi = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            ob.insert(nums[i]);
            int x = ob.max_xoring(nums[i]);
            maxi = max(maxi, x);
        }
        return maxi;
    }
};