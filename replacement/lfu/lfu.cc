#include <algorithm>
#include <iterator>

#include "cache.h"
#include "util.h"

// initialize replacement state
void CACHE::initialize_replacement()
{

}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{

    uint32_t way = 0;
    uint32_t small;
    uint32_t small_idx;
 
    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set * NUM_WAY + way].valid == false) {
            break;
        }
    }

    small = block[set * NUM_WAY + 0].lru;
    small_idx = 0;
    
    if (way == NUM_WAY) {
    // all ways are valid, find the least frequently used way
        for (way=0; way<NUM_WAY; way++) {
            if (small > block[set * NUM_WAY + way].lru) {
                small = block[set * NUM_WAY + way].lru;
                small_idx = way;
                break;
            }
        }
    }

            
    block[set * NUM_WAY + small_idx].lru = 0;

    way = small_idx;

    if (way >= NUM_WAY) {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }
    return way;

}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    string TYPE_NAME;
   
    if (hit && (type == WRITEBACK)) //Writeback hit doesn't update LFU state
        return;

       // update LFU state
    block[set * NUM_WAY + way].lru = block[set * NUM_WAY + way].lru + 1;
     
}

void CACHE::replacement_final_stats()
{

}