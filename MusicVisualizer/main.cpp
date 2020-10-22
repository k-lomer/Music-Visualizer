#include <chrono>
#include <thread>

#include "visualizer.h"

typedef std::chrono::milliseconds ms;
constexpr int fps = 60;
constexpr ms frame_duration(1000 / fps);

int main(int argc, char* argv[])
{
    Visualizer generator;
    bool continue_app = generator.init_successful();

    while (continue_app)
    {
        auto t0 = std::chrono::steady_clock::now();
        continue_app = generator.update();
        auto t1 = std::chrono::steady_clock::now();

        ms update_duration(std::chrono::duration_cast<ms>(t1 - t0).count());
        if (update_duration < frame_duration) {
            std::this_thread::sleep_for(frame_duration - update_duration);
        }
    }

    return 0;
}
