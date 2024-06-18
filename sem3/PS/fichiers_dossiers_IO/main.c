#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ls_l.h"
#include "rec.h"
#include "cp.h"

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage : %s [dirs/files] (dir/file)\n", argv[0]);
        return -1;
    }else if(argc==2){
        //ls
        char* name = argv[1];
        browse_rec(name, "", 0, print_long);
    }else{
        //cp
        int opt;
        short type;
        while((opt=getopt(argc, argv, "af")) !=-1){
            type=0;
            switch(opt){
                case 'a':
                    type+=1;
                    break;
                case 'f':
                    type+=2;
                    break;
            }
        }

        char* args[50];
        extern int optind;
        for(int i=0; i<argc-optind;i++){
            args[i]=argv[i+optind];
        }
        cp(args,argc-optind,type);
    }
    return 0;
}