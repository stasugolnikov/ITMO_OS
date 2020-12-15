#include "wrappers.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int s, const struct sockaddr* addr, socklen_t addrlen) {
    int res = bind(s, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int s, int backlog) {
    int res = listen(s, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int s, struct sockaddr* addr, socklen_t* addrlen) {
    int res = accept(s, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int s, const struct sockaddr* addr, socklen_t addrlen) {
    int res = connect(s, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Setuid(uid_t uid) {
    int res = setuid(uid);
    if (res == -1) {
        perror("setuid failed");
        exit(EXIT_FAILURE);
    }
}