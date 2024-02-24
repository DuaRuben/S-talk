#include "printerThread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define MAX_LEN 1024

pthread_t thread;
List* list;


void * printerThread(void * unused){

    while (1) {
        waitForRecieverSignal();
        pthread_mutex_lock(&recieverListMutex);
        {
            pthread_cond_wait(&recieverListToMonitorCond, &recieverListMutex);
            List_first(list);
            char* x = List_remove(list);
            printf("Message Recieved: \n\n'%s'\n", x);
        }
        pthread_mutex_unlock(&recieverListMutex);
    }
} 

void waitForRecieverSignal() {
   while (1) {
        pthread_cond_wait(&recieverListToMonitorCond, &recieverListMutex);
        break;
   }
}
void Printer_init(List* recieverList) {
    list = recieverList;
    pthread_create(&thread,NULL,printerThread,NULL);
}
void Printer_shutdown(){
    pthread_join(thread,NULL);
}
