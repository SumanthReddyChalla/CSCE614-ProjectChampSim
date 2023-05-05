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
    // baseline LRU
    //return lru_victim(cpu, instr_id, set, current_set, ip, full_addr, type);
    
	uint32_t way = 0;

    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set * NUM_WAY + way].valid == false) {
            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY) {
        for (way=0; way<NUM_WAY; way++) {
            if (block[set * NUM_WAY + way].lru == NUM_WAY-1) {
                break;
            }
        }
    }

    if (way == NUM_WAY) {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }

    return way;

}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    string TYPE_NAME;
    // baseline LRU
    if (hit && (type == WRITEBACK)) // writeback hit does not update LRU state
        return;

      // update lru replacement state
    for (uint32_t i=0; i<NUM_WAY; i++) {
        if (block[set * NUM_WAY + i].lru < block[set * NUM_WAY + way].lru) {
            block[set * NUM_WAY + i].lru ++;
        }
    }
    block[set * NUM_WAY + way].lru = 0; // promote to the MRU position

}

void CACHE::replacement_final_stats()
{

}
