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
void validate_arguments(int argc, char *argv[]);
void check_algorithms(int is_counter_based_clock);

int main(int argc, char *argv[]) {
  struct memstats *mem_stats;
  int status, is_counter_based_clock;

  validate_arguments(argc, argv);
  
  is_counter_based_clock = atoi(argv[1]);

  mem_stats = malloc(sizeof(*mem_stats));

  /* Set counter-based clock algorithm */
  mem_stats->is_counter_based_clock = is_counter_based_clock;
  check_algorithms(is_counter_based_clock);

  /* Call new system call */
  status = syscall(302, mem_stats);

  printf("Current number of free pages: %d\n", mem_stats->free_pages);
  printf("Current number of pages used by slab allocator: %d\n", mem_stats->slab_pages);
  printf("Current number of pages in the active list: %d\n", mem_stats->active_list_pages);
  printf("Current number of pages in the inactive list: %d\n", mem_stats->inactive_list_pages);
  printf("Current number of pages in the active list whose reference bits are set: %d\n", mem_stats->active_list_ref_pages);
  printf("Current number of pages in the inactive list whose reference bits are set: %d\n", mem_stats->inactive_list_ref_pages);
  printf("Cumulative number of pages moved from the active list to the inactive list: %d\n", mem_stats->total_active_to_inactive_pages);
  printf("Cumulative number of pages evicted from the inactive list: %d\n", mem_stats->total_from_inactive_pages);

  if (status < 0) {
    printf("Something went wrong. Status: %d\n", status);
    return 0;
  }

  return 0;
}

void validate_arguments(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s <is_counter_based_clock>\n", argv[0]);
    exit(-1);
  }
}

void check_algorithms(int is_counter_based_clock) {
  if (is_counter_based_clock) {
    printf("Counter-clock based algorithm...\n");
  } else {
    printf("Second-chance LRU approximation algorithm...\n");
  }
}
