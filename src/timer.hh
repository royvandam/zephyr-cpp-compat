#pragma once

#include <zephyr.h>

class Timer {
protected:
    struct k_timer _timer;

public:
    Timer() {
        k_timer_init(&_timer, nullptr, nullptr);
    }

    ~Timer() {
        k_timer_stop(&_timer);
    }

    template<class Duration>
    void start(Duration interval) {
        using namespace std::chrono;
        k_timer_start(&_timer,
            K_USEC(duration_cast<microseconds>(interval).count()),
            K_USEC(duration_cast<microseconds>(interval).count()));
    }

    void stop() {
        k_timer_stop(&_timer);
    }

    void wait() {
        k_timer_status_sync(&_timer);
    }
};