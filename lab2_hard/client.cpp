#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "wrappers.h"

int check_mode(char *buf) {
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] == 'F') return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int sock = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};

    adr.sin_family = AF_INET;
    adr.sin_port = htons(34546);

    Connect(sock, (struct sockaddr *) &adr, sizeof(adr));

    pid_t serverid;
    read(sock, &serverid, sizeof(serverid));

    while (true) {
        char buf[256] = {'\0'};

        printf("[Enter user ID, status[F/B], process, args]/[Quit]: ");

        fgets(buf, 256, stdin);

        buf[strlen(buf) - 1] = '\0';
        int n = strlen(buf) + 1;

        if (strcmp(buf, "Quit") == 0) {
            kill(serverid, SIGUSR1);
            close(sock);
            return 0;
        }

        write (sock, &n, sizeof(int));
        write(sock, buf, n * sizeof(char));

        char out[256] = {'\0'};
        int code;
        int size;

        int mode = check_mode(buf);
        if (mode == 1) {
            read(sock, &size, sizeof(int));
            read(sock, out, size * sizeof(char));
            read(sock, &code, sizeof(int));
            printf("%s\n", out);
            printf("Process finished with exit code %d\n", code);
        } else {
            read(sock, &code, sizeof(int));
            printf("Process finished with exit code %d\n", code);
        }

    }
}