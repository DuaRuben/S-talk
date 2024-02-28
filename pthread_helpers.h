#ifndef PTHREAD_HELPERS_H
#define PTHREAD_HELPERS_H

#include <pthread.h>

// Declare mutex and condition variables
extern pthread_mutex_t recieverListMutex;
extern pthread_cond_t recieverListToMonitorCond;

extern pthread_mutex_t inputSenderMutexVar;
extern pthread_cond_t inputSenderCondVar;

extern pthread_cond_t exitProgramCondVar;
extern pthread_mutex_t exitProgramMutexVar;

// Function to initialize mutex and condition variables
void initialize_pthreads();
void close_pthreads();
void exit_program();
#endif