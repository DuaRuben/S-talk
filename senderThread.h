#ifndef _SENDERTHREAD_H_
#define _SENDERTHREAD_H_
#include "list.h"
#include <pthread.h>

void * senderThread(void * unused);
void Sender_init(List* senderList,int socket);
void Sender_shutdown();

#endif