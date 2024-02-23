#ifndef _PRINTERTHREAD_H_
#define _PRINTERTHREAD_H_
#include "list.h"

void * printerThread(void * unused);
void Printer_init(List* recieverList,pthread_cond_t condition,pthread_mutex_t mutex);
void Printer_shutdown();

#endif