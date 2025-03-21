#include "pthread_helpers.h"
#include "main.h"
#include "list.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

static List *listptr2;
pthread_t threadRec;
struct sockaddr_in sinRemote2;
static int s;

void *recieverThread(void *unused) // we'll signal this when we get input from keyboard, hence add cond_wait for thread r
{
   unsigned int sin_len = sizeof(sinRemote2);
    while (1)
    {
        char messageRx[MAX_LEN] = {'\0'};
        int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *)&sinRemote2, &sin_len);
        int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termRx] = 0;

        char *temp = strdup(messageRx);
        pthread_mutex_lock(&recieverListMutex);
        {
            List_append(listptr2, temp);
            pthread_cond_signal(&recieverListToMonitorCond); // signal printer thread
        }
        pthread_mutex_unlock(&recieverListMutex);
    }
}

void Reciever_init(List *recieverList)
{
    // pthread_cond_init(&recCond);
    // Copying List
    listptr2 = recieverList;
    s = getSocket();
    pthread_create(&threadRec, NULL, recieverThread, NULL);
}
void Reciever_shutdown()
{
    pthread_cancel(threadRec);
    pthread_join(threadRec, NULL);
}

// scp -P 24 my_file_name.c user_name@asb9804u-a01.csil.sfu.ca:~/target_folder
