
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>



#define THREADS_MAX 4

//funcao que calcula se o numero eh primo ou nao
unsigned int primo(unsigned int N) {
	int c;
	int div = 0;
	for (c = 1; c <= N; c++) {
    		if (N % c == 0) { 
     		div++;
    		}
  	}
    
  	if ( div == 2) {return 1;}
  	else {return 0; }
}


int n_completos = 0; //indica quantos numeros foram processados
pthread_mutex_t trava;
int count = 0; //indica quantos numeros primos tem na entrada
int aux = 0;
int pointer = 0;//apontador que ira percorrer o vetor que armazena valores de entrada
int p=0, q=0; //variaveis utilizadas nos for's
int array[100]; //vetor da entrada

void* worker(void *arg) {
  int *N = (int*)(arg);
  int M = (*N);
  //printf("Iniciando thread %d\n", M);
  int atuador = -1;
  
  
  while (1) {
    if (n_completos >= p) break;
    pthread_mutex_lock(&trava);
    atuador = array[pointer];
    n_completos += 1;
    aux = primo(array[pointer]);
    if (aux == 1) {(count)++;}
    pointer++;
    pthread_mutex_unlock(&trava);
    //printf("Numero %d acessado por thread %d\n", atuador, M);
    
    
    for (int j=0; j<500000; j++);
  }
  //printf("Saindo de thread %d\n", M);
  return NULL;
}



int main(int argc, char **argv) {
  pthread_t workers[THREADS_MAX];
  int thread_id[THREADS_MAX];



  /*Tratamento e armazenamento da sequência de números (input)*/

  char temp;
  do {
      scanf("%d%c", &array[p], &temp);
      p++;
      } while(temp != '\n');

int num_threads = 0;

  // definindo o número de threads
  if(p <= 4){
   num_threads = (p % 5);
  }
  
  else if(p > 4){
  num_threads = THREADS_MAX;
  }

//printf("numero de threads: %d\n", num_threads);
  /* Identificadores de thread */
  for (int i=0; i<num_threads; i++) {
    thread_id[i] = i;
  }

  /* Disparanto threads */
  for (int i=0; i<num_threads; i++) {
    pthread_create(&(workers[i]), NULL, worker, (void*) (&thread_id[i]));
  }

  /* Esperando threads */
  for (int i=0; i<num_threads; i++) {
    pthread_join(workers[i], NULL);
  }

printf("%d\n", count);

  return 0;
}
