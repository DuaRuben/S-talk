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

static List* listptr2;
pthread_t threadRec;
struct sockaddr_in sinRemote2;
static int s;


void *recieverThread(void *unused) //we'll signal this when we get input from keyboard, hence add cond_wait for thread r
{
   //mutex lock here
   //pthread_cond_wait(&recCond); // pass mutex also
   
        memset(&sinRemote2, 0, sizeof(sinRemote2));
        sinRemote2.sin_family = AF_INET;
        sinRemote2.sin_addr.s_addr = inet_addr("142.58.15.67");
        sinRemote2.sin_port = htons(12345);
       unsigned int sin_len = sizeof(sinRemote2);

    while (1) {
        //waitForRecieverSignal();

        // init addr for rec

        // i dont think we need this here because not sending



        char messageRx[MAX_LEN];
        printf("Here");
        int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *)&sinRemote2, sin_len);
        printf("Not Here");
        int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termRx] = 0;

        //unlock mutexafter append
        // signal waiter in printer thread
        // hell get mutex
        // mutex for wach pipeline
	    char* temp = strdup(messageRx);
       	pthread_mutex_lock(&recieverListMutex);
        {
            List_append(listptr2, temp);
            pthread_cond_signal(&recieverListToMonitorCond); // signal printer thread
        }
    	pthread_mutex_unlock(&recieverListMutex);
        free(temp);
        
        //List_curr(listptr2);
        //if (strlen(messageRx) > 0)
            //appendToList(messageRx);

        // i can call waitforsinganl here when returning from 
        // /printing on screen will signal backto move forward
    }

}

void appendToList(char* messageRx) { // should check here if nodes avail, wait for signal i think should work in this case
    pthread_mutex_lock(&recieverListMutex);
        {
            List_append(listptr2, &messageRx);
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
    listptr2 = recieverList;
    s = socket;
    pthread_create(&threadRec, NULL, recieverThread, NULL);
}
void Reciever_shutdown()
{
    pthread_join(threadRec, NULL);
}

//scp -P 24 my_file_name.c user_name@asb9804u-a01.csil.sfu.ca:~/target_folder
