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
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char const *argv[])
{
    pid_t cid1, cid2, cid3, cid4, cid5, cid6;
    int stat1, stat2, stat3, stat4, stat5, stat6;
    DIR *dp;
    struct dirent *ep;

    cid1 = fork();
    if (cid1 < 0) exit(0);
    if (cid1 == 0){
        char *ag[] = {"unzip", "pets.zip", "-d", "/home/frans0416/modul2/petshop/tes", NULL};
        execv("/bin/unzip", ag);
    }

    while(wait(&stat1)>0);
    char path[] = "/home/frans0416/modul2/petshop/tes";
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir (dp))) {
            char pathTemp[500];
            sprintf(pathTemp,"%s/%s", path, ep->d_name);
            if ((strcmp(ep->d_name, ".")==0) || (strcmp(ep->d_name, "..")==0))continue;
            if (!is_regular_file(pathTemp)){
                cid2 = fork();
                if (cid2 < 0)exit(0);
                if (cid2 == 0){
                    char *ag[] = {"rm", "-r", pathTemp, NULL};
                    execv("/bin/rm", ag);
                }
            }
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    while(wait(&stat2)>0);
    char path[] = "/home/frans0416/modul2/petshop/tes"
    return 0;
}
