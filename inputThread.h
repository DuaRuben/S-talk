#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_
#include "list.h"
#include <pthread.h>

void * inputThread(void * unused);
void Input_init(List* senderList);
void Input_shutdown();

#endif