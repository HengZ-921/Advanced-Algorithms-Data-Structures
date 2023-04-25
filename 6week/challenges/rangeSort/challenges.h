#ifndef CHALLENGES_H
#define CHALLENGES_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

typedef long int lint;

void *safeMalloc(int n);
lint readNumber();

void fillIntv ( int n, lint **ar );
void fillQr ( int m, lint **ar );
void qkSort( short base, short row, int begin, int end, lint **ar);
int loSearch(lint x, lint *ar, int n);
int hiSearch(lint x, lint *ar, int n);

#endif