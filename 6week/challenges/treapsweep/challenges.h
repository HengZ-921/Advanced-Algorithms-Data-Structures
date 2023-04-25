#ifndef CHALLENGES_H
#define CHALLENGES_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* We used line sweep algorithm to find all intervals overlappint with the query, this requires to
 * sort all the starting points and end points and querys in a stable manner. Here, we used mergesort,
 * so the time complexity is (2*n + m) * log(2*n + m).
 * 
 * Then, we can easily get all the interals at each query, and we used an order statistic tree
 * to retrieve the kth smallest interval in the array. The maintaining and searching of a binary
 * tree is bound to O(h). Since we used treap as the order statistic tree, we may get an
 * approximately balances BST. So, a single operation on the BST is bound to O(log(n)).
 * 
 * In the line sweep algorithm, we need to go through all starting points, ending points and
 * query, so in the worst case, we need (2*n + m) operations on BST.
 * Therefore, the overall time complexity is (2*n + m) * log(2*n + m) + (2*n + m) * log(n), which
 * is bound to O(n * log(n)).
 */

#define QINF 300000
#define EINF 600000

typedef long int lint;
typedef struct TreeNode* BSTree;
struct TreeNode {
    lint key;
    int size, prior;
    BSTree lc, rc;
};

void *safeMalloc(int n);
lint readNumber();
void mergeSort(lint *arr, int *num, int l, int r);
int *linesweep ( int n, int m, lint *starts, lint *ends, lint *intv, lint *kqrs);

BSTree newNode (lint t);
BSTree addNode (BSTree nd, lint t);
BSTree delNode (BSTree rt, lint t);
lint kthSmallest (BSTree rt, lint k);
void findKthVal ( int n, int m, int *ords, lint *intv, lint *kqrs );
void freeTree( BSTree rt );

void inorder(BSTree root);

#endif