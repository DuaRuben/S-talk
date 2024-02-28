#include "pthread_helpers.h"
#include "printerThread.h"
#include "recieverThread.h"
#include "inputThread.h"
#include "senderThread.h"

// Define mutex and condition variables
pthread_mutex_t recieverListMutex ;
pthread_cond_t recieverListToMonitorCond;

//Condition variable for InputSender
pthread_cond_t inputSenderCondVar;
//Mutex variable for InputSender
pthread_mutex_t inputSenderMutexVar;


//Conditon variable for Exiting Program
pthread_cond_t exitProgramCondVar;
//Mutex variable for Exiting Program
pthread_mutex_t exitProgramMutexVar;


// Function to initialize mutex and condition variables
void initialize_pthreads() {
	
	// You can perform additional initialization here if needed
    // For example, dynamic initialization of mutexes and condition variables
    pthread_mutex_init(&recieverListMutex, NULL);
    pthread_cond_init(&recieverListToMonitorCond, NULL);

    pthread_mutex_init(&inputSenderMutexVar,NULL);
    pthread_cond_init(&inputSenderCondVar,NULL);

    pthread_cond_init(&exitProgramCondVar,NULL);
    pthread_mutex_init(&exitProgramMutexVar,NULL);
}

void close_pthreads(){
    pthread_mutex_destroy(&recieverListMutex);
    pthread_mutex_destroy(&inputSenderMutexVar);
    pthread_mutex_destroy(&exitProgramMutexVar);
         
    pthread_cond_destroy(&recieverListToMonitorCond);
    pthread_cond_destroy(&inputSenderCondVar);
    pthread_cond_destroy(&exitProgramCondVar);
}

void exit_program(){
    pthread_mutex_lock(&exitProgramMutexVar);
    {
        pthread_cond_wait(&exitProgramCondVar,&exitProgramMutexVar);
    }
    pthread_mutex_unlock(&exitProgramMutexVar);
    Reciever_shutdown();
    Input_shutdown();
    Printer_shutdown();
    Sender_shutdown();
    close_pthreads();
}