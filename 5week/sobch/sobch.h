#ifndef SOBCH_H
#define SOBCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* We first create a hashtable and fill it with the inputs, with chaining too avoid collision,
 * the time complexity of inserting data is around O(1). The time complexity for data retrieving 
 * is also approxiamtely O(1).
 * Therefore, the overall time complexity is O(n + m).
 */

typedef struct ListNode* List;

struct ListNode {
  char *name;
  long int time;
  List next;
};

void *safeMalloc(int n);
int readNumber();
char *readName();

int hashnum (char *T, int p);
void buildHash( int n, int p, List *table);
List addItem(char *s, int t, List li);
void freeList(List li);

int retrieve (char *s, List li);
void reportTime ( int m, int p, List *li );

#endif