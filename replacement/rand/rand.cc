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
  return rand() % NUM_WAY + 0;

}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
  string TYPE_NAME;
}

void CACHE::replacement_final_stats()
{

}
