#ifndef MEMSTATS_H
#define MEMSTATS_H

struct memstats {
  unsigned long free_pages;                    /* current number of free pages */
  unsigned long slab_pages;                     /* current number of pages used by slab allocator */
  int active_list_pages;              /* current number of pages in the active list */
  int inactive_list_pages;            /* current number of pages in the inactive list */
  int active_list_ref_pages;          /* current number of pages in the active list whose reference bits are set */
  int inactive_list_ref_pages;        /* current number of pages in the inactive list whose reference bits are set */
  int total_active_to_inactive_pages; /* cumulative number of pages moved from the active list to the inactive list */
  int total_from_inactive_pages;      /* cumulative number of pages evicted from the inactive list */
};

#endif
