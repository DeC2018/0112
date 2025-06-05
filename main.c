#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 5000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper to parse input string like "[5,4,8,11,null,13,4,7,2,null,null,null,1]" to array
int parseInput(const char* s, char arr[][16], int* n) {
    int i = 0, j = 0, k = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '[')) ++i;
    while (s[i] && s[i] != ']') {
        if (s[i] == ',') {
            arr[k][j] = '\0';
            ++k; j = 0;
        } else if (s[i] != ' ') {
            arr[k][j++] = s[i];
        }
        ++i;
    }
    if (j > 0) {
        arr[k][j] = '\0';
        ++k;
    }
    *n = k;
    return k;
}

// Helper to build tree from level-order array
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode** nodes = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    for (int i = 0; i < n; ++i) nodes[i] = NULL;
    struct TreeNode* root = newNode(atoi(arr[0]));
    nodes[0] = root;
    int idx = 1;
    for (int i = 0; i < n && idx < n; ++i) {
        if (!nodes[i]) continue;
        // left child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->left = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->left;
        }
        idx++;
        // right child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->right = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->right;
        }
        idx++;
    }
    free(nodes);
    return root;
}

// Helper to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// The required function
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) return false;
    if (root->val == targetSum && root->left == NULL && root->right == NULL) return true;
    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}

int main() {
    struct {
        const char* tree;
        int targetSum;
    } tests[] = {
        {"[5,4,8,11,null,13,4,7,2,null,null,null,1]", 22},
        {"[1,2,3]", 5},
        {"[]", 0}
    };
    int num_cases = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s, targetSum = %d\n", tests[i].tree, tests[i].targetSum);
        char arr[MAX_NODES][16];
        int n = 0;
        parseInput(tests[i].tree, arr, &n);
        struct TreeNode* root = buildTree(arr, n);
        bool result = hasPathSum(root, tests[i].targetSum);
        printf("Output: %s\n", result ? "true" : "false");
        deleteTree(root);
    }
    return 0;
}
