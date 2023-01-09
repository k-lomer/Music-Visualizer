#pragma once

#include <chrono>

// CountdownTimer class to measure when a given time interval has passed.
// template param: TimeT - the chrono unit for time duration
template <class TimeT=std::chrono::seconds>
class CountdownTimer {
public:
    // CountdownTimer constructor.
    // Note that the countdown will begin on initialization.
    // param: duration - the time that the countdown will last
    CountdownTimer(TimeT duration) :
    m_start_time(std::chrono::high_resolution_clock::now()),
    m_countdown_duration(duration) {}

    // Whether the given duration has passed since the timer started.
    bool expired() {
    auto now = std::chrono::high_resolution_clock::now();
    return now - m_start_time > m_countdown_duration;
    }

    // Reset the timer with the same duration.
    void reset() {
        m_start_time = std::chrono::high_resolution_clock::now();
    }

    // Reset the timer with a new duration.
    // param: duation - the new time interval to measure
    void reset(TimeT duration) {
        m_countdown_duration = duration;
        m_start_time = std::chrono::high_resolution_clock::now();
    }


private:
    // The time at which the timer started.
    std::chrono::steady_clock::time_point m_start_time;
    // The duration of the countdown timer in the templated time unit.
    TimeT m_countdown_duration;
};
