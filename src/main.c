
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


int n_processados = 0; //indica quantos numeros foram processados
pthread_mutex_t trava;
int count = 0; //indica quantos numeros primos tem na entrada
int aux = 0; //variavel auxiliar
int pointer = 0;//apontador que ira percorrer o vetor que armazena valores de entrada
int p=0; //variavel utilizada no for
int array[100]; //vetor que armazena a entrada

void* funcao_thread(void *arg) {
  int *N = (int*)(arg); 
  int M = (*N); //indica qual eh a thread
  int atuador = -1; //variavel que recebera os valores de entrada, um de cada vez
  
  
  while (1) {
    if (n_processados >= p) break; //enquanto todos os numeros nao forem 
    pthread_mutex_lock(&trava); 
    atuador = array[pointer]; //passa numero a ser checado para a variavel atuador
    n_processados += 1; //marca como como concluida a checagem do numero
    pointer++; //avanca no vetor de armazenamento da entrada
    pthread_mutex_unlock(&trava);
    
//verifica se o numero eh primo ou nao
    aux = primo(atuador);
    if (aux == 1) {(count)++;} //se for, adiciona +1 na variavel contadora
    
    
    for (int j=0; j<500000; j++); //causar um atraso
  }
  return NULL;
}



int main(int argc, char **argv) {
  //identificando as threads
  pthread_t threads[THREADS_MAX];
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

  /* Identificadores de thread */
  for (int i=0; i<num_threads; i++) {
    thread_id[i] = i;
  }

  /* Disparanto threads */
  for (int i=0; i<num_threads; i++) {
    pthread_create(&(threads[i]), NULL, funcao_thread, (void*) (&thread_id[i]));
  }

  /* Esperando threads */
  for (int i=0; i<num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

printf("%d\n", count); //resultado final

  return 0;
}
