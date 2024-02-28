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

int getMyPort() {return myPort;}
int getFriendPort() {return friendPort;}
char* getFriendMachineName() {return friendMachineName;}
int getSocket() {return sockt;}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("The format to establish a connection with another host should be of the form:\n\t<./s-talk [my port number] [remote machine name] [remote port number]>\nPlease try again.");
        return 0;
    }
    initialize_pthreads();
    senderList = List_create();
    recieverList = List_create();
    if (senderList == NULL || recieverList == NULL){
        printf("Error! List(s) could not be created.\nExiting the Program\n");
        return 1;
    }
    // Reciever
    myPort = atoi(argv[1]);
    friendMachineName = argv[2];
    friendPort = atoi(argv[3]);
    memset(&localsocket, 0, sizeof(localsocket));
    localsocket.sin_family = AF_INET;
    localsocket.sin_addr.s_addr = htonl(INADDR_ANY);
    localsocket.sin_port = htons(getMyPort());

    // Creating a socket
    sockt = socket(AF_INET, SOCK_DGRAM, 0);
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

    Reciever_init(recieverList);
    Printer_init(recieverList);
    
    Input_init(senderList);
<<<<<<< Updated upstream
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
    exit_program();
    return 0;
=======
    Sender_init(senderList);

    Reciever_shutdown();
    Printer_shutdown();

    Input_shutdown();
    Sender_shutdown();
>>>>>>> Stashed changes
}
