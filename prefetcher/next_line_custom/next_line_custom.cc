#include "next_line_custom.h"

#include "cache.h"

/* Initialize the prefetcher's utility variables */
void CACHE::prefetcher_initialize() {
    for(int i=0; i<NUM_CPUS; i++)
        prev_page_id[i] = -1;    /* Set it to the maximum 64-bit value */
}


uint32_t CACHE::prefetcher_cache_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint32_t metadata_in) {
    uint64_t page_id = EXTRACT_PAGE_ID(addr);        /* Extract out the page ID of the current load/store */
    uint32_t block_id = EXTRACT_BLOCK_ID(addr);      /* Extract out the block ID of the current load/store */
    int32_t prefetch_block_id = (int32_t) block_id;  /* Temporarily store the block ID that we'll increment/decrement later on */
    uint64_t prefetch_addr;                          /* Where we'll store the prefetch address later on */
   
    /* Check if the access is on the same page as previous page */
    /* If no, then reset the buffer and return */
    /* NOTE: cpu is a member variable of CACHE, which stores the ID of the CPU where the cache belongs */
    if(!is_on_same_page(cpu, page_id)) {
        hist_buff[cpu].reset();
        return 0;
    }
   
    /* Previous access was to the same page - We can continue */
    hist_buff[cpu].append(block_id);                   /* Append the latest block ID to the buffer */
   
    /* If the history buffer is not full, we can't send a prefetch request */
    if(!hist_buff[cpu].is_full())
        return 0;
   
    /* History buffer is full -- We can continue */
    /* If the buffer has forward-movement, we will prefetch the next block. Else the previous block */
    if(hist_buff[cpu].has_forward_movement())
        prefetch_block_id++;
    else
        prefetch_block_id--;
   
    /* Now we can send a prefetch request, if the prefetch block falls in the same page */
    if(prefetch_block_id >= BLOCK_ID_MIN && prefetch_block_id <= BLOCK_ID_MAX) {
        prefetch_addr = prepare_prefetch_address(page_id, prefetch_block_id);   /* Prepare the address to prefetch */
       
        /* Finally send the prefetch ! */
        /* The prefetch will be filled till L1-D */
        /* Because we don't have any use for metadata, set it to 0 */
        prefetch_line(ip, addr, prefetch_addr, FILL_L1, 0);
    }
  return metadata_in;
}


uint32_t CACHE::prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{
  return metadata_in;
}

void CACHE::prefetcher_cycle_operate() {}

void CACHE::prefetcher_final_stats() {}