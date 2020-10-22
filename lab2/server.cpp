#include <arpa/inet.h>
#include <fcntl.h>
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

void run_process_foreground(std::vector<char *> &strs, int &fd_out, int &fd_err) {
    int fd_stdout[2];
    int fd_stderr[2];

    if (pipe(fd_stdout) == -1 || pipe(fd_stderr) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (!pid) {
        close(fd_stdout[0]);

        uid_t uid = std::stoi(strs.front());
        Setuid(uid);
        char **args = &strs[1];

        dup2(fd_stdout[1], STDOUT_FILENO);
        dup2(fd_stderr[1], STDERR_FILENO);

        execv(args[0], args);
        close(fd_stdout[1]);
    } else {
        ssize_t nread;
        char buff[1000];
        std::string ans;
        while (read(fd_stdout[0], buff, sizeof(buff))) {
            std::cout << ans << '\n';
            ans += buff;
            read(fd_out, buff, sizeof(buff));
        }
        fd_out = fd_stdout[0];
        fd_err = fd_stderr[0];
    }
}

void run_process_background(std::vector<char *> &strs, int &fd_out, int &fd_err) {
    int fd_stdout[2];
    int fd_stderr[2];

    if (pipe(fd_stdout) == -1 || pipe(fd_stderr) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid_child = fork();

    if (pid_child == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (!pid_child) {
        close(fd_stdout[0]);
        close(fd_stderr[0]);
        dup2(fd_stdout[1], STDOUT_FILENO);
        dup2(fd_stderr[1], STDERR_FILENO);

        pid_t pid_grandchild = fork();
        if (!pid_grandchild) {
            uid_t uid = std::stoi(strs.front());
            Setuid(uid);
            char **args = &strs[1];
            execv(args[0], args);
        }
        exit(0);
        close(fd_stdout[1]);

    } else {
        close(fd_stdout[1]);

        int log_file = open("file.log", O_WRONLY | O_CREAT, 0777);

        ssize_t nread;
        char buf[1000];
        std::string s;
        while ((nread = read(fd_stdout[0], buf, sizeof(buf)))) {
            s += buf;
            write(log_file, buf, nread);
        }
        std::cout << s;
        close(fd_stdout[0]);
        //fd_out = fd_stdout[0];
        //fd_err = fd_stderr[0];
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
    int fd_out, fd_err;
    run_process_background(strs, fd_out, fd_err);

    close(sock);
    close(server);
    return 0;
}