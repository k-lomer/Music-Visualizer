#pragma once

#include <chrono>

// CountdownTimer class to measure when a given time interval has passed
// template param: TimeT - the chrono unit for time duration
template <class TimeT=std::chrono::seconds>
class CountdownTimer {
public:
    // Constructor for the countdown timer
    // Note that the countdown will begin on initialization
    // param: duration - the time that the countdown will last
    CountdownTimer(TimeT duration) :
    start_time(std::chrono::high_resolution_clock::now()),
    countdown_duration(duration) {}

    // Whether the given duration has passed since the timer started
    bool expired() {
    auto now = std::chrono::high_resolution_clock::now();
    return now - start_time > countdown_duration;
    }

    // Reset the timer with the same duration
    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Reset the timer with a new duration
    // param: duation - the new time interval to measure
    void reset(TimeT duration) {
        countdown_duration = duration;
        start_time = std::chrono::high_resolution_clock::now();
    }


private:
    std::chrono::steady_clock::time_point start_time;
    TimeT countdown_duration;
};
