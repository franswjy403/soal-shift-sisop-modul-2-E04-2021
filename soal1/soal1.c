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
#include <dirent.h>

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
        DIR *dp;
        struct dirent *ep;
        pid_t cid1, cid2, cid3, cid4, cid5, cid6, cid7, cid8, cid9, cid10, cid11, cid12;
        pid_t cidT1, cidT2, cidT3, cidT4, cidT5;
        time_t times = time(NULL);
        int status1, status2, status3, status4, status5, status6, status7, status8, status9;
        int statA, statB, statC, statD, statE;
        
        struct tm* date = localtime(&times);
        char birthday[40];
        strftime(birthday, 30, "%m-%d_%H:%M:%S", date);

        if (strcmp(birthday, "04-09_16:22:00")!=0)continue;

        cid1 = fork();
        if (cid1 < 0)exit(0);
        if (cid1 == 0){
            char *ag[] = {"mkdir", "-p", "Musyik", NULL};
            execv("/bin/mkdir", ag);
        }
        
        cid2 = fork();
        if (cid2 < 0)exit(0);
        if (cid2 == 0){
            char *ag[] = {"mkdir", "-p", "Fylem", NULL};
            execv("/bin/mkdir", ag);
        }

        cid3 = fork();
        if (cid3 < 0)exit(0);
        if (cid3 == 0){
            char *ag[] = {"mkdir", "-p", "Pyoto", NULL};
            execv("/bin/mkdir", ag);
        }

        //Musyik
        while(wait(&status1)>0);
        cid4 = fork();
        if (cid4 < 0) exit(0);
        if (cid4 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musyik_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }

        while(wait(&status4)>0);
        cid7 = fork();
        if (cid7 < 0) exit (0);
        if (cid7 == 0){
            char *ag[] = {"unzip", "Musyik_for_stevany.zip", "-d", "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1", NULL};
            execv("/bin/unzip", ag);
        }

        while(wait(&statA)>0);
        char pathMusik[] = "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/MUSIK";
        dp = opendir(pathMusik);
        if (dp != NULL)
        {
            int statTemp;
            char dest[500]="/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/Musyik";
            while ((ep = readdir (dp))) {
                    char src[500];
                    sprintf(src, "%s/%s", pathMusik, ep->d_name);
                    cid10 = fork();
                    if (cid10 < 0) exit(0);
                    if (cid10 == 0){
                        char *ag[] = {"mv", "-t", dest, src, NULL};
                        execv("/bin/mv", ag);
                    }
                }
            (void) closedir (dp);
            while(wait(&statTemp)>0);
            cidT1 = fork();
            if (cidT1 < 0)exit(0);
            if (cidT1 == 0){
                char *ag[]={"rm", "-r", "MUSIK", NULL};
                execv ("/bin/rm", ag);
            }
        } else perror ("Couldn't open the directory");        

        //Fylem
        while(wait(&status2)>0);
        cid5 = fork();
        if (cid5 < 0) exit(0);
        if (cid5 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Fylem_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }

        while(wait(&status6)>0);
        cid8 = fork();
        if (cid8 < 0) exit (0);
        if (cid8 == 0){
            char *ag[] = {"unzip", "Fylem_for_stevany.zip", "-d", "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1", NULL};
            execv("/bin/unzip", ag);
        }

        while(wait(&statB)>0);
        char pathFilm[] = "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/FILM";
        dp = opendir(pathFilm);
        if (dp != NULL)
        {
            int statTemp;
            char dest[500]="/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/Fylem";
            while ((ep = readdir (dp))) {
                    char src[500];
                    sprintf(src, "%s/%s", pathFilm, ep->d_name);
                    cid10 = fork();
                    if (cid10 < 0) exit(0);
                    if (cid10 == 0){
                        char *ag[] = {"mv", "-t", dest, src, NULL};
                        execv("/bin/mv", ag);
                    }
                }
            (void) closedir (dp);
            while(wait(&statTemp)>0);
            cidT2 = fork();
            if (cidT2 < 0)exit(0);
            if (cidT2 == 0){
                char *ag[]={"rm", "-r", "FILM", NULL};
                execv ("/bin/rm", ag);
            }
        } else perror ("Couldn't open the directory"); 

        //Pyoto
        while(wait(&status3)>0);
        cid6 = fork();
        if (cid6 < 0) exit(0);
        if (cid6 == 0){
            char *ag[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Pyoto_for_stevany.zip", "-o", "/dev/null", NULL};
            execv("/bin/wget", ag);
        }

        while(wait(&status5)>0);
        cid9 = fork();
        if (cid9 < 0) exit (0);
        if (cid9 == 0){
            char *ag[] = {"unzip", "Pyoto_for_stevany.zip", "-d", "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1", NULL};
            execv("/bin/unzip", ag);
        }

        while(wait(&statB)>0);
        char pathFoto[] = "/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/FOTO";
        dp = opendir(pathFoto);
        if (dp != NULL)
        {
            int statTemp;
            char dest[500]="/home/frans0416/Documents/sisopE/soal-shift-sisop-modul-2-E04-2021/soal1/Pyoto";
            while ((ep = readdir (dp))) {
                    char src[500];
                    sprintf(src, "%s/%s", pathFoto, ep->d_name);
                    cid10 = fork();
                    if (cid10 < 0) exit(0);
                    if (cid10 == 0){
                        char *ag[] = {"mv", "-t", dest, src, NULL};
                        execv("/bin/mv", ag);
                    }
                }
            (void) closedir (dp);
            while(wait(&statTemp)>0);
            cidT3 = fork();
            if (cidT3 < 0)exit(0);
            if (cidT3 == 0){
                char *ag[]={"rm", "-r", "FOTO", NULL};
                execv ("/bin/rm", ag);
            }
        } else perror ("Couldn't open the directory");
        
        if (strcmp(birthday, "04-09_22:22:00")!=0)continue;
        
        while (wait(&statD)>0);
        cidT4 = fork();
        if (cidT4 < 0)exit(0);
        if (cidT4 == 0){
            char *ag[] = {"zip", "-r", "Lopyu_Stevany.zip", "Musyik", "Fylem", "Pyoto", NULL};
            execv("/bin/zip", ag);
        }

        while (wait(&statE)>0);
        cidT5 = fork();
        if (cidT5 < 0)exit(0);
        if (cidT5 == 0){
            char *ag[] = {"rm", "-rf", "Musyik", "Fylem", "Pyoto", NULL};
            execv("/bin/rm", ag);
        }

    }
}
