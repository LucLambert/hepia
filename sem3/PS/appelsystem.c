#include <stdio.h>
#include <errno.h>
int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage : %s filename", argv[0]);
        return 1;
    }else{
        FILE* fp=fopen(argv[1],"r");
        if(fp==NULL){
            perror(argv[1]);
        }else{
            while(!feof(fp)){
                printf("%c",fgetc(fp));
            }
            fclose(fp);
        }
        printf("\n");
    }
    return 0;
}