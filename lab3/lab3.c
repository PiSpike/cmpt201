// Spike Sorensen
// CMPT201 Lab3

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// char *readline(int number)
int main() {
  char *line[5] = {NULL};
  size_t size[5] = {0};
  size_t nread;
  int i = 0;

  while (1) {

    printf("Enter: ");
    if (line[i % 5] != NULL) {
      free(line[i % 5]);
      size[i % 5] = 0;
    }
    nread = getline(&line[i % 5], &size[i % 5], stdin);
    line[i % 5][nread - 1] = '\0';
    if (strcmp(line[i % 5], "print") == 0) {
      for (int j = i - 4; j <= i; j++) {
        if (j < 0) {
          j = 0;
        }
        if (line[j % 5] != NULL) {
          printf("%s\n", line[j % 5]);
        }
      }
    }
    i++;
  }
}
