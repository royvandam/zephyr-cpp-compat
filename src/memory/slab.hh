#pragma once

#include <zephyr.h>
#include <cassert>
#include <cstdint>
#include <chrono>

namespace Memory::Slab {
    template<typename T, std::size_t N>
    class Area {
    private:
        T __aligned(4) _memory[N];

    public:
        T* pointer() { return _memory; };
        constexpr std::size_t size() const { return N; }
    };

    template<typename T>
    struct Allocator {
    public:
        using value_type = T;

    private:
        struct k_mem_slab _slab;

    public:
        template<std::size_t N>
        Allocator(Area<T, N>& area) {
            k_mem_slab_init(&_slab, area.pointer(), sizeof(T), area.size());
        }

        [[nodiscard]] T* allocate(std::size_t n = 1) noexcept {
            // There is no guaranty multiple blocks are aligned consecutively.
            assert(n == 1); 

            // Allocate memory
            using namespace std::chrono_literals;
            return allocate(0ms);
        }

        template<typename Duration>
        [[nodiscard]] T* allocate(Duration wait_time) noexcept {
            using namespace std::chrono;

            // Define the time out in kernel ticks
            k_timeout_t timeout = wait_time.count() != 0
                ? K_MSEC(duration_cast<milliseconds>(wait_time).count())
                : K_NO_WAIT;

            // Allocate the block and cast the pointer to the explicit type
            void* ptr = nullptr;
            if (k_mem_slab_alloc(&_slab, &ptr, timeout) == 0) {
                return static_cast<T*>(ptr);
            }

            return nullptr;
        }

        void deallocate(T* ptr, std::size_t n = 1) noexcept {
            assert(n == 1);
            k_mem_slab_free(&_slab, (void**)&ptr);
        }

        std::size_t blocks_free() {
            return k_mem_slab_num_free_get(&_slab);
        }

        std::size_t blocks_used() {
            return k_mem_slab_num_used_get(&_slab);
        }
    };

    template <class T, class U>
    bool operator==(const Allocator<T>&, const Allocator<U>&) { return true; }
    template <class T, class U>
    bool operator!=(const Allocator<T>&, const Allocator<U>&) { return false; }
}