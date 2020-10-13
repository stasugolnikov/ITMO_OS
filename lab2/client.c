#include <sys/types.h>
#include <sys/socket.h>
#include "wrappers.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>


int main(int argc, char* argv[]) {   
    int sock = Socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in adr = {0};
    
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    
    Connect(sock, (struct sockaddr*) &adr, sizeof(adr));
    char* message;
    fgets(message, 256, stdin);
    write(sock, message, 256);
   
    char buf[256];
    read(sock, buf, 256);

    printf("%s", buf);
   
    
    close(sock);
    return 0;
}
