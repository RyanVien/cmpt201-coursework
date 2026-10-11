#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 64

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }

  write(STDOUT_FILENO, buf, len);
}

void initialize_block(struct header *block, uint64_t size, struct header *next, int value) {
  block->size = size;
  block->next = next;
  memset(block + 1, value, size - sizeof(struct header));
}

void *increase_heap_size(intptr_t extraSize) {
  void *p = sbrk(extraSize);

  if (p == (void *)-1) {
    handle_error("sbrk");
  }

  return p;
}

void print_block(struct header *block) {
  unsigned char *data = (unsigned char *)(block + 1);

  for (size_t i = 0; i < block->size - sizeof(struct header); i++) {
    uint64_t value = data[i];
    print_out("%lu\n", &value, sizeof(value));
  }
}

int main() {
  char *heapStart = increase_heap_size(256);
  struct header *block0 = (struct header *)heapStart;
  struct header *block1 = (struct header *)(heapStart + 128);

  initialize_block(block0, 128, NULL, 0);
  initialize_block(block1, 128, block0, 1);

  print_out("first block:       %p\n", &block0, sizeof(&block0));
  print_out("second block:      %p\n", &block1, sizeof(&block0));
  print_out("first block size:  %lu\n", &block0->size, sizeof(block0->size));
  print_out("first block next:  %p\n", &block0->next, sizeof(block0->next));
  print_out("second block size: %lu\n", &block1->size, sizeof(block1->size));
  print_out("second block next: %p\n", &block1->next, sizeof(block1->next));

  print_block(block0);
  print_block(block1);

  return 0;
}
