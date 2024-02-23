#include "list.h"
#ifndef _RECIEVERTHREAD_H_
#define _RECIEVERTHREAD_H_

void* recieverThread(void * unused);
void Reciever_init(List* recieverList,int socket, struct sockaddr_in sRemote,pthread_cond_t condition,pthread_mutex_t mutex);
void Reciever_shutdown();

#endif