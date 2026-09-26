// Spike Sorensen
// CMPT201 Lab2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define _POSIX_C_SOURCE 200809L

int main() {
  char *line = NULL;
  size_t size = 0;
  size_t nread;
  int wstatus;
  int execstatus;
  pid_t cpid, w;

  while (1) {
    printf("Enter a program to run: ");
    nread = getline(&line, &size, stdin);
    // printf("Length: %zd\n", nread);
    if (nread == 1) {
      printf("Exit\n");
      free(line);
      break;
    }
    // Need line to end with \0 for execlp() to work
    line[nread - 1] = '\0';

    cpid = fork();
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cpid == 0) {
      // printf("Child\n");
      execstatus = execlp(line, line, (char *)NULL);
      if (execstatus == -1) {
        printf("Fail\n");
        break;
      }
    } else {
      // printf("Parent\n");
      w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
      if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
    }
  }
}
