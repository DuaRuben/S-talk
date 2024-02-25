#include "pthread_helpers.h"

// Define mutex and condition variables
pthread_mutex_t recieverListMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t recieverListAppendCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t recieverListToMonitorCond = PTHREAD_COND_INITIALIZER;

//Condition variable for InputSender
pthread_cond_t inputSenderCondVar;
//Mutex variable for InputSender
pthread_mutex_t inputSenderMutexVar;


// Function to initialize mutex and condition variables
void initialize_pthreads() {
    // You can perform additional initialization here if needed
    // For example, dynamic initialization of mutexes and condition variables
    pthread_mutex_init(&recieverListMutex, NULL);
    pthread_cond_init(&recieverListAppendCond, NULL);
    pthread_cond_init(&recieverListToMonitorCond, NULL);
    pthread_mutex_init(&inputSenderMutexVar,NULL);
    pthread_cond_init(&inputSenderCondVar,NULL);
}