// COP4610 – Principles of Operating Systems – Summer C 2017
// Prof. Jose F. Osorio
// Student Name: Alicia Rodriguez – 5162522
// Project: Virtual Memory Management
// Specs: sys_memstats system call
// Due Date: 07/22/2017 by 11:55pm
// Module Name: memstats.c

// I Certify that this program code has been written by me
// and no part of it has been taken from any sources.

#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

asmlinkage long sys_memstats(void) {
  printk(KERN_INFO "Hello world!\n");
  return 0;
}
