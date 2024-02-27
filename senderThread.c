#include "senderThread.h"
#include "pthread_helpers.h"
#include "list.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

pthread_t thread;
List *list;
struct sockaddr_in sinRemote;
int socket;

void *senderThread(void *unused)
{
    // setup sinRemote
    struct sockaddr_in sinRemote;
    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
    sinRemote.sin_port = htons(12345);
    unsigned int sin_len = sizeof(sinRemote);

    pthread_mutex_lock(&inputSenderMutexVar);
    {
        //wait for signal
        pthread_cond_wait(&inputSenderCondVar,&inputSenderMutexVar);

        //remove from list
        char msg[MAX_LEN];
        List_first(list);
        char *temp = List_remove(list);
        if(temp!=NULL){
            strcpy(msg,temp);
            free(temp);
        }

        //send Msg
        sendto(socket, msg, strlen(msg), 0, (struct sockaddr *)&sinRemote, sin_len);
    }
    pthread_mutex_unlock(&inputSenderMutexVar);
}

void Sender_init(List *senderList, int sockt)
{
    socket = sockt;
    list = senderList;
    pthread_create(&thread, NULL, senderThread, NULL);
}

void Sender_shutdown()
{
    pthread_join(thread, NULL);
}