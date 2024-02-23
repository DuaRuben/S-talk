#include "recieverThread.h"
#include "list.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

List* list;
pthread_t thread;
struct sockaddr_in sinRemote;
int s;
pthread_cond_t recieverToPrintCond;
pthread_mutex_t recieverToPrintMutex;



void *recieverThread(void *unused) //we'll signal this when we get input from keyboard, hence add cond_wait for thread r
{
   //mutex lock here
   //pthread_cond_wait(&recCond); // pass mutex also
    struct sockaddr_in sinRemote;
    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
    sinRemote.sin_port = htons(12345);
    unsigned int sin_len = sizeof(sinRemote);
    char messageRx[MAX_LEN];
    int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *)&sinRemote, sin_len);
    int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
    messageRx[termRx] = 0;
    pthread_mutex_lock(&recieverToPrintMutex);
    {
        List_append(list,messageRx);
        pthread_cond_signal(&recieverToPrintCond);
    }
    pthread_mutex_unlock(&recieverToPrintMutex);
    //unlock mutexafter append
    // signal waiter in printer thread
    // hell get mutex
    // mutex for wach pipeline

}
void Reciever_init(List* recieverList, int socket, pthread_cond_t condition, pthread_mutex_t mutex)
{
    //pthread_cond_init(&recCond);
    //Copying List
    s = socket;
    list = recieverList;
    recieverToPrintCond = condition;
    recieverToPrintMutex = mutex;
    pthread_create(&thread, NULL, recieverThread, NULL);
}
void Reciever_shutdown()
{
    pthread_join(thread, NULL);
}
