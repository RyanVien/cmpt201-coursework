#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("PID: %d, PPID: %d\n", getpid(), getppid());
  pid_t pid = fork();

  if (pid == 0) {
    printf("Child: PID = %d, parent PID =%d\n", getpid(), getppid());
  }

  else {
    printf("Parent: PID = %d, child PID =%d\n", getpid(), pid);
  }

  return 0;
}
