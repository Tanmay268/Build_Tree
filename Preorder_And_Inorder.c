/*
Implement a program that takes the input of (i) a preorder expression and (ii) an 
inorder expression, and construct the corresponding Binary tree.
*/

#include <stdio.h>
#include <stdlib.h>
struct Tree {
    char data;
    struct Tree *left;
    struct Tree *right;
};

struct Tree *Create_node(char val) {
    struct Tree *newNode = (struct Tree*)malloc(sizeof(struct Tree));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void PrintInOrder(struct Tree *root) {
    if (root != NULL) {
        PrintInOrder(root->left);
        printf("%c\t", root->data);
        PrintInOrder(root->right);
    }
}

int search(char arr[], int strt, int end, char value) {
    for (int i = strt; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1; 
}

struct Tree *BuildTree(char inorder[], char preorder[], int inStart, int inEnd) {
    static int preIndex = 0;
    if (inStart > inEnd) {
        return NULL;
    }
    struct Tree *node = Create_node(preorder[preIndex++]);
    if (inStart == inEnd) {
        return node;
    }
    int inIndex = search(inorder, inStart, inEnd, node->data);
    node->left = BuildTree(inorder, preorder, inStart, inIndex - 1);
    node->right = BuildTree(inorder, preorder, inIndex + 1, inEnd);
    return node;
}

int main() {
    char in[] = { 'D', 'B', 'E', 'A', 'F', 'C' };
    char pre[] = { 'A', 'B', 'D', 'E', 'C', 'F' };
    int len = sizeof(in) / sizeof(in[0]);
    struct Tree* root = BuildTree(in, pre, 0, len - 1);

    printf("Inorder traversal of the constructed tree is:\n");
    PrintInOrder(root);
    return 0;
}
