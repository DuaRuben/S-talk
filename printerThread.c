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
            pthread_cond_wait(&recieverListToMonitorCond, &recieverListMutex);

            List_first(listptr1);
            char *x = List_remove(listptr1);

            // if msg reciever is !
            if (*x == '!' && *(x + 1) == '\0')
            {
                fputs("Connection Terminated From Other The Host:\n", stdout);
                pthread_mutex_lock(&exitProgramMutexVar);
                {
                    pthread_cond_signal(&exitProgramCondVar);
                }
                pthread_mutex_unlock(&exitProgramMutexVar);
            }
            else
            {
                fputs("\n[", stdout);
                fputs(getFriendMachineName(), stdout);
                fputs("]: ", stdout);
                fputs(x, stdout);
                fputs("\n", stdout);
            }
            free(x);
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
    pthread_cancel(threadPr);
    pthread_join(threadPr, NULL);
}