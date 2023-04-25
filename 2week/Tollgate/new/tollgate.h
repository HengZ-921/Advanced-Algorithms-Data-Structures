#ifndef TOLLGATE_H
#define TOLLGATE_H

/* In this chanllenge, two methods are used to find the lowest cost, brute force and dynamic.
 * 
 * If the number of tollgates n <= (h + c), then there are at most 100 tollgates,
 * and the skip can only happen once at most, so the worst case is consider ( c + 1 ) skip/pay
 * configurations. Therefore, the time complexity of brute force methods is bound to O(c),
 * and the memory complecity is bound to O(n), since we need to store the price of all the tollgates.
 * 
 * If the input is long, n > (h + c), then we use dynamic programming, the memory complexity is
 * bound to O(h + c), since we only store the sum of payment and the states in two arrays,
 * both with (h + c + 1) elemets.
 * We first use function init to initilaize the two arrays, Sums and States, the time complexity of
 * this function is bound to O( (h + c) ^ 2 ).
 * Then for the rest ( n - h - c ) inputs, we use function update to find the lowest payment before
 * each tollgate. The time complexity of a single run of this function is O( h + c ).
 * Therefore, the overall time complexity of this dynamic method is O ( n * (h + c) ).
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void *safeMalloc(int n);
int readNumber();

long int bruteSkip (int *pl, int h, int c, int num);
void shortway(int h, int c, int N);

void init (long int *s, int *t, int h, int c);
void update (long int *s, int *t, int h, int c, int N);
void longway(int h, int c, int N);



#endif
