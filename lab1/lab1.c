#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *line = NULL;
  size_t size = 0;
  ssize_t nread;

  printf("Please enter some text: ");
  nread = getline(&line, &size, stdin);
  // printf("Retrieved line of length %zd:\n", nread);
  // printf("%s\n", line);

  char *saveptr;
  char *token;
  token = strtok_r(line, " ", &saveptr);
  printf("Tokens:\n%s\n", token);
  for (int j = 1;; j++) {
    token = strtok_r(NULL, " ", &saveptr);
    if (token == NULL)
      break;
    printf("%s\n", token);
  }

  free(line);
}
