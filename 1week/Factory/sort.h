#ifndef SORT_H
#define SORT_H

typedef long int lint;
typedef long long int lli;

lli readNumber();
lint readFactory();
void swap(lint i, lint j, lint arr[]);
lint partition(lint length, lint tarr[], lint parr[]);
void quickSort(lint length, lint arr[], lint parr[]);
void sortTime(lint facNum, lint prodArr[], lint timeArr[]);
void startProduction(lint facNum, lli requestNum, lint timeArr[], lint prodArr[]);
void bubbleSort(lint length, lint starr[], lint parr[], lint tarr[]);

void *safeMalloc(long int n);

#endif