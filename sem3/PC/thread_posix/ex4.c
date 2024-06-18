#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct my_tab{
    int size;
    int* tab;
} my_tab_t;

void *thread(void *arg){
    int* res=(int*)malloc(sizeof(int));
    *res=0;
    my_tab_t* t=(my_tab_t*)arg;
    for(int i=0; i<t->size; i++){
        *res+=t->tab[i];
    }
    printf("intermediate res=%d\n",*res);
    return res;
}

void inc_mat(int M, int size, int N,int (*mat)[size]){
    int cpt=1;
    for(int i=0; i<size; i++){
        for(int j=0; j<M; j++){
            if(cpt>N)
                mat[j][i]=0;
            else
                mat[j][i]=cpt++;
        }
    }
}

void print_math(int M, int size,int (*mat)[size]){
    for(int i=0; i<M; i++){
        for(int y=0; y<size; y++){
            printf(" %d ",mat[i][y]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    if(argc!=3){
        fprintf(stderr,"Usage: %s nbr threads\n", argv[0]);
        return EXIT_FAILURE;
    }else{
        int N,M;
        N=atoi(argv[1]);
        M=atoi(argv[2]);
        if(N<M){
            fprintf(stderr,"threads to important\n");
            return EXIT_FAILURE;
        }
        int size_max=N/M;
        if(N%M>0){
            size_max+=1;
        }
        int mat[M][size_max];
        inc_mat(M,size_max,N,mat);
        print_math(M, size_max, mat);

        pthread_t threads[M];
        my_tab_t ts[M];
        for(int i=0; i<M; i++){
           ts[i].size = size_max;
           ts[i].tab = mat[i];
        } 

        for(int i=0; i<M; i++){
            if(pthread_create(&threads[i], NULL, thread, &ts[i]) != 0){
                fprintf(stderr,"failed to create thread\n");
                return EXIT_FAILURE;
            }
        }

        int sum[M];
        int* tmp;
        for(int i=0; i<M; i++){
            if(pthread_join(threads[i], (void**)&tmp)!=0){
                fprintf(stderr, "pthread_join failed!\n");
                return EXIT_FAILURE;
            }
            sum[i]=*tmp;
            free(tmp);
        }

        int res1=0;
        for(int i=0; i<M; i++){
            res1+=sum[i];
        }
        printf("thread res = %d\n",res1);

        int res2=0;
        for(int i=0; i<M;i++){
            for(int y=0; y<size_max; y++){
                res2+=mat[i][y];
            }
        }
        printf("sequentielle res = %d\n",res2);

        return EXIT_SUCCESS;
    }
}