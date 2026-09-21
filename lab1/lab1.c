#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *ret;
  char *saveptr;
  char *buff = NULL;
  size_t size = 0;
  printf("Please enter some text: ");
  ssize_t num_char = getline(&buff, &size, stdin);

  if (num_char == -1) {
    perror("getline failed");
    return 1;
  }

  printf("Tokens:\n");

  ret = strtok_r(buff, " ", &saveptr);
  while (ret != NULL) {
    printf("\t%s\n", ret);
    ret = strtok_r(NULL, " ", &saveptr);
  }
  free(buff);
  return 0;
}
