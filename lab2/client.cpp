#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "wrappers.h"

int main(int argc, char* argv[]) {
    int sock = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};

    adr.sin_family = AF_INET;
    adr.sin_port = htons(34546);

    Connect(sock, (struct sockaddr*)&adr, sizeof(adr));
    
    char buf[256];

    printf("Enter user ID, status, process, args: ");

    fgets(buf, 256, stdin);

    buf[strlen(buf) - 1] = '\0';

    write(sock, buf, 256);
    
    char buff[1000];
    int code;
    read(sock, buff, 1000);
    read(sock, &code, 8);
    printf("%s\n", buff);
    printf("Process finished with exit code %d\n", code);

    close(sock);
    return 0;
}