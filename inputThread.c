#include "inputThread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "pthread_helpers.h"
#define MAX_LEN 1024

pthread_t thread3;
List *listptr3;

void *inputThread(void *unused)
{
    while (1)
    {
        // take input from user
        char sendMsg[MAX_LEN];
        fgets(sendMsg, sizeof(sendMsg), stdin);

        // convert into character string
        unsigned int length = strlen(sendMsg);
        if (length > 0 && sendMsg[length - 1] == '\n')
        {
            sendMsg[length - 1] = '\0';
        }
        // Make a pointer to the sendMsg string
        char *Msg = strdup(sendMsg);

        // add to the list
        //  signal senderThread to work on it
        pthread_mutex_lock(&inputSenderMutexVar);
        {
            List_append(listptr3, Msg);
            pthread_cond_signal(&inputSenderCondVar);
        }
        pthread_mutex_unlock(&inputSenderMutexVar);
    }
}
void Input_init(List *senderList)
{
    listptr3 = senderList;
    pthread_create(&thread3, NULL, inputThread, NULL);
}
void Input_shutdown()
{
    pthread_cancel(thread3);
    pthread_join(thread3, NULL);
}
