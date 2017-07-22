// COP4610 – Principles of Operating Systems – Summer C 2017
// Prof. Jose F. Osorio
// Student Name: Alicia Rodriguez – 5162522
// Project: Virtual Memory Management
// Specs: memstats structure
// Due Date: 07/22/2017 by 11:55pm
// Module Name: memstats.h

// I Certify that this program code has been written by me
// and no part of it has been taken from any sources.

#ifndef MEMSTATS_H
#define MEMSTATS_H

struct memstats {
  unsigned long free_pages;                       /* current number of free pages */
  unsigned long slab_pages;                       /* current number of pages used by slab allocator */
  unsigned long active_list_pages;                /* current number of pages in the active list */
  unsigned long inactive_list_pages;              /* current number of pages in the inactive list */
  unsigned long active_list_ref_pages;            /* current number of pages in the active list whose reference bits are set */
  unsigned long inactive_list_ref_pages;          /* current number of pages in the inactive list whose reference bits are set */
  unsigned long total_active_to_inactive_pages;   /* cumulative number of pages moved from the active list to the inactive list */
  unsigned long total_taken_from_inactive_pages;  /* cumulative number of pages evicted from the inactive list */
};

#endif
