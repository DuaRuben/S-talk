#include "main.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string.h>

int main(){
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    
    struct sockaddr_in addr; 
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(12345);  
    addr.sin_addr.s_addr = INADDR_ANY; 
    memset(&addr.sin_zero,'\0', 8);
    
    struct sockaddr *psa_in = (struct sockaddr*)&addr;

    bind(s, (struct sockaddr *)psa_in, sizeof(struct sockaddr_in));
}
