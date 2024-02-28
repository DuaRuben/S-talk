#include "main.h"
#include "pthread_helpers.h"
#include "list.h"
#include "inputThread.h"
#include "printerThread.h"
#include "recieverThread.h"
#include "senderThread.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define MAX_LEN 1024
#define PORT 22110


List *senderList;
List *recieverList;
struct sockaddr_in localsocket;

int main()
{
    initialize_pthreads();
    senderList = List_create();
    recieverList = List_create();
    if(senderList == NULL || recieverList == NULL){
        printf("Error! List(s) could not be created.\nExiting the Program\n");
        return 1;
    }
    // Reciever

    memset(&localsocket, 0, sizeof(localsocket));
    localsocket.sin_family = AF_INET;
    localsocket.sin_addr.s_addr = htonl(INADDR_ANY);
    localsocket.sin_port = htons(12346);

    // Creating a socket
    int sockt = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockt == -1)
    {
        printf("Error!Socket creation Failed\nExiting the Program\n.");
        return 2;
    }

    // Binding a socket
    int x = bind(sockt, (struct sockaddr *)&localsocket, sizeof(struct sockaddr_in));
    if (x == -1)
    {
        printf("Error!Cannot bind a socket");
        return 3;
    }

    // struct sockaddr_in addr;
    // memset(&addr, 0, sizeof(addr));
    // addr.sin_family = AF_INET;
    // addr.sin_addr.s_addr = inet_addr("142.58.15.216");
    // addr.sin_port = htons(12346);

    // // memset(&addr.sin_zero,'\0', 8);
    // int s = socket(AF_INET, SOCK_DGRAM, 0);
    // int x = bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    // //if(x ==0){
    // //    printf("Success");
    // //}
    // recieverThread
    Reciever_init(recieverList, sockt);
    Printer_init(recieverList);
    
    Input_init(senderList);
    Sender_init(senderList, sockt);
    // PrinterThread
    // inputThread
    // senderThread

    // // waiting for screen
    // struct sockaddr_in sinRemote;

    // memset(&addr, 0, sizeof(addr));
    // sinRemote.sin_family = AF_INET;
    // sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
    // sinRemote.sin_port = htons(12345);

    // char* msg[100];
    // scanf("%99s", msg);
    // char messageTx[MAX_LEN];
    // strcpy(messageTx, msg);
    // unsigned int sin_len = sizeof(sinRemote);

    // sendto(s, messageTx , strlen(messageTx), 0, (struct sockaddr *) &sinRemote, sin_len);

    // sin_len = sizeof(sinRemote);
    // char messageRx[MAX_LEN];
    // int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *) &sinRemote,
    //          sin_len);

    // int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
    // messageRx[termRx] = 0;
    // printf("Message Recieved (%d bytes): \n\n'%s'\n", bytesRx, messageRx);


    Reciever_shutdown();
    Input_shutdown();
    Printer_shutdown();
    Sender_shutdown();
}
