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

char* caesarChiper (char string[]){
    int i;
    for (i=0;i<strlen(string);i++){
        char temp = string[i];
        if (temp>='A' && temp<='Z'){
            temp+=5;
            if (temp>'Z'){
                temp = temp - 'Z' + 'A' - 1;
            }
            string[i]=temp;
        }
        else if(temp>='a' && temp<='z'){
            temp+=5;
            if (temp>'z'){
                temp = temp - 'z' + 'a' - 1;
            }
            string[i]=temp;
        }
    }
    return string;
}

int main(int argc, char* argv[]) {
    if (argc!=2 || (strcmp(argv[1], "-z")!=0 && strcmp(argv[1], "-x")!=0)){
        printf ("Command not found\n");
        exit(0);
    }

    int flag;
    if (strcmp(argv[1], "-z")==0){
        flag=1;
    }
    else if (strcmp(argv[1], "-x")==0){
        flag=2;
    }
    
    FILE *killer = fopen("killer.sh", "w+");
    fprintf(killer, "#!/bin/bash\nflag=%d\nif [ $flag -eq 1 ]\nthen killall ./soal3\nelse\nkill %d\nfi\nrm killer.sh", flag, getpid()+3);
    fclose(killer);

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

    if ((chdir("/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal3")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    int status, status2, status3, status4;
    while (1) {
        pid_t cid1, cid2, cid3, cid4, cid5, cid6;
        time_t times = time(NULL);
        struct tm* date1 = localtime(&times);
        char now[35];
        strftime(now, 30, "%Y-%m-%d_%H:%M:%S", date1);

        cid1 = fork();
        if (cid1 < 0) exit(EXIT_FAILURE);
        if (cid1 == 0) {
            char *ag[] = {"/bin/mkdir", "-p", now, NULL};
            execv("/bin/mkdir", ag);
        }

        int status;
        
        while (wait(&status)>0);
        cid2 = fork();
        if (cid2 < 0) exit(EXIT_FAILURE);
        if (cid2 == 0){
            chdir(now);
            int i;
            for (i=0;i<10;i++){
                time_t times2 = time(NULL);
                struct tm* date2 = localtime(&times2);
                char now2[35];
                strftime(now2, 30, "%Y-%m-%d_%H:%M:%S", date2);
                char photo[1000];
                sprintf(photo, "https://picsum.photos/%ld", (times2 % 1000) + 50);

                cid3 = fork();
                if (cid3 < 0) exit(0);
                if (cid3 == 0){
                    char *ag[] = {"wget", photo, "-O", now2, "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", ag);
                }
                sleep(5);
            }

            if (i>=0){
                char temp[100];
                strcpy(temp, "Download Success");
                strcpy(temp, caesarChiper(temp));
                cid4 = fork();
                    if (cid4 < 0) exit(EXIT_FAILURE);
                    if (cid4 == 0){
                        FILE *fp = fopen("status.txt", "w+");
                        fprintf(fp, "%s", temp);
                        fclose(fp);
                }
            }
            while(wait(&status3)>0);
            chdir("..");
            char zipName[100];
            sprintf(zipName, "%s.zip", now);

            cid5 = fork();
            if (cid5 < 0) exit(EXIT_FAILURE);
            if (cid5 == 0){
                char *ag[] = {"zip", "-r", zipName, now, NULL};
                execv ("/bin/zip", ag);
            }

            while(wait(&status4)>0);

            cid6 = fork();
            if (cid6 < 0) exit(EXIT_FAILURE);
            if (cid6 == 0){
                char *ag[] = {"rm", "-r", now, NULL};
                execv("/bin/rm", ag);
            }
        }
        sleep(40);
    }
}