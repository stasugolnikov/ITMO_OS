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

    printf("Enter user ID, process, args: ");

    fgets(buf, 256, stdin);

    buf[strlen(buf) - 1] = '\0';

    write(sock, buf, 256);

    close(sock);
    return 0;
}