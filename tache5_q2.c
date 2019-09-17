#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <pthread.h>


int *tab;
int *etat;
int NTH;
int MAX;
int DEMIMAX;
pthread_mutex_t var_mutex;
pthread_cond_t var_cond;
int threads_ready;


void *th_fonc(void *ptr);

void creat_thread(int nth, int max);

int main(int argc, char const *argv[]) {
    if(argc !=3)
    {
        perror("ERREUR NOMBRE D'ARGUMENTS");
        return 1;
    }
    NTH = atoi(argv[2]);
    MAX = atoi(argv[1]);
    DEMIMAX = (int)(MAX/2);
    float temps;
    clock_t t1, t2;

    t1 = clock();

    if((tab = malloc(DEMIMAX*sizeof(int)))==NULL){
        perror("ERREUR MALLOC");
        exit(1);
    }
    int ind;
    for(ind=0;ind<DEMIMAX;ind++)
        tab[ind]=1;

    pthread_t *threads = malloc(NTH*sizeof(pthread_t));

    pthread_cond_init(&var_cond, NULL);
    pthread_mutex_init(&var_mutex, NULL);
    threads_ready = 0;
    pthread_mutex_lock(&var_mutex);
    int is1,i,j;
    int* val;
    for(i=0; i<NTH;i++){
            val = malloc(sizeof(int));
            *val = 3+2*i;
            is1 = pthread_create(&threads[i], NULL, th_fonc,(void *)val); 

    }

    threads_ready = 1;
    pthread_mutex_unlock(&var_mutex);
    pthread_cond_broadcast(&var_cond);

    for(i=0;i<NTH;i++){
        is1 = pthread_join(threads[i],NULL);
    }

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("Execution time = %f\n", temps);
    if (MAX >=2)
      printf("2\n");
    for(ind=0; ind*2+3 < MAX;ind++)
        if(tab[ind]==1)
            printf("%d\n",2*ind+3);

    return 0;
}





void *th_fonc(void *ptr){
    int k=*(int *)ptr;
    pthread_mutex_lock(&var_mutex);
    while(threads_ready==0) pthread_cond_wait(&var_cond,&var_mutex);
    pthread_mutex_unlock(&var_mutex);

    int i,j;
    for(i=k; i<((int)sqrt(MAX)); i += 2*NTH){
      if(tab[(i-3)/2]==1)
      {
          for(j=i*i; j<MAX;j= j + 2*i){
              tab[(j-3)/2]=0;
          }
      }

    }
}