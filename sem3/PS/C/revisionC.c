#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void ex1(){
    long n = 15;
    long *p = &n;
    long **pp = &p;

    printf("a) les valeurs de p et pp ? %p, %p\nb) la valeur de *p ? %ld\nc) la valeur de *pp ? %p\nd) la valeur de **pp ? %ld\n", p,pp,*p,*pp,**pp);
}

typedef struct _strReplace{
    char s[50];
    char replace;
}strReplace;

void ex2(strReplace* a){
    for(long unsigned i = 0; i<strlen(a->s); i++){
        if(a->s[i]==' '){
            a->s[i]=a->replace;
        }
    }
    
}

char* ex3(strReplace* a){
    char* res = (char*)malloc(sizeof(char)*50);   
    for(long unsigned i = 0; i<strlen(a->s); i++){
        res[i] = a->s[i];
        if(res[i]==' '){
            res[i]=a->replace;
        }
    }
    char tmp[50];
    for(long unsigned i = 0; i<strlen(res); i++){
        tmp[i] = res[i];
    }
    for(long unsigned i = 0; i<strlen(res); i++){
        res[i] = tmp[strlen(tmp)-1-i];
    }
    return res;
}

void ex4(int argc, char** argv){
    if(argc != 5){
        printf("Usage : %s label <n (nombre itérations)> <x (nombre décimal)> <y (nombre entier) >\n", argv[0]);
    }else{
        printf("%s\n", argv[1]);
        int n = atoi(argv[2]);
        double x = atof(argv[3]);
        int y = atoi(argv[4]);

        for(int m=0; m<n; m++){
            printf("%lf^%d = %lf\n",x,y+m, pow(x,y+m));
        }
    }
}

int main(int argc, char** argv){
    int ex=4;
    strReplace sr = {"Je remplace les espaces ", '0'};
    switch(ex){
        case 1:
            ex1();
            break;
        case 2: 
            ex2(&sr);
            printf("%s\n",sr.s);
            break;
        case 3:{ 
            char* r = ex3(&sr);
            printf("%s\n", r);
            free(r);
            break;
        }    
        case 4:
            ex4(argc, argv);
    }
    return 0;
}