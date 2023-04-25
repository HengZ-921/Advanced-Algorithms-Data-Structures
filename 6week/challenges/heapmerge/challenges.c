#include "challenges.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

lint readNumber() {
  short i = 0;
  char c = getchar(), line[12];
  while ( 1 ) {
    if ( isdigit(c) ) { line[i] = c; i++; }
    c = getchar();
    if ( i > 0 && (!isdigit(c)) ) { break; }
  }
  line[i] = '\0';
  return atol(line);
}

int *linesweep ( int n, int m, lint *starts, lint *ends, lint *intv, lint *kqrs) {
  int i; lint *days = safeMalloc( (2 * n + m) * sizeof(lint)); 
  for (i = 0; i < m; i++ ) { kqrs[i] = readNumber(); days[i + n] = readNumber(); }
  for (i = 0; i < n; i++ ) {
    days[i] = starts[i]; days[i + n + m] = ends[i]; intv[i] = ends[i] - starts[i] + 1;
  }
  free(starts); free(ends);
  int *ords = safeMalloc((2 * n + m) * sizeof(int));
  for (i = 0; i < n; i++ ) { ords[i] = i; ords[i + n + m] = i + EINF; }
  for (i = 0; i < m; i++ ) { ords[i + n] = i + QINF; }  
  mergeSort(days, ords, 0, 2 * n + m - 1); free(days);
  return ords;
}

BSTree newNode (lint t) {
  BSTree nd = safeMalloc(sizeof(struct TreeNode));
  nd->key = t; nd->size = 1; nd->lc = NULL; nd->rc = NULL;
  return nd;
}

BSTree addNode (BSTree nd, lint t) {
  if (nd == NULL) { return newNode(t); }
  if (t > nd->key) { nd->rc = addNode(nd->rc, t); }
  else { nd->lc = addNode(nd->lc, t); }
  nd->size += 1;
  return nd;
}

BSTree delNode (BSTree rt, lint t) {
  if ( rt == NULL ) { return rt; }
  rt->size -= 1;
  if ( rt->key < t ) { rt->rc = delNode(rt->rc, t); return rt; }
  else if ( rt->key > t ) { rt->lc = delNode(rt->lc, t); return rt; }
  // If one of the children is empty
  if ( rt->rc == NULL ) { BSTree child = rt->lc; free(rt); return child; }
  else if ( rt->lc == NULL ) { BSTree child = rt->rc; free(rt); return child; }
  // If both children exist
  else {
    BSTree sucP = rt, suc = rt->rc; // Find successor
    while ( suc->lc != NULL ) { sucP = suc; suc = suc->lc; sucP->size -= 1; }
    if ( sucP != rt ) { sucP->lc = suc->rc; }
    else { sucP->rc = suc->rc; }
    rt->key = suc->key; free(suc); return rt;
  }
}

lint kthSmallest (BSTree rt, lint k) {
  int cur = 1;
  if (rt->lc != NULL) { cur += rt->lc->size; }
  if ( cur == k ) { return rt->key; }
  else if ( cur > k ) { return kthSmallest(rt->lc, k); }
  else { return kthSmallest(rt->rc, k - cur); }
}

void freeTree( BSTree rt ) {
  if (rt == NULL) { return; }
  freeTree(rt->lc); freeTree(rt->rc);
  free(rt);
}

void findKthVal ( int n, int m, int *ords, lint *intv, lint *kqrs ) {
  BSTree bst = NULL; int i, count = m;
  for (i = 0; i < 2 * n + m - 1; i++) {
    if ( ords[i] < QINF ) { bst = addNode(bst, intv[ords[i]]); }
    else if ( ords[i] >= EINF ) { bst = delNode(bst, intv[ords[i] - EINF]); }
    else {
      if ( bst->size < kqrs[ords[i] - QINF] ) { kqrs[ords[i] - QINF] = -1; }
      else { kqrs[ords[i] - QINF] = kthSmallest(bst, kqrs[ords[i] - QINF]); }
      --count;
    }
    if ( !count ) { freeTree(bst); break; }
  }
  free(ords); free(intv);
}

void inorder(BSTree root) {
	if (root != NULL) {
		inorder(root->lc);
		printf("S %d: %ld| ", root->size, root->key);
		inorder(root->rc);
	}
}

void merge(lint *arr, int *num, int p, int q, int r) {
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1, n2 = r - q, i, j, k = p;
  lint *La = safeMalloc( n1 * sizeof(lint) ), *Ra = safeMalloc( n2 * sizeof(lint) );
  int *Ln = safeMalloc( n1 * sizeof(int) ), *Rn = safeMalloc( n2 * sizeof(int) );

  for (i = 0; i < n1; i++) { La[i] = arr[p + i]; Ln[i] = num[p + i]; }
  for (j = 0; j < n2; j++) { Ra[j] = arr[q + 1 + j]; Rn[j] = num[q + 1 + j]; }
  i = 0, j = 0;
  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (La[i] <= Ra[j]) { arr[k] = La[i]; num[k] = Ln[i]; i++; }
    else { arr[k] = Ra[j]; num[k] = Rn[j]; j++; } k++;
  }
  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) { arr[k] = La[i]; num[k] = Ln[i]; i++; k++; }
  while (j < n2) { arr[k] = Ra[j]; num[k] = Rn[j]; j++; k++; }

  free(La); free(Ln); free(Ra); free(Rn);
}

void mergeSort(lint *arr, int *num, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, num, l, m); mergeSort(arr, num, m + 1, r);
    merge(arr, num, l, m, r);
  }
}
