#include "main.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LEN 1024
#define PORT 22110

int main()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(sin));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    // memset(&addr.sin_zero,'\0', 8);
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

    while (1)
    {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_LEN];
        int bytesRx = recvfrom(s, messageRx, MAX_LEN, 0, (struct sockaddr *) &sinRemote,
                 sin_len);

        int termRx = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        messageRx[termRx] = 0;
        printf("Message Recieved (%d bytes): \n\n'%s'\n", bytesRx, messageRx);         
        
        // char messageTx[MAX_LEN];
        // sprintf(messageTx, "Math");
        // sin_len = sizeof(sinRemote);
        
        // sendto(s, messageTx , strlen(messageTx), 0, (struct sockaddr *) &sinRemote, sin_len);

        
    }
}
