#ifndef GARBAGE_H
#define GARBAGE_H
#define MAXLOAD 100001

#include <stdlib.h>
#include <stdio.h>

/* This problem is a maximum flux problem, with multisource and multisink.
 * To Solve this problem, we first merged the multisource to one source connected to 
 * all middle nodes which are orginally connected to different source nodes, 
 * and treat the multisink in the same manner. This can be done during the reading of matrix input,
 * which is bound to O(n^2).
 * Then, we used Ford Fulkerson algorithm with BFS to find the path between the synthetic source 
 * and synthetic sink. It has been proven that the time complexity of this algorithm for
 * the worst case is O(E * V^3) when it is implemented in adjacency matrix, and in our implementation
 * V = n, E = V^2 / 2 in the worst case.
 * Therefore, the overall time complexity of the program is bound to O(n^5).
 * We also need O(n^2) memory to store the adjacency matrix.
 */

typedef struct Queue {
  short *array;
  short back;
  short front;
  short size;
} Queue;
typedef long long int lint;

Queue newQueue(short s);
void enqueue(short item, Queue *qp);
short dequeue(Queue *qp);

void *safeMalloc( int n );
char *markPortals ( short n, short s, short t);
int **fillGraph ( int n, int s, int t, int m, char *vmarks );
char BFS ( int **G, short m, short *prev );
void FordFulkerson ( int **G, short m );

#endif