#include "senderThread.h"
#include "pthread_helpers.h"
#include "list.h"
#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

pthread_t thread4;
List *listptr4;
int sendersocket;

void *senderThread(void *unused)
{
    struct addrinfo* ptrToFriendMachineAddr = getfriendMachineAddr();

    while (1)
    {
        pthread_mutex_lock(&inputSenderMutexVar);
        {
            // wait for signal
            pthread_cond_wait(&inputSenderCondVar, &inputSenderMutexVar);

            // remove from list
            char msg[MAX_LEN];
            List_first(listptr4);
            char *temp = List_remove(listptr4);
            if (temp != NULL)
            {
                strcpy(msg, temp);
                free(temp);
            }

            // if msg is !
            if (msg[0] == '!' && msg[1] == '\0')
            {
                pthread_mutex_lock(&exitProgramMutexVar);
                {
                    fputs("Exiting Program...\n", stdout);
                    sendto(sendersocket, msg, strlen(msg), 0, ptrToFriendMachineAddr->ai_addr, ptrToFriendMachineAddr->ai_addrlen);
                    pthread_cond_signal(&exitProgramCondVar);
                }
                pthread_mutex_unlock(&exitProgramMutexVar);
            }
            else
            {
                sendto(sendersocket, msg, strlen(msg), 0, ptrToFriendMachineAddr->ai_addr, ptrToFriendMachineAddr->ai_addrlen);
            }
        }
        pthread_mutex_unlock(&inputSenderMutexVar);
    }
}

void Sender_init(List *senderList)
{
    sendersocket = getSocket();
    listptr4 = senderList;
    pthread_create(&thread4, NULL, senderThread, NULL);
}

void Sender_shutdown()
{
    pthread_cancel(thread4);
    pthread_join(thread4, NULL);
}
