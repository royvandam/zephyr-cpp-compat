#pragma once

#include <zephyr.h>
#include <chrono>

namespace std::this_thread {
    template<class Rep, class Period>
    void sleep_for(const std::chrono::duration<Rep, Period>& sleep_duration) {
        using namespace std::chrono;
        k_sleep(K_NSEC(duration_cast<nanoseconds>(sleep_duration).count()));
    }

    template<class Clock, class Duration>
    void sleep_until(const std::chrono::time_point<Clock,Duration>& sleep_time) {
        using namespace std::chrono;
        auto now = Clock::now();
        if (now >= sleep_time) { return; }
        auto sleep_duration = sleep_time - now;
        k_sleep(K_NSEC(duration_cast<nanoseconds>(sleep_duration).count()));
    }
}