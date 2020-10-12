#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "wrappers.h"

int main(int argc, char* argv[]) {
    int server = Socket(AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server,(struct sockaddr*) &adr, sizeof(adr));
    Listen(server, 5);
    socklen_t adrlen = sizeof(adr);
    int sock = Accept(server, (struct sockaddr*) &adr, &adrlen);
    char buf[256];
    int num_read = read(sock, buf, 256);
    if (num_read == -1) {
	perror("read failed");
	exit(EXIT_FAILURE);
    }
    fprintf(stdout, "%s is argv[1]\n", buf);
    write(sock, buf, num_read);
    close(sock);
    close(server);
    return 0;
}
