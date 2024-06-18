#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "rec.h"

int PATH_MAX=260;
int STR_MAX=200;

void cp_file(char* filename, char* dest){
    int fd = open(filename, O_RDONLY);
    if(fd<0)
        fprintf(stderr, "Cannot open %s: %s\n", filename, strerror(errno));
    else{
        int fd_dest = open(dest, O_WRONLY);
        if(fd_dest<0)
            fprintf(stderr, "Cannot open %s: %s\n", dest, strerror(errno));
        else{
            struct stat info;
            if(stat(filename, &info)<0)
                fprintf(stderr, "Cannot stat %s: %s\n", filename, strerror(errno));
            else{
                char buf[info.st_blksize];
                int current = 0;
                while(current < info.st_size){
                    if((current+=read(fd, buf, sizeof(buf)))<0){
                        fprintf(stderr, "Cannot read %s: %s\n", filename, strerror(errno));
                        break;
                    }
                    else{
                        if(write(fd_dest, buf, current%info.st_blksize)<0){
                            fprintf(stderr, "Cannot write %s: %s\n", dest, strerror(errno));
                            break;
                        }
                    }   
                }
            }
        }
        if(close(fd_dest)<0)
           fprintf(stderr, "Cannot close %s: %s\n", dest, strerror(errno)); 
    }
    if(close(fd)<0)
        fprintf(stderr, "Cannot close %s: %s\n", filename, strerror(errno));
}

void create_file(char* name, mode_t mode){
    int fd = open(name, O_CREAT, mode);
    if(fd<0)
        fprintf(stderr, "Cannot open %s: %s\n", name, strerror(errno));
    else
        if(close(fd)<0)
            fprintf(stderr, "Cannot close %s: %s\n", name, strerror(errno)); 
}

void cp_link(char* filename, char* dest){
    struct stat info;
    if(lstat(filename, &info)<0)
        fprintf(stderr, "Cannot lstat %s: %s\n", filename, strerror(errno));
    else{
        create_file(dest, info.st_mode); 
        char rpath[PATH_MAX];
        if((realpath(filename, rpath))==NULL)
            fprintf(stderr, "Cannot realpath %s: %s\n", filename, strerror(errno));
        else{
            if(symlink(dest, rpath)==-1)
                fprintf(stderr, "Cannot symlink %s: %s\n", dest, strerror(errno));
        }
    }
}

bool Exist(char* name){
    return access(name, F_OK)==0;
}

bool isFile_or_Lnk(char * name){
    struct stat info;
    if(lstat(name, &info)<0){
        fprintf(stderr, "Cannot lstat %s: %s\n", name, strerror(errno));
        return false;
    }else{
        return S_ISREG(info.st_mode) || S_ISLNK(info.st_mode);
    }   
}

bool isLnk(char * name){
    struct stat info;
    if(lstat(name, &info)<0){
        fprintf(stderr, "Cannot lstat %s: %s\n", name, strerror(errno));
        return false;
    }else{
        return S_ISLNK(info.st_mode);
    }   
}

void create_dir(char * name, mode_t mode){
    if(mkdir(name,mode)<0)
       fprintf(stderr, "Cannot create %s: %s\n", name, strerror(errno));
}

void create_path(char* to, char* path_res){
    char path[PATH_MAX];
    //absolute path
    if(to[0]=='/'){
        strcpy(path, to);
    }
    else{ // relative path
        if(getcwd(path, sizeof(path))==NULL)
            fprintf(stderr, "Cannot getcwd : %s\n", strerror(errno));
    
        if(path[strlen(path)] != '/')
            strcat(path, "/");
    
        strcat(path,to);
    }

    char* path_tab[PATH_MAX];
    char tmp_path[PATH_MAX];
    strcpy(tmp_path, path);
    path_tab[0]=strtok(tmp_path, "/");
    int i=0;
    do{
        path_tab[++i]=strtok(NULL, "/");     
    }while(path_tab[i]!=NULL);

    char inc_path[PATH_MAX];
    strcpy(inc_path,"/");

    for(int y=0; y<i; y++){
        if(strcmp(path_tab[y],".")!=0 && strcmp(path_tab[y],"..")!=0){
            strcat(inc_path,path_tab[y]);
            if(y!=i-1){
                if(!Exist(inc_path)){
                    create_dir(inc_path, S_IRWXG|S_IRWXO|S_IRWXU);
                }
                strcat(inc_path,"/");
            }else if(!Exist(inc_path)){
                create_file(inc_path, S_IRWXG|S_IRWXO|S_IRWXU);
            }    
        }
    }
    strcpy(path_res,inc_path);
}

void get_filename_from_path(char* path, char* filename){
    char* path_tab[PATH_MAX];
    char tmp_path[PATH_MAX];
    strcpy(tmp_path, path);
    path_tab[0]=strtok(tmp_path, "/");
    int i=0;
    do{
        path_tab[++i]=strtok(NULL, "/");     
    }while(path_tab[i]!=NULL);

    strcpy(filename,path_tab[i-1]);
}

bool End_by_points(char* str){
    if(str[strlen(str)-3]=='/'){
        if(str[strlen(str)-2]=='.'){
            return str[strlen(str)-1]=='.';
        }
    }else if(str[strlen(str)-2]=='/'){
        return str[strlen(str)-1]=='.';
    }
    return false;
    
}

