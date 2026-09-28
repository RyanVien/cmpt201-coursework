#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    execl("/bin/ls", "-a", NULL);
  }

  else {
    execl("/bin/ls", "-alh", NULL);
  }

  printf("%d\n", getpid());

  return 0;
}
