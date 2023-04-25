#ifndef STICK_H
#define STICK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* In this challenge, we used best fit algorithm to fill all the sticks. The files are always put in
 * the stick with least rest space.
 * Since the file size are all exponents of 2, so there are at most log(10^8) = 26 file sizes, 
 * and thus the inputs can be easily sorted by counting sort.
 * Also the best-fit packing can also be implemented in different batches by calculating the number
 * of sticks with the same rest space.
 * The fileStore deals with all files of the same size, tries to put them in the stick with least
 * remaining memory. The worst case is that all the types of sticks are transversed, and after store
 * the file in one type of stick, the remaining stick memory is sorted for next best-fit packing,
 * so the time complexity of this function is bounded to O(log(s)^2).
 * There are log(s) different file sizes. Therefore, the time complexity of the algorithm
 * is bound to O(log(s)^3).
 * In the program, four arrays of size log(s) are allocated to store the number and size of 
 * files and sticks. So, the memory complexity are also bound to O(log(s)).
*/

void *safeMalloc(int n);
int readNumber();

void swap(int i, int j, int *arr, int *num);
int partition(int length, int *arr, int *num);
void quickSort(int length, int *arr, int *num);

void combine (int L, int *arr, int *num);
void fileStore (int *type, int size, int amount, int *restMem, int *copies);
void firstFitStore ( int s, int f );

#endif