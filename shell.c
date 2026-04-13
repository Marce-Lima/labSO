#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

int main() {
  char comando[MAX];
  int pid;

  while (1) {
    printf("> ");
    scanf("%s", comando); //fget - ler comandos inteiros
    if (!strcmp(comando, "exit")) {
      exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid) {
      waitpid(pid, NULL, 0); //ler com & 
    } else {
      execlp(comando, comando, NULL);
      printf("Erro ao executar comando!\n");
      exit(EXIT_FAILURE);
    }
  }
}

//execvp
