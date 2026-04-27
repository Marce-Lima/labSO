#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

int main() {
  char comando[MAX];
  int booleano;
  int contador;
  int pid, i; 
  char* tk[128];
  char* ta;
  
  //inicialização
  for(int i = 0; i < 128; i++){
    tk[i] = NULL;
  }

  //loop shell
  while (1) {
    booleano = 0;// booleano para identificar o & e avisar para que nao é para ser executado
    contador = 0; // Conta quantas palavras tem a string kk
    printf("> ");
    if(!fgets(comando, MAX, stdin)){
        break;
    }// nao deixa entrar mais doq pode
    
    comando[strcspn(comando, "\n")] = 0;
    // tira o \n
    
    if(!strcmp(comando, "exit")){
      exit(EXIT_SUCCESS);
    }
    
    tk[0] = strtok(comando, " ");
    if(tk[0] == NULL){
        continue;
    }// caso a primeira palavra seja um enter
    
    
    contador++;
    
    //loop todas as palavras
    for(int i = 1; ta = strtok(NULL, " "); i++, contador++){
        tk[i] = ta;
        printf("%s\n", tk[i]);
    }
    
    // verifica em todas as palavras se te um &
    for(int i = 1; i < contador; i++){
        if(strcmp(tk[i], "&") == 0){
            tk[i] = NULL;
            booleano = 1;
        }
        
    }
    
    if(strcmp(tk[0], "exit") == 0){
      exit(EXIT_SUCCESS);
    }
    
    pid = fork();
    if (pid == 0) {
        execvp(tk[0], tk);
      printf("Erro ao executar comando!\n");
      exit(EXIT_FAILURE); 
    } else {
      if(booleano == 0){
          waitpid(pid, NULL, 0); 
       }
    }
    
    
    //Zerando o vetor para ser usado novamente ;)
    for(int i = 0; i < 128; i++){
        tk[i] = NULL;
    }
  }
}