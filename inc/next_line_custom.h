#include "champsim.h"

#include <deque>

/* Convenient macros to extract out page ID and block ID from a given 64-bit address */
#define EXTRACT_PAGE_ID(addr)   ((addr) >> LOG2_PAGE_SIZE)              /* Extract the page ID */
#define EXTRACT_BLOCK_ID(addr)  (((addr) >> LOG2_BLOCK_SIZE) & 0x3f)    /* Extract the block ID within the page */
 
/* Minimum and maximum value of the block IDs */
#define BLOCK_ID_MIN    0
#define BLOCK_ID_MAX    ((PAGE_SIZE / BLOCK_SIZE) - 1)

/* The length of the buffer, i.e. 'K' as mentioned in the question */
/* Tweak this value accordingly */
#define BUFFER_LENGTH   5

/* Utility method to prepare the address to prefetch */
uint64_t prepare_prefetch_address(uint64_t page_id, uint32_t block_id) {
    return (page_id << LOG2_PAGE_SIZE) + (block_id << LOG2_BLOCK_SIZE);
};

/* NUM_CPUS is a pre-defined constant set to the number of cores to use in the simulation */
uint64_t prev_page_id[NUM_CPUS];    /* Store the IDs of the previous page, per prefetcher */

/* Returns True if the access is to the same page. False otherwise */
bool is_on_same_page(uint32_t cpu_id, uint64_t curr_page_id) {
    uint64_t tmp_prev_page_id = prev_page_id[cpu_id];   /* Temporarily store the value of previous page ID */
    prev_page_id[cpu_id] = curr_page_id;                /* Update the page ID of the latest page accessed */
   
    /* If previous page ID is same as the current page ID */
    if(curr_page_id == tmp_prev_page_id)
        return true;
   
    /* Nope, it's different. Return False */
    return false;
};

class HistoryBuffer {
    std::deque<uint32_t> buffer;    // Use deque as internal data structure
    uint32_t max_size;              // Maximum capacity of the buffer
   
public:
    // Constructor
    HistoryBuffer(uint32_t k) {
max_size = k;
}
   
    // Return the current size of the buffer
    int32_t size() {
        return buffer.size();
    }
   
    // Append a cache block # to the back of the buffer
    void append(uint32_t blk_id) {
        buffer.push_back(blk_id);
       
        // Ensure that the buffer stores only K most-recent entries
        if (buffer.size() > max_size) {
            buffer.pop_front();
        }
    }

   // Reset the buffer by removing all elements
    void reset() {
        buffer.clear();
    }
   
    // Check if the buffer is full
    bool is_full() {
        return buffer.size() == max_size;
    }
   
    // Check if there is forward movement in the buffer
    bool has_forward_movement() {
        uint32_t maxsize = max_size;
        uint32_t num_forward = 0;
        for (uint32_t i = 0; i < maxsize -1; i++) {
            if (buffer[i] < buffer[i + 1]) {
                num_forward++;
            }
        }
        return num_forward >= ((max_size - 1) / 2 + 1);
    }
};

/* Declare buffers per prefetcher */
HistoryBuffer hist_buff[NUM_CPUS] = {HistoryBuffer(BUFFER_LENGTH)};    /* History-Buffer Module for the prefetcher */

