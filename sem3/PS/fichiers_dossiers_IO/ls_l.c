#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "ls_l.h" 

void define_mode(char* res, int mode){
    int y = 0;
    for(int i=2; i>-1; i--){
        int oct = mode & (7<<i*3);
        oct = (oct>>i*3);
        switch(oct){
            case 7:
                res[y]='r';
                res[y+1]='w';
                res[y+2]='x';
                break;
            case 6:
                res[y]='r';
                res[y+1]='w';
                res[y+2]='-';
                break;
            case 5:
                res[y]='r';
                res[y+1]='-';
                res[y+2]='x';
                break;
            case 4:
                res[y]='r';
                res[y+1]='-';
                res[y+2]='-';
                break;
            case 3:
                res[y]='-';
                res[y+1]='w';
                res[y+2]='x';
                break;
            case 2:
                res[y]='-';
                res[y+1]='w';
                res[y+2]='-';
                break;
            case 1:
                res[y]='-';
                res[y+1]='-';
                res[y+2]='x';
                break;
        }
        y+=3;
    }
    res[y]='\0';
}

char define_type(struct stat info){
    char res = ' ';
    if(S_ISREG(info.st_mode))
        res='-';
    else if(S_ISDIR(info.st_mode))
        res='d';
    else if(S_ISLNK(info.st_mode))
        res='l';
    else if(S_ISBLK(info.st_mode))
        res='b';
    else if(S_ISCHR(info.st_mode))
        res='c';
    else if(S_ISFIFO(info.st_mode))
        res='p';
    return res;
}

void print_long(char* name){
    struct stat info;
    if(lstat(name, &info)==-1)
        fprintf(stderr, "Cannot lstat %s: %s\n", name, strerror(errno));
    
    char t[32];
    struct tm* tt = localtime(&info.st_mtime);
    strftime(t, 32, "%a %b %e %H:%m:%S %G", tt);

    char mode[11];
    define_mode(mode, info.st_mode);

    char type = define_type(info);
    printf("%c%s %10ld %-s %-s\n", type, mode, info.st_size, t, name);
}