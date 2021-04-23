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

typedef struct animals
{
    char nama[50];
    char jenis[50];
    char umur[10];
}anmls;

anmls animal[50];

char files[100][50];
int countFiles=0;
char uniqueAnimals[100][100];

char *makeFileName(char fileName[], int len, int pos){
    char temp[100]="";
    int i=pos+len+1;
    for (;i<strlen(fileName);i++){
        if (fileName[i]==';') break;
        strncat(temp, &fileName[i],1);
    }
    char *name=temp;
    return name;
}

void insertFiles(char fileName[]){
    int i;
    char temp[100]="";
    for (i=0;i<strlen(fileName);i++){
        if(fileName[i]=='.' && fileName[i+1]=='j'){
            strcpy(files[countFiles++], temp);
            strcpy(temp, "");
            break;
        }
        if(fileName[i]=='_'){
            strcpy(files[countFiles++], temp);
            strcpy(temp, "");
            continue;
        }
        strncat(temp, &fileName[i], 1);
    }
}

anmls substr(char string[], char delim){

    anmls hewan;
    int i;
    char temp[100]="";
    for (i=0;i<strlen(string);i++){
        if (string[i]==delim)break;
        strncat(temp, &string[i], 1);
    }
    strcpy(hewan.jenis, temp);
    ++i;

    char temp2[100]="";
    for (;i<strlen(string);i++){
        if (string[i]==delim)break;
        strncat(temp2, &string[i], 1);
    }
    strcpy(hewan.nama, temp2);
    ++i;

    char temp3[100]="";
    for (;i<strlen(string);i++){
        strncat(temp3, &string[i], 1);
    }
    strcpy(hewan.umur, temp3);

    return hewan;
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int checkAnimal(char jenisAnimal[], int count){
    int i;
    for (i=0; i < count ; i++){
        if (strcmp(jenisAnimal, uniqueAnimals[i])==0) return 1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    pid_t cid1, cid2, cid3, cid4, cid5, cid6, cidTemp;
    int stat1, stat2, stat3, stat4, stat5, stat6;
    DIR *dp;
    struct dirent *ep;

    cid1 = fork();
    if (cid1 < 0) exit(0);
    if (cid1 == 0){
        char *ag[] = {"unzip", "pets.zip", "-d", "/home/frans0416/modul2/petshop", NULL};
        execv("/bin/unzip", ag);
    }

    while(wait(&stat1)>0);
    char path[] = "/home/frans0416/modul2/petshop";
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
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir (dp))) {
            if ((strcmp(ep->d_name, ".")==0) || (strcmp(ep->d_name, "..")==0))continue;
            char fileName[500];
            sprintf(fileName, "%s", ep->d_name);
            insertFiles(fileName);
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    int i;

    int countAnimals=0;
    int countUniqueAnimals=0;

    for (i = 0; i < countFiles; i++)
    {
        animal[countAnimals]=substr(files[i], ';');
        countAnimals++;
    }

    for (i = 0;i<countAnimals;i++){
        if(countUniqueAnimals==0 || !checkAnimal(animal[i].jenis, countUniqueAnimals)){
            strcpy(uniqueAnimals[countUniqueAnimals++], animal[i].jenis);
        }
    }
   
    for (i=0;i<countUniqueAnimals;i++){
        cid3 = fork();
        if (cid3 < 0)exit(0);
        if (cid3 == 0){
            char filePath[500];
            sprintf(filePath, "%s/%s", path, uniqueAnimals[i]);
            char *ag[] = {"mkdir", "-p", filePath, NULL};
            execv("/bin/mkdir", ag);
        }
    }

    while(wait(&stat3)>0);
    dp = opendir(path);
    if (dp != NULL)
    {
        int j;
        while ((ep = readdir (dp))) {
            if ((strcmp(ep->d_name, ".")==0) || (strcmp(ep->d_name, "..")==0))continue;
            char fileName[500];
            sprintf(fileName, "%s", ep->d_name);
            for (j=0; j<countUniqueAnimals;j++){
                char* flag = strstr(fileName, uniqueAnimals[j]);
                if (flag){
                    int pos = (int) (flag - fileName);
                    int len = strlen (uniqueAnimals[j]);
                    char name[100];
                    strcpy(name, makeFileName(fileName, len, pos));
                    char dest[500];
                    char src[500];
                    sprintf(dest, "%s/%s/%s.jpg", path, uniqueAnimals[j], name);
                    sprintf(src, "%s/%s", path, ep->d_name);
                    if (is_regular_file(src)){
                        cid4 = fork();
                        if (cid4 < 0)exit(0);
                        if (cid4 == 0){
                            char *ag[] = {"cp", "-f", src, dest, NULL};
                            execv("/bin/cp", ag);
                        }
                    }
                }
            }
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    int statNew;
    while(wait(&statNew)>0);
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir (dp))) {
            if ((strcmp(ep->d_name, ".")==0) || (strcmp(ep->d_name, "..")==0))continue;
            char fileName[500];
            sprintf(fileName, "%s", ep->d_name);
            char src[500];
            sprintf(src, "%s/%s", path, ep->d_name);
            char* sign = strstr(fileName, ".jpg");
            if (sign){
                pid_t cidNew;
                cidNew = fork();
                if (cidNew < 0) exit(EXIT_FAILURE);
                if (cidNew == 0){
                    char *ag[] = {"rm", src, NULL};
                    execv("/bin/rm", ag);
                }
            }
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");

    while(wait(&stat4)>0);
    dp = opendir(path);
    if (dp != NULL)
    {
        int j;
        while ((ep = readdir (dp))) {
            char pathTemp[500];
            sprintf(pathTemp,"%s/%s", path, ep->d_name);
            if ((strcmp(ep->d_name, ".")==0) || (strcmp(ep->d_name, "..")==0))continue;
            if (!is_regular_file(pathTemp)){
                char folderName[100];
                strcpy(folderName, ep->d_name);
                int j=0,k=0;
                char pathFile[700];
                sprintf(pathFile, "%s/keterangan.txt", pathTemp);
                FILE *fp = fopen(pathFile, "a+");
                for (j=0;j<countAnimals;j++){
                    if (strcmp(animal[j].jenis, folderName)==0)
                        fprintf(fp, "nama: %s\numur: %s tahun\n\n", animal[j].nama, animal[j].umur);
                }
                fclose(fp);
            }
        }
        (void) closedir (dp);
    } else perror ("Couldn't open the directory");
    return 0;
}
