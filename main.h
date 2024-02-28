#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int getMyPort();
int getFriendPort();
char* getFriendPortChar();
char* getFriendMachineName();
int getSocket();
void freeItem(void *item);

extern int myPort;
extern char* friendMachineName;
extern int friendPort;
extern int sockt;

extern struct addrinfo *friendMachineAddr;
void remoteAddrInit(char *friendMachineName, char *friendPort);
struct addrinfo *getfriendMachineAddr();

// gcc -c printerThread.c -o printerThread.o && gcc -c pthread_helpers.c -o pthread_helpers.o && gcc -c recieverThread.c -o recieverThread.o && gcc -c main.c -o main.o && gcc recieverThread.o printerThread.o list.o pthread_helpers.o main.o -o m -lpthread
// scp -P 24 "D:\SFU\CMPT 300\Assignments\assignment2\ass2.zip" kba89@asb9700u-g01.csil.sfu.ca:~/sfuhome
// ssh -p 24 kba89@asb9700-g01.csil.sfu.ca
// scp -P 24 kba89@asb9700-g01.csil.sfu.ca:~/sfuhome/ass2/assnew.zip "C:\Users\gwp16\Downloads"
#endif
