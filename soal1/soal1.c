#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main() {
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        pid_t cid1, cid2, cid3, cid4, cid5, cid6;
        time_t times = time(NULL);
        int status1, status2, status3;
        struct tm* date = localtime(&times);
        char birthday[40];
        strftime(birthday, 30, "%m-%d_%H:%M:%S", date);
        
        //if (strcmp(birthday, "04-09_22:22:00")!=0)continue;

        cid1 = fork();
        if (cid1 < 0)exit(0);
        if (cid1 == 0){
            char *ag[] = {"mkdir", "-p", "Musyik", NULL};
            execv("/bin/mkdir", ag);
        }

        cid4 = fork();
        if (cid4 < 0) exit(0);
        if (cid4 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musyik_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }
        
        cid2 = fork();
        if (cid2 < 0)exit(0);
        if (cid2 == 0){
            char *ag[] = {"mkdir", "-p", "Fylem", NULL};
            execv("/bin/mkdir", ag);
        }

        cid5 = fork();
        if (cid5 < 0) exit(0);
        if (cid5 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Fylem_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }

        cid3 = fork();
        if (cid3 < 0)exit(0);
        if (cid3 == 0){
            char *ag[] = {"mkdir", "-p", "Pyoto", NULL};
            execv("/bin/mkdir", ag);
        }

        cid6 = fork();
        if (cid6 < 0) exit(0);
        if (cid6 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Pyoto_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }

        sleep(30);
    }
}