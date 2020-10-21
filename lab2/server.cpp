#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

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

void run_process(std::vector<char *> &strs) {
    int fd[2][2];
    pipe(fd[0]);
    pipe(fd[1]);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (!pid) {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[0][0]);

        uid_t uid = std::stoi(strs.front());
        Setuid(uid);
        char **args = &strs[1];

        dup2(fd[1][1], STDOUT_FILENO);

        execv(args[0], args);
        close(fd[1][1]);
    } else {
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[0][1]);

        int log_file = open("file.log", O_WRONLY | O_CREAT, 0777);
        
        ssize_t nread;
        char buf[1000];
        while ((nread = read(fd[1][0], buf, sizeof(buf)))) {
            write(log_file, buf, nread);
        }

        close(fd[1][0]);
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