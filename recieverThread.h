#include "list.h"
#include <pthread.h>
#ifndef _RECIEVERTHREAD_H_
#define _RECIEVERTHREAD_H_

void* recieverThread(void * unused);
void Reciever_init(List* recieverList, int socket, pthread_cond_t condition, pthread_mutex_t mutex);
void Reciever_shutdown();

#endif
