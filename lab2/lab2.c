#define _POSIX_C_SOURCE 200809
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
  char *input = NULL;
  size_t length = 0;

  while (true) {
    printf("Enter progress to run.\n");
    printf("> ");

    if ((length = getline(&input, &length, stdin)) != -1) {
      input[length - 1] = '\0';
      printf("Command will be: %s\n", input);

      pid_t pid = fork();

      if (pid != 0) {
        pid_t ppid = waitpid(pid, NULL, 0);

        if (ppid == -1) {
          printf("ERROR waiting for PID\n");
        }
      }

      else {
        if (execlp(input, input, NULL) == -1) {
          printf("Exec failure\n");
          free(input);
          exit(EXIT_FAILURE);
        }
      }
    }

    else {
      printf("Getline failed\n");
      free(input);
      exit(EXIT_FAILURE);
    }
  }
}
