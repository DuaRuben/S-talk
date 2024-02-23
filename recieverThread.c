#include "recieverThread.h"
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
struct sockaddr_in addr;
struct sockaddr_in sinRemote;
int s;

void *recieverThread(void *unused)
{
    unsigned int sin_len = sizeof(sinRemote);
    sin_len = sizeof(sinRemote);
    char messageRx[MAX_LEN];
    int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *)&sinRemote, sin_len);
    int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
    messageRx[termRx] = 0;
    List_append(list,messageRx);

}
void Reciever_init(List* recieverList)
{
    //Reciever
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("142.58.15.216");
    addr.sin_port = htons(12346);

    //Sender
    memset(&addr, 0, sizeof(addr));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_addr.s_addr = inet_addr("142.58.15.122");
    sinRemote.sin_port = htons(12345);

    //Creating a socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        printf("Error!Socket cannot was not created.");
    }

    //Binding a socket
    int x = bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if (x == -1)
    {
        printf("Error!Cannot bind a socket");
    }

    //Copying List
    list = recieverList;
    pthread_create(&thread, NULL, recieverThread, NULL);
}
void Reciever_shutdown()
{
    pthread_join(thread, NULL);
}