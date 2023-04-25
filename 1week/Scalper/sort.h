#ifndef SORT_H
#define SORT_H

typedef int lint;
lint readNumber();
void swap(lint i, lint j, lint arr[]);
lint partition(lint length, lint arr[], char sell[]);
void quickSort(lint length, lint arr[], char sell[]);
void sortDate(lint websiteNum, lint dateArray[], char sellArray[]);
void findMax(lint websiteNum, lint dateArray[], char sellArray[]);

#endif