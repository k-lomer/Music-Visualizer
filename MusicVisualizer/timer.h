#pragma once

#include <chrono>

template <class TimeT=std::chrono::seconds>
class CountdownTimer {
public:
	CountdownTimer(TimeT duration) :
	start_time(std::chrono::high_resolution_clock::now()),
	countdown_duration(duration) {}

	bool expired() {
	auto now = std::chrono::high_resolution_clock::now();
	return now - start_time > countdown_duration;
	}

	void reset() {
		start_time = std::chrono::high_resolution_clock::now();
	}

private:
	std::chrono::steady_clock::time_point start_time;
	TimeT countdown_duration;
};
