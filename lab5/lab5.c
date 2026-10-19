#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  struct header *curr = free_list_ptr;

  while (curr != NULL) {
    if (curr->size >= size) {
      return curr->id;
    }

    curr = curr->next;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  struct header *best = NULL;
  struct header *curr = free_list_ptr;

  while (curr != NULL) {
    if (curr->size >= size && (best == NULL || curr->size < best->size)) {
      best = curr;
    }

    curr = curr->next;
  }

  if (best != NULL) {
    best_fit_id = best->id;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  struct header *worst = NULL;
  struct header *curr = free_list_ptr;

  while (curr != NULL) {
    if (curr->size >= size && (worst == NULL || curr->size > worst->size)) {
      worst = curr;
    }

    curr = curr->next;
  }

  if (worst != NULL) {
    worst_fit_id = worst->id;
  }

  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  return 0;
}

/*
 * Part 2
 *
 * Free is already merged so I just have to deal with the block that was freed(z).
 * Need to check if a free block is next to z.
 *
 * Step 1:
 *  Look through free list form head. For each free block curr:
 *    - if curr ends exactly where z starts, curr is block before z
 *    - if curr starts exactly where z ends, curr is block after z
 *
 * Step 2:
 *  Check which of the following condition cases z is:
 *    - nothing before or after: add z to front of list
 *        z->next = head
 *        head = z
 *
 *    - only block before: make before block bigger
 *        before->size = before->size + z->size
 *
 *    - only block after: z replaces after block
 *        z->size = z->size + after->size
 *        z->next = after->next
 *        block that pointed to after, now points to z
 *
 *    - blocks before AND after: merge all three into before block
 *        before->size = before->size + z->size + after->size
 *        remove after block form list
 *
 *  Example:
 *    Free list is: head->n->b->m, and z was freed.
 *    m is before z and n is after z, so both exist.
 *    m, z, and n merge into m, n is removed from list
 *    New list: b->m, m is now bigger.
 */
