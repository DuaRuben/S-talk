#include "printerThread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_t thread;
void * printerThread(void * unused){
    //printf("Message Recieved (%d bytes): \n\n'%s'\n", bytesRx, messageRx);
}
void Printer_init(){
    pthread_create(&thread,NULL,printerThread,NULL);
}
void Printer_shutdown(){
    pthread_join(&thread,NULL);
}
