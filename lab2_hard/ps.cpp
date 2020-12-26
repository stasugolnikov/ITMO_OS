#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <stdlib.h>
#include <iostream>
#include <sys/user.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string>


int main() {
    int i, mib[4];
    size_t len = 4;
    struct kinfo_proc kp;
    sysctlnametomib("kern.proc.pid", mib, &len);

    int shm_fd;

    char *ptr;

    shm_fd = shm_open("jopa", O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, 4096);

    ptr = (char *) mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);


    for (i = 0; i < 1000; i++) {
        mib[3] = i;
        len = sizeof(kp);
        sysctl(mib, 4, &kp, &len, NULL, 0);
        if (len > 0) {
            std::string info =
                    "PID: " + std::to_string(kp.kp_proc.p_pid) + " CPU: " + std::to_string(kp.kp_proc.p_pctcpu) +
                    " Priority: " + std::to_string(kp.kp_proc.p_priority);

            sprintf(ptr, "%s\n", info.c_str());
        }

    }


    return 0;
}
