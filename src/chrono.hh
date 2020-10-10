#pragma once

#include <zephyr.h>
#include <chrono>

namespace std::chrono::zephyr {
    class steady_clock {
    public:
        typedef uint64_t rep;
        typedef std::micro period;
        typedef std::chrono::duration<rep, period> duration;
        typedef std::chrono::time_point<steady_clock> time_point;

        static constexpr bool is_steady = true;

        static time_point now() noexcept {
            static time_point _epoch;
            return _epoch + duration(k_ticks_to_us_near64(k_uptime_ticks()));
        };

    private:
        steady_clock() = delete;
        ~steady_clock() = delete;
        steady_clock(steady_clock const &) = delete;
    };
}
