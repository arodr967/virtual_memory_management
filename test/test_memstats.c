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

int main() {
  int status;

  status = syscall(302);

  printf("Status: %d\n", status);
}
