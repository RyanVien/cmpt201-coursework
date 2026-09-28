#include <stdio.h>
#include <unistd.h>

int main() {
  fork();

  char *message = "Hello world!\n";
  for (int i = 0; i < 20; i++) {
    printf("%c", message(1));
    fflush(stdout);
    sleep(5);
  }
  printf("\n");
  printf("DONE\n");

  return 0;
}