void safe_cp_file(char* from, char* to, short param){
    if(!(End_by_points(from) || End_by_points(to))){
        if(Exist(from)){
            if(isFile_or_Lnk(from)){
                if(Exist(to)){
                    if(isFile_or_Lnk(to)){
                        struct stat info;
                        struct stat info2;
                        if(lstat(to, &info)<0)
                            fprintf(stderr, "Cannot lstat %s: %s\n", to, strerror(errno));
                        else if(lstat(from, &info2)<0)
                            fprintf(stderr, "Cannot lstat %s: %s\n", from, strerror(errno));
                        else{
                            if(info.st_size != info2.st_size || info.st_mtime > info2.st_mtime){
                                if(param>=2 && isLnk(from)){// -f
                                    cp_link(from, to);
                                }else{
                                    cp_file(from, to);
                                }
                            }else if(param%2==1){//if -a
                                if(chmod(to, info2.st_mode)==-1)
                                    fprintf(stderr, "Cannot chmod %s: %s\n", to, strerror(errno));
                            }
                        }
                    }else if(isDir(to)){
                        if(to[strlen(to)-1] != '/'){
                            strcat(to, "/");
                        }
                        char tmp_filename[PATH_MAX];
                        char tmp_path[PATH_MAX];
                        get_filename_from_path(from,tmp_filename);
                        strcpy(tmp_path, to);
                        strcat(tmp_path, tmp_filename);
                        struct stat info;
                        if(lstat(from, &info)<0)
                            fprintf(stderr, "Cannot lstat %s: %s\n", from, strerror(errno));
                        else{
                            if(param>=2 && isLnk(from)){// -f
                                cp_link(from, to);
                            }else{
                                create_file(tmp_path, info.st_mode);
                                cp_file(from, to);
                            }
                        }    
                    }   
                }else{
                    struct stat info;
                    if(lstat(from, &info)<0)
                        fprintf(stderr, "Cannot lstat %s: %s\n", from, strerror(errno));
                    else{
                        if(param>=2 && isLnk(from)){// -f
                            cp_link(from, to);
                        }else{
                            create_file(to, info.st_mode);
                            cp_file(from, to);
                        }
                    } 
                }
            }
        }else{
            fprintf(stderr, "Cannot copy from non existent file : %s\n", from);
        }
    }
}

void foo(char* a, char* b){
    printf("%s -> %s\n", a, b);
}

void get_last_from_path(char* path, char* res){
    char* path_tab[100];
    char tmp_path[100];
    strcpy(tmp_path, path);
    path_tab[0]=strtok(tmp_path, "/");
    int i=0;
    do{
        path_tab[++i]=strtok(NULL, "/");     
    }while(path_tab[i]!=NULL);

    strcpy(res, path_tab[i-1]);
}

void cp(char** argv, int argc, short param){
    if(Exist(argv[argc-1])){
        if(isDir(argv[argc-1])){
            for(int i=0; i<argc-1; i++){
                if(Exist(argv[i])){
                    if(isFile_or_Lnk(argv[i])){
                        if(argv[argc-1][strlen(argv[argc-1])-1] != '/'){
                            strcat(argv[argc-1], "/");
                        }
                        char tmp_filename[PATH_MAX];
                        char tmp_path[PATH_MAX];
                        get_filename_from_path(argv[i],tmp_filename);
                        strcpy(tmp_path, argv[argc-1]);
                        strcat(tmp_path, tmp_filename);
                        struct stat info;
                        if(lstat(argv[i], &info)<0)
                            fprintf(stderr, "Cannot lstat %s: %s\n", argv[i], strerror(errno));
                        else{
                            if(param>2 && isLnk(argv[i])){// -f
                                cp_link(argv[i], tmp_path);
                            }else{
                                create_file(tmp_path, info.st_mode);
                                cp_file(argv[i], tmp_path);
                            }
                        } 
                        
                    }else if(isDir(argv[i])){
                        char to[100];
                        char tmp[100];
                        
                        get_last_from_path(argv[i],tmp);
                        strcpy(to,argv[argc-1]);
                        if(to[strlen(to)-1]!='/')
                            strcat(to,"/");
                        strcat(to, tmp);
                        
                        struct stat info;
                        if(stat(argv[i], &info)<0)
                            fprintf(stderr, "Cannot stat %s: %s\n", argv[i], strerror(errno));
                        else{
                            if(!Exist(to))
                                create_dir(to, info.st_mode);
                            browse_rec(argv[i], to, param, safe_cp_file);
                        }
                    }else{
                        fprintf(stderr,"Cannot ultra-cp something different than link, file, dir");
                    }
                }else{
                    fprintf(stderr,"Cannot ultra-cp from inexistant %s", argv[0]);
                }
            }
        }else{
            if(argc==2){
                if(Exist(argv[0])){
                    if(isFile_or_Lnk(argv[0])){
                        if(param>2 && isLnk(argv[0])){// -f
                            cp_link(argv[0], argv[argc-1]);
                        }else{
                            cp_file(argv[0], argv[argc-1]);
                        }
                    }
                }
            }else{
                fprintf(stderr, "Cannot copy more than 1 file into 1 file");
            }
        }
    }else{
        if(argc==2){
            if(Exist(argv[0])){
                if(isFile_or_Lnk(argv[0])){
                    struct stat info;
                    if(lstat(argv[0], &info)==-1)
                        fprintf(stderr, "Cannot lstat %s: %s\n", argv[0], strerror(errno));
                    else{
                        if(param>2 && isLnk(argv[0])){// -f
                            cp_link(argv[0], argv[argc-1]);
                        }else{
                            create_file(argv[argc-1], info.st_mode);
                            cp_file(argv[0], argv[argc-1]);
                        }
                    }
                }else{
                    fprintf(stderr,"Cannot ultra-cp something different than link or file");
                }
            }else{
                fprintf(stderr,"Cannot ultra-cp from inexistant %s", argv[0]);
            }
        }else{
            fprintf(stderr, "Cannot copy more than 1 file to file");
        }
    }
}