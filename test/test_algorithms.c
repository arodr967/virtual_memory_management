// COP4610 – Principles of Operating Systems – Summer C 2017
// Prof. Jose F. Osorio
// Student Name: Alicia Rodriguez – 5162522
// Project: Virtual Memory Management
// Specs: Test the different algorithms in part 2
// Due Date: 07/22/2017 by 11:55pm
// Module Name: test_algorithms.c

// I Certify that this program code has been written by me
// and no part of it has been taken from any sources.

#include <stdio.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
  clock_t start, end;
  double cpu_time_used;
  int i;
  int *test;

  start = clock();

  for (i = 0; i < 5000000; i++) {
    test = malloc(50 * sizeof(int));
  }
  free(test);

  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f\n", cpu_time_used);

  return 0;
}
