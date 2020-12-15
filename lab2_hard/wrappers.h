#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <sys/types.h>
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

void Bind(int s, const struct sockaddr* addr, socklen_t addrlen);

void Listen(int s, int backlog);

int Accept(int s, struct sockaddr* addr, socklen_t* addrlen);

void Connect(int s, const struct sockaddr* addr, socklen_t addrlen);

void Setuid(uid_t uid);

#endif
