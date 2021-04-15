#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include<time.h>
#include<wait.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal3")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

    while (1) {
        pid_t cid1, cid2, cid3, cid4;
        time_t times = time(NULL);
        struct tm* date1 = localtime(&times);
        char now[35];
        strftime(now, 30, "%Y-%m-%d_%H:%M:%S", date1);
        cid1 = fork();

        if (cid1 < 0) exit(0);
        if (cid1 == 0) {
            char *ag[] = {"/bin/mkdir", "-p",now, NULL};
            execv("/bin/mkdir", ag);
        }
        sleep(40);
    }
}