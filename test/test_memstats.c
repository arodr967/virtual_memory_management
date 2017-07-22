// COP4610 – Principles of Operating Systems – Summer C 2017
// Prof. Jose F. Osorio
// Student Name: Alicia Rodriguez – 5162522
// Project: Virtual Memory Management
// Specs: Test sys_memstats system call
// Due Date: 07/22/2017 by 11:55pm
// Module Name: test_memstats.c

// I Certify that this program code has been written by me
// and no part of it has been taken from any sources.

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <memstats.h>

// Function declarations
void print_stats(struct memstats *mem_stats);
void run_system_call(struct memstats *mem_stats);

int main() {
  struct memstats *mem_stats;
  int i, *test;

  mem_stats = malloc(sizeof(*mem_stats));
  run_system_call(mem_stats);
  printf("\nMemory statistics without allocating a lot of memory...\n");
  print_stats(mem_stats);

  // Allocate a lot of memory
  for (i = 0; i < 5000000; i++) {
    test = malloc(50 * sizeof(int));
  }

  run_system_call(mem_stats);
  printf("\nMemory statistics with allocating a lot of memory...\n");
  print_stats(mem_stats);

  free(test);

  return 0;
}

void run_system_call(struct memstats *mem_stats) {
  int status;

  /* Call new system call */
  status = syscall(302, mem_stats);

  if (status < 0) {
    printf("Something went wrong. Status: %d\n", status);
    exit(-1);
  }
}

void print_stats(struct memstats *mem_stats) {
  printf("Current number of free pages: %d\n", mem_stats->free_pages);
  printf("Current number of pages used by slab allocator: %d\n", mem_stats->slab_pages);
  printf("Current number of pages in the active list: %d\n", mem_stats->active_list_pages);
  printf("Current number of pages in the inactive list: %d\n", mem_stats->inactive_list_pages);
  printf("Current number of pages in the active list whose reference bits are set: %d\n", mem_stats->active_list_ref_pages);
  printf("Current number of pages in the inactive list whose reference bits are set: %d\n", mem_stats->inactive_list_ref_pages);
  printf("Cumulative number of pages moved from the active list to the inactive list: %d\n", mem_stats->total_active_to_inactive_pages);
  printf("Cumulative number of pages evicted from the inactive list: %d\n", mem_stats->total_taken_from_inactive_pages);
}
