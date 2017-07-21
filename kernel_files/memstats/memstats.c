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
#include <linux/mmzone.h>
#include <linux/mm.h>
#include <linux/vmstat.h>
#include <linux/list.h>
#include <linux/memstats.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

extern int IS_COUNTER_BASED_CLOCK;

void init_kernel_stats(struct memstats *kernel_stats);
void set_counter_based_clock(struct memstats *kernel_stats);

asmlinkage long sys_memstats(struct memstats *stats) {

  struct zone *zones;
  struct page *page_ptr;
  struct pglist_data *data_ptr;
  struct list_head *active_page, *inactive_page;
  struct memstats *kernel_stats = kmalloc(sizeof(*kernel_stats), GFP_KERNEL);

  unsigned long nr_slab = 0,
    free_pages = 0;

  int active_list_pages = 0,
    inactive_list_pages = 0,
    active_list_ref_pages = 0,
    inactive_list_ref_pages = 0;

  if (kernel_stats == NULL) {
    printk(KERN_ERR "sys_memstats: Failure to kmalloc\n");
    return -1;
  }

  // If the address for the memstats structure is null
  if (stats == NULL) {
    // Invalid argument
    printk(KERN_ERR "sys_memstats: Invalid argument\n");
    return -22;
  }

  printk(KERN_INFO "sys_memstats: Starting memstats system call...\n");

  set_counter_based_clock(stats);
  init_kernel_stats(kernel_stats);

  for_each_online_pgdat(data_ptr) {
    // Initialize zones
    zones = data_ptr->node_zones;

    // Traverse over all memory zones
    for_each_zone(zones) {

      // Get each free page
      free_pages += zones->free_pages;

      // Get pages used by slab allocator
      nr_slab += global_page_state(NR_SLAB);

      // Get each active page
      list_for_each(active_page, &(zones->active_list)) {
        active_list_pages++;

        // Test for the active list referenced pages
        page_ptr = list_entry(active_page, struct page, lru);
        active_list_ref_pages += test_bit(PG_referenced, &page_ptr->flags);
      }

      // Get each inactive page
      list_for_each(inactive_page, &(zones->inactive_list)) {
        inactive_list_pages++;

        // Test for the inactive list referenced pages
        page_ptr = list_entry(inactive_page, struct page, lru);
        inactive_list_ref_pages += test_bit(PG_referenced, &page_ptr->flags);
      }
    }
  }

  kernel_stats->free_pages = free_pages;
  kernel_stats->slab_pages = nr_slab;
  kernel_stats->active_list_pages = active_list_pages;
  kernel_stats->inactive_list_pages = inactive_list_pages;
  kernel_stats->active_list_ref_pages = active_list_ref_pages;
  kernel_stats->inactive_list_ref_pages = inactive_list_ref_pages;

  printk(KERN_INFO "sys_memstats: Updated memstats values\n");

  // Copy kernel-space memstats into user-space memstats
  if(copy_to_user(stats, kernel_stats, sizeof(*kernel_stats))) {
    return -EFAULT;
  }

  printk(KERN_INFO "sys_memstats: End of memstats system call\n");

  return 0;
}

void init_kernel_stats(struct memstats *kernel_stats) {
  kernel_stats->free_pages = 0;
  kernel_stats->slab_pages = 0;
  kernel_stats->active_list_pages = 0;
  kernel_stats->inactive_list_pages = 0;
  kernel_stats->active_list_ref_pages = 0;
  kernel_stats->inactive_list_ref_pages = 0;
  kernel_stats->total_active_to_inactive_pages = 0;
  kernel_stats->total_from_inactive_pages = 0;

  printk(KERN_INFO "sys_memstats: Initialized memstats values to 0\n");
}

void set_counter_based_clock(struct memstats *stats) {
  if (stats->is_counter_based_clock == 1) {
    IS_COUNTER_BASED_CLOCK = 1;
    printk(KERN_INFO "sys_memstats: Using counter-based clock algorithm...\n");
  } else {
    IS_COUNTER_BASED_CLOCK = 0;
    printk(KERN_INFO "sys_memstats: Using second-chance LRU approximation algorithm...\n");
  }
}
