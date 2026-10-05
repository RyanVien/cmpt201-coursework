#define _POSIX_C_SOURCE 200809
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5

char *records[MAX_LEN];
int recordCount = 0;

char *getInput() {
  char *buffer = NULL;
  size_t buffSize = 0;
  printf("Enter input: ");
  size_t len = getline(&buffer, &buffSize, stdin);

  if (len == -1) {
    exit(1);
  }

  buffer[len - 1] = '\0';
  return buffer;
}

void deleteLastRecord() {
  if (recordCount > 0) {
    free(records[0]);

    for (int i = 0; i < recordCount - 1; i++) {
      records[i] = records[i + 1];
    }

    recordCount--;
  }
}

void addRecord(char *input) {
  if (recordCount >= 5) {
    deleteLastRecord();
  }

  records[recordCount] = input;
  recordCount++;
}

void printRecords() {
  if (recordCount > 0) {
    for (int i = 0; i < recordCount; i++) {
      printf("%s\n", records[i]);
    }
  }
}

int main() {
  while (1) {
    char *input = getInput();
    addRecord(input);

    if (strcmp(input, "print") == 0) {
      printRecords();
    }
  }

  return 0;
}
