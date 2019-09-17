#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

int* tab = NULL;
void cribleSequentiel(int n){
    if (n<=3) return;
    n=n-2;
    if((tab = malloc(sizeof(int)*n))==NULL){
      perror("ERREUR MALLOC");
      exit(1);
    }
    int i;

    //initialisation de tous les elements à 1
    for(i=0; i<=n;i++) tab[i]=1;

    //cherche les nombres premiers de 2 a n
    for(i=2; i<=((int)sqrt(n)); i++)
    if(tab[i]==1){
        int j;
        for(j = i*i; j<n; j+=i) tab[j]=0;
    }
}

int main(int argc, char* argv[]){
  if(argc !=2)
  {
    perror("ERREUR NOMBRE D'ARGUMENTS");
    return 1;
  }
  int MAX = atoi(argv[1]);

  float temps;
  clock_t t1, t2;

  t1 = clock();

  cribleSequentiel(MAX);

  t2 = clock();
  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  printf("Execution time = %f\n", temps);
  int qtePremier =0;
  int ind;
  for(ind=2; ind <= MAX;ind++)
    if(tab[ind]==1)
      qtePremier++;

  printf("Quantité de nombres Premiers: %d\n",qtePremier);
  return 0;
}