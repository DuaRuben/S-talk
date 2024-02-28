#include "printerThread.h"
#include "pthread_helpers.h"
#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define MAX_LEN 1024

pthread_t threadPr;
List *listptr1;

void *printerThread(void *unused)
{
    while (1)
    {
        pthread_mutex_lock(&recieverListMutex);
        {
            //while (!list) // while list is empty work in kardia jaaye somehow
            pthread_cond_wait(&recieverListToMonitorCond, &recieverListMutex);

            //List_first(listptr1);
            char *y = List_curr(listptr1);
            //printf("Message Recieved: \n\n'%s'\n", y);
            char *x = List_remove(listptr1);
            //printf("lCount: %d", List_count(listptr1));
            printf("Message Recieved: \n\n'%s'\n", x);
        }
        pthread_mutex_unlock(&recieverListMutex);
    }
}

void Printer_init(List *recieverList)
{
    listptr1 = recieverList;
    pthread_create(&threadPr, NULL, printerThread, NULL);
}
void Printer_shutdown()
{
    pthread_join(threadPr, NULL);
}
