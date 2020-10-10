#include "slab_test.hh"
#include "slab.hh"

#include <cassert>

#include <chrono>
using namespace std::chrono_literals;

static Memory::Slab::Area<int, 16> area;
static Memory::Slab::Allocator<int> allocator(area);

void Test_Slab() {
    int* ptrs[area.size()];

    assert(allocator.blocks_free() == area.size());
    for (size_t i = 0; i < area.size(); i++) {
        ptrs[i] = allocator.allocate();
    }
    assert(allocator.blocks_free() == 0);
    assert(allocator.allocate(10ms) == nullptr);
    for (size_t i = 0; i < area.size(); i++) {
        allocator.deallocate(ptrs[i]);
    }
    assert(allocator.blocks_free() == area.size());
}