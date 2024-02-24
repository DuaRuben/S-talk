#include "list.h"
#include <pthread.h>
#ifndef _RECIEVERTHREAD_H_
#define _RECIEVERTHREAD_H_

void* recieverThread(void * unused);
void Reciever_init(List* recieverList, int socket);
void Reciever_shutdown();

#endif
