#ifndef RESTAURANT_H
#define RESTAURANT_H

/* In this chanllenge, we are looking for the grid point which minimizes the sum of Mahattan
 * distance to all the restaurant grid points. The solution to this problem is to find the medians
 * of x coordinates and y coordinates.
 *
 * In the function record, we record all the y coordinates in a r-element array. Then quickSelect
 * is used to find the median of this array. It is well known that the time complexity of
 * quickSelect algorithm is bounded to O(n), with randomly selected pivots. As for x median, we can
 * get the number while reading the inputs.
 * 
 * Therefore, the overall time complexity is O(N^2 + r), where O(N^2) is the time complexity of
 * reading inputs. And the memory complexity is O(r), which is used to store the y coordinate array.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

void *safeMalloc(int n);
int readNumber();
char readChar();

int record (int N, int r, int *y);

void swap ( int *ar, int a, int b );
int partition(int *ar, int l, int r);
int quickSelect (int *ar, int l, int r, int i);

#endif
