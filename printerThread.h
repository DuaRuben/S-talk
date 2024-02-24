#ifndef _PRINTERTHREAD_H_
#define _PRINTERTHREAD_H_
#include "list.h"
#include <pthread.h>

void * printerThread(void * unused);
void Printer_init(List* recieverList);
void Printer_shutdown();
void waitForRecieverSignal();

#endif
