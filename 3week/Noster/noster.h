#ifndef NOSTER_H
#define NOSTER_H

/* In this chanllenge, we are aiming for the longest non-decreasing subsequence of the inputs.
 * The algorithm of this assignment is adpated from the algorithm of C. Schensted (1961)
 * (DOI: https://doi.org/10.4153/CJM-1961-015-3).
 *
 * This is a dynamic programming algorithm, the array idxAr stores the indices of the last elements of 
 * the non-decreasing subsequence of length n, and in array preAr, the indices of the precursor
 * elements are stored.
 * Upon each input, the array idxAr is searched to update the array of last elements of non-
 * decreasing subsequences. By using binary search, this search process can be accelarated to
 * O(log(n)). The worst case is the whole input is a non-decreasing subsequence, so that the whole
 * array will be stored in array idxAr and searched for n times, and thus the time complexity of
 * the algorithms is bound to O(n log(n)).
 * The memory complexity is O(n) since three arrays of size n are allocated to retrieve the elements
 * in the longest non-decreasing subsequence.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void *safeMalloc(int n);
int readNumber();

int improve( int L, int preidx, int *idx, int *ar );
int binarySearch ( int i, int n, int *ar, int * idxAr, int *preAr);
void nosterRelease( int N );

#endif
