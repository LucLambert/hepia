#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "cp.h"

bool is_parent_or_current_dir(char* name){   
    return strcmp(name, "..")==0 || strcmp(name, ".")==0;
}

bool isDir(char* name){
    struct stat info;
    if(lstat(name, &info)<0){
        fprintf(stderr, "Cannot lstat %s: %s\n", name, strerror(errno));
    }else{
        return S_ISDIR(info.st_mode);
    }
    return false;
}

void add_slash(char* name){
    if(name[strlen(name)-1]!='/')
        strcat(name,"/");
}

void browse_rec(char* name, char* to, short param,void (*f)(char*,char*,short)){//possibiliter d'amélioration void tab, size_t size, int n
    struct stat info;
    if(lstat(name, &info)<0){
        fprintf(stderr, "Cannot lstat %s: %s\n", name, strerror(errno));
    }
    else{
        if(!S_ISDIR(info.st_mode)){// all but no dir"
            f(name, to, param);
        }
        else{//if dir
            char* dir=name;
            DIR* d = opendir(dir);
            if(d == NULL)
                fprintf(stderr, "Cannot open %s: %s\n", dir, strerror(errno) );
            else{
                struct dirent* dc;
                while(NULL != (dc = readdir(d))){
                    if(errno == EBADF)
                        fprintf(stderr, "Cannot read %s: %s\n", dir, strerror(errno) );
                    else{
                        char path_from[100];
                        char path_to[100];
                        
                        strcpy(path_from, dir);
                        strcpy(path_to, to);
                        
                        add_slash(path_from);
                        strcat(path_from,dc->d_name);

                        if(strcmp(to,"")!=0)
                            add_slash(path_to);
                        strcat(path_to,dc->d_name);
                        
                        f(path_from, path_to, param);

                        if(isDir(path_from)){
                            if(!is_parent_or_current_dir(dc->d_name)){ //if not .. or .
                                struct stat info;
                                if(stat(path_from, &info)<0)
                                    fprintf(stderr, "Cannot stat %s: %s\n", path_from, strerror(errno));
                                else{
                                    if(strcmp(to,"")==0){
                                        browse_rec(path_from, to, param, f);
                                    }else{
                                        if(!Exist(path_to))
                                            create_dir(path_to, info.st_mode);
                                        browse_rec(path_from, path_to, param, f);
                                    }
                                }      
                            }    
                        }  
                    }
                }
            }
            if (closedir(d)==-1)
                fprintf(stderr, "Cannot close %s: %s\n", dir, strerror(errno) );
        }
    }
}
