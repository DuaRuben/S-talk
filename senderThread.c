#include "senderThread.h"
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
int s;
pthread_cond_t inputToSendCond;
pthread_mutex_t inputToSendMutex;

void *senderThread(void *unused) // we'll signal this when we get input from keyboard, hence add cond_wait for thread r
{
    // mutex lock here
    // pthread_cond_wait(&recCond); // pass mutex also

    struct sockaddr_in sinRemote;
    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
    sinRemote.sin_port = htons(12345);
    unsigned int sin_len = sizeof(sinRemote);

    pthread_mutex_lock(&inputToSendMutex);
    {
        char *msg[100];
        List_first(list);
        char *temp = List_remove(list);
        strcpy(temp, msg);
        unsigned int sin_len = sizeof(sinRemote);
    }
    pthread_mutex_unlock(&inputToSendMutex);
    sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&sinRemote, sin_len);
    // unlock mutexafter append
    //  signal waiter in printer thread
    //  hell get mutex
    //  mutex for wach pipeline
}

void Sender_init(List *senderList, int socket, pthread_cond_t condition, pthread_mutex_t mutex)
{
    // pthread_cond_init(&recCond);
    // Copying List
    s = socket;
    list = senderList;
    inputToSendCond = condition;
    inputToSendMutex = mutex;
    pthread_create(&thread, NULL, senderThread, NULL);
}

void Sender_shutdown()
{
    pthread_join(thread, NULL);
}