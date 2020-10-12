#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wrappers.h"


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

void Inet_pton (int af, const char* src, void* dst) {
    int res = inet_pton(af, src, dst);
    if (res == -1 || res == 0) {
	perror("inet_pton failed");
	exit(EXIT_FAILURE);
    }
}


