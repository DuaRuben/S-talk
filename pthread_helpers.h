#ifndef PTHREAD_HELPERS_H
#define PTHREAD_HELPERS_H

#include <pthread.h>

// Declare mutex and condition variables
extern pthread_mutex_t recieverListMutex;
extern pthread_cond_t recieverListAppendCond;
extern pthread_cond_t recieverListToMonitorCond;
extern pthread_mutex_t inputSenderMutexVar;
extern pthread_cond_t inputSenderCondVar;

// Function to initialize mutex and condition variables
void initialize_pthreads();

#endif