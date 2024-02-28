#include "senderThread.h"
#include "pthread_helpers.h"
#include "list.h"
#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024

pthread_t thread4;
List *listptr4;
struct sockaddr_in sinRemote4;
int sendersocket;

void *senderThread(void *unused)
{
    char *fmn = getFriendMachineName();
    memset(&sinRemote4, 0, sizeof(sinRemote4));
    sinRemote4.sin_family = AF_INET;
    sinRemote4.sin_addr.s_addr = inet_addr(fmn);
    sinRemote4.sin_port = htons(getFriendPort());
    unsigned int sin_len = sizeof(sinRemote4);

    while (1) {
        pthread_mutex_lock(&inputSenderMutexVar);
        {
            // wait for signal
            pthread_cond_wait(&inputSenderCondVar, &inputSenderMutexVar);

            // remove from list
            char msg[MAX_LEN];
            List_first(listptr4);
            char *temp = List_remove(listptr4);
            if (temp != NULL)
            {
                strcpy(msg, temp);
                free(temp);
            }

            // send Msg
            sendto(sendersocket, msg, strlen(msg), 0, (struct sockaddr *)&sinRemote4, sin_len);
        }
<<<<<<< Updated upstream

        //send Msg
        sendto(sendersocket, msg, strlen(msg), 0, (struct sockaddr *)&sinRemote4, sin_len);

        // if msg is !
        if(msg[0] == '!' && msg[1]=='\0'){
            pthread_mutex_lock(&exitProgramMutexVar);
            {
                pthread_cond_signal(&exitProgramCondVar);
            }
            pthread_mutex_unlock(&exitProgramMutexVar);
        }
    }
    pthread_mutex_unlock(&inputSenderMutexVar);
=======
        pthread_mutex_unlock(&inputSenderMutexVar);
>>>>>>> Stashed changes
    }
}

void Sender_init(List *senderList)
{
    sendersocket = getSocket();
    listptr4 = senderList;
    pthread_create(&thread4, NULL, senderThread, NULL);
}

void Sender_shutdown()
{
    pthread_join(thread4, NULL);
}
