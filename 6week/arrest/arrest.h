#ifndef ARREST_H
#define ARREST_H

#include <stdlib.h>
#include <stdio.h>

/* The protestors who are on the edge or connect with those on the edge cannot be arrested,
 * therefore, we need to traverse the graph to find and mark these protestors.
 * In this program, we used DFS to traverse the graph, and the time complexity of this method
 * is bound to O( n^2 ).
 * Before performing the DFS, we need to read and store the inputs, which is also O( n^2 ).
 * At last, we need to count the unmarked protestors, also O( n^2 ).
 * So, overall the time complexity of the algorithm is bound to O( n^2 ) and the O( n^2 ) memory is
 * required to store the inputs.
 */

void *safeMalloc( int n );
short readNumber();
char getSymbol ();

void fillGraph ( short n, char **G );
void dfs (char **G, short x, short y, short n);
void searchGraph ( short n, char **G );
void countArrest ( short n, char **G );

#endif