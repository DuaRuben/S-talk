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


void *recieverThread(void *unused) //we'll signal this when we get input from keyboard, hence add cond_wait for thread r
{
   //mutex lock here
   //pthread_cond_wait(&recCond); // pass mutex also

    while (1) {
        //waitForRecieverSignal();

        // init addr for rec
        struct sockaddr_in sinRemote;

        // i dont think we need this here because not sending
        memset(&sinRemote, 0, sizeof(sinRemote));
        sinRemote.sin_family = AF_INET;
        sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
        sinRemote.sin_port = htons(12345);
        unsigned int sin_len = sizeof(sinRemote);


        char messageRx[MAX_LEN];
        int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *)&sinRemote, sin_len);
        int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termRx] = 0;

        //unlock mutexafter append
        // signal waiter in printer thread
        // hell get mutex
        // mutex for wach pipeline

        if (strlen(messageRx) > 0)
            appendToList(messageRx);

        // i can call waitforsinganl here when returning from 
        // /printing on screen will signal backto move forward
    }

}

void appendToList(char* messageRx) { // should check here if nodes avail, wait for signal i think should work in this case
    pthread_mutex_lock(&recieverListMutex);
        {
            List_append(list, messageRx);
            pthread_cond_signal(&recieverListToMonitorCond); // signal printer thread
        }
    pthread_mutex_unlock(&recieverListMutex);
}

// void waitForRecieverSignal() {
//    while (1) {
//         pthread_cond_wait(&recieverListAppendCond, &recieverListMutex);
//         break;
//    }
// }

void Reciever_init(List* recieverList, int socket)
{
    //pthread_cond_init(&recCond);
    //Copying List
    list = recieverList;
    s = socket;
    pthread_create(&thread, NULL, recieverThread, NULL);
}
void Reciever_shutdown()
{
    pthread_join(thread, NULL);
}
