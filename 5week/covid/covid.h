#ifndef COVID_H
#define COVID_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

/* In this challenge, we used dynamic programming, an m-element array are allocated to store the 
 * largest number of zombies in previous routes.
 * On each grid point, the largest sum can be reached on this grid point are calculated based on 
 * previous results, with the reading of new numbers. At the last cell, we can get the largest number
 * of zombies can be produced in the whole map.
 * Therefore, the time complexity is bound to O(n * m) and the result can be calculated on the fly.
 * The memory complexity is bound to O(m).
 */

void *safeMalloc(int n);
int readNumber();

void initialize (int m, int *ar);
void propagate (int n, int m, int *ar);

#endif