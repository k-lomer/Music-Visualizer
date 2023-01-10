#pragma once
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

#include "audio_recorder.h"
#include "audio_sink.h"
#include "../Utilities/color_palettes.h"
#include "SDL.h"
#include "signal_box.h"
#include "../Utilities/timer.h"
#include "visual_layer.h"
#include "visual_layer_factory.h"

// Visualizer class.
// This class owns the SDL window and performs visual updates based on system audio.
class Visualizer: public AudioSink {
public:
    // Visualizer constructor.
    Visualizer();
    // Visualizer destructor.
    ~Visualizer();

    // The status of the initialization process.
    // return: bool - whether the initialization was successful
    bool init_successful() const;

    // Update the visuals based on the most recent packet.
    // return: bool - whether the update was successful
    bool update();

    // Copy a packet of data from the audio recorder.
    // param: data - pointer to data values
    // param: channels - the number of audio channels
    // param: frames - the number of frames of data
    void copy_data(float * data, int channels, int frames) override;

private:
    // Applicationi window members.
    //
    // The SDL window.
    SDL_Window* m_window = nullptr;
    // The SDL renderer.
    SDL_Renderer* m_renderer = nullptr;
    // The current SDL event.
    SDL_Event m_current_event;
    // The SDL window width.
    int m_window_width = 1000;
    // The SDL window height.
    int m_window_height = 600;
    // Whether the visualizer application is in full screen mode.
    bool m_full_screen = false;
    // Whether the visualizer application is minimized.
    bool m_minimized = false;


    // Audio recording members.
    //
    // The audio recorder.
    AudioRecorder m_recorder;
    // The thread performing audio recording.
    std::thread m_recording_thread;
    // The flag to signal to the audi recording thread to exit.
    std::atomic_bool m_exit_recording_thread_flag = false;
    // The mutex for accessing the packet buffer.
    std::mutex m_packet_buffer_mutex;
    // The type of audio data packets.
    typedef std::vector<float> packet;
    // The buffer for storing audio data packets, must use a mutex to access this as it is used by multiple threads.
    std::vector<std::shared_ptr<packet>> m_packet_buffer;
    // The signal box for signal processing.
    SignalBox m_signal_box;
    // The config for the signal box.
    SignalBoxConfig m_signal_box_cfg;
    // Whether to debug print the signal config.
    bool m_debug_print_signal_cfg;


    // Visual layer members.
    //
    // The visual layer factory, for generating visual layers.
    VisualLayerFactory m_visual_layer_factory;
    // The current visual layers to display.
    std::deque<std::unique_ptr<VisualLayer>> m_visual_layers;
    // The initial color palette to use for visual layers.
    color::ColorPalette m_palette = color::ColorPalette::Mars;
    // The timer responsible for changing the visual layers.
    CountdownTimer<std::chrono::seconds> m_layer_change_timer;
    // The time to display a visual layer for.
    static const std::chrono::seconds s_change_time;
    // The number of visual layers to initialize.
    static const size_t s_num_layers_init;
    // The maximum number of visual layers allowed.
    static const size_t s_max_layers;


    // Debug FPS members.
    //
    // Whether to debug print the FPS.
    bool m_debug_print_fps;
    // The timer for calculating the FPS (1 second duration).
    CountdownTimer<std::chrono::seconds> m_fps_timer;
    // The number of frames counted.
    int m_fps_frames_counter = 0;


    // Handle SDL window events.
    // param: e - the SDL window event to handle
    void handle_event(const SDL_Event & e);

    // Add a visual layer to the visualizer.
    void add_visual_layer();

    // Remove a visual layer from the visualizer.
    void remove_visual_layer();

    // Change the oldest of the visual layers.
    void change_visual_layer();

    // Change all of the visual layers.
    void change_all_layers();

    // Change the color palette.
    void change_color();

    // Draw the visual layers on the screen.
    void draw();
};
