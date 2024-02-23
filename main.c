#include "main.h"
#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "recieverThread.h"

#define MAX_LEN 1024
#define PORT 22110

List* senderList;
List* recieverList;



int main()
{
    senderList = List_create();
    recieverList = List_create();

    //recieverThread
    Reciever_init(recieverList);
    //PrinterThread
    //inputThread
    //senderThread

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("142.58.15.216");
    addr.sin_port = htons(12346);

    // memset(&addr.sin_zero,'\0', 8);
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    int x = bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    //if(x ==0){
    //    printf("Success");
    //}
    while (1)
    {
        
        // waiting for screen
        struct sockaddr_in sinRemote;
    
        memset(&addr, 0, sizeof(addr));
        sinRemote.sin_family = AF_INET;
        sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
        sinRemote.sin_port = htons(12345);

        char* msg[100];
        scanf("%99s", msg);
        char messageTx[MAX_LEN];
        strcpy(messageTx, msg);
        unsigned int sin_len = sizeof(sinRemote);
        
        sendto(s, messageTx , strlen(messageTx), 0, (struct sockaddr *) &sinRemote, sin_len);
        
 
        sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN];
        int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *) &sinRemote,
                 sin_len);

        int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termRx] = 0;
        printf("Message Recieved (%d bytes): \n\n'%s'\n", bytesRx, messageRx);  
    }
    Reciever_shutdown();
}