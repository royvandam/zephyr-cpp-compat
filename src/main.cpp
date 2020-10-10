#include <logging/log.h>
LOG_MODULE_REGISTER(sandbox, LOG_LEVEL_INF);

#include "thread.hh"

#include "memory.hh"
#include "memory/slab_test.hh"

#include "chrono.hh"
using namespace std::chrono_literals;

#include <zephyr.h>

void main(void) {
    LOG_INF("Testing Memory::Slab::Allocator...");
    Test_Slab();
    LOG_INF("Success!");

    while (1) {
        std::this_thread::sleep_for(1000ms);
    }
}
