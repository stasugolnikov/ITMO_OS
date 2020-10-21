#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "wrappers.h"

void split(std::vector<char *> &strs, char str[]) {
    char *substr = strtok(str, " ");
    while (substr) {
        strs.push_back(substr);
        substr = strtok(NULL, " ");
    }
}

void run_process(std::vector<char *> strs) {
    pid_t pid = fork();
    if (pid == -1) exit(2);

    if (pid == 0) {
        uid_t uid = std::stoll(strs.front());
        char **args = &strs[1];
        Setuid(uid);
        //dup2(sock, 1);
        execv(args[0], args);
    } else {
        //
    }
}

int main(int argc, char *argv[]) {
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34546);

    Bind(server, (struct sockaddr *)&adr, sizeof(adr));

    Listen(server, 5);

    socklen_t adrlen = sizeof(adr);
    int sock = Accept(server, (struct sockaddr *)&adr, &adrlen);

    char buf[256];

    if (read(sock, buf, 256) == -1) exit(1);

    std::vector<char *> strs;
    split(strs, buf);
    strs.push_back(NULL);

    run_process(strs);

    close(sock);
    close(server);
    return 0;
}