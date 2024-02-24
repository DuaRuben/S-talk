#include "printerThread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define MAX_LEN 1024

pthread_t thread;
pthread_cond_t recieverToPrintCond;
pthread_mutex_t recieverToPrintMutex;
List* list;


void * printerThread(void * unused){

    pthread_mutex_lock(&recieverToPrintMutex);
    {
        pthread_cond_wait(&recieverToPrintCond,&recieverToPrintMutex);
        char* x = List_remove(list);
        printf("Message Recieved: \n\n'%s'\n", x);
    }
    pthread_mutex_unlock(&recieverToPrintMutex);
}
void Printer_init(List* recieverList,pthread_cond_t condition,pthread_mutex_t mutex){
    list = recieverList;
    recieverToPrintCond = condition;
    recieverToPrintMutex = mutex;
    pthread_create(&thread,NULL,printerThread,NULL);
}
void Printer_shutdown(){
    pthread_join(thread,NULL);
}
