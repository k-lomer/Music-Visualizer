#pragma once
#include <atomic>
#include <mutex>
#include <vector>
#include <thread>

#include "audio_recorder.h"
#include "audio_sink.h"
#include "color_palettes.h"
#include "SDL.h"
#include "timer.h"
#include "visual_layer.h"
#include "visual_layer_factory.h"

// Visualizer class
// This class owns the SDL window and performs visual updates based on system audio
class Visualizer: public AudioSink {
public:

    Visualizer();
    ~Visualizer();

    // The status of the initialization process
    // return: bool - whether the initialization was successful
    bool init_successful() const;

    // Update the visuals based on the most recent packet
    // return: bool - whether the update was successful
    bool update();

    // Copy a packet of data from the audio recorder
    // Must override the method from AudioSink
    // param: data - pointer to data values
    // param: channels - the number of audio channels
    // param: frames - the number of frames of data
    void copy_data(float * data, int channels, int frames) override;

private:
    // Window members
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event current_event;
    int window_width = 1000;
    int window_height = 600;
    bool mFullScreen = false;
    bool mMinimized = false;

    // Audio recording members
    AudioRecorder recorder;
    std::thread recording_thread;
    std::atomic_bool exit_recording_thread_flag = false;
    std::mutex packet_buffer_mutex;
    typedef std::vector<float> packet;
    packet packet_buffer; // Must use mutex to access

    // Visual Layer members
    VisualLayerFactory vl_factory;
    std::vector<std::unique_ptr<VisualLayer>> visual_layers;
    CountdownTimer<std::chrono::seconds> layer_change_timer;
    static const std::chrono::seconds change_time;
    static const int num_layers_init;
    Color::color_palette palette = Color::Vaporwave;

    // Debug FPS
    bool debug_print_fps = true;
    CountdownTimer<std::chrono::seconds> fps_timer;
    int frames = 0;

    // Handle SDL window events
    // param: e - the SDL window event to handle
    void handle_event(const SDL_Event & e);

    // Add a visual layer to the visualizer
    void add_visual_layer();

    // Remove a visual layer from the visualizer
    void remove_visual_layer();

    // Change the oldest of the visual layers
    void change_visual_layer();

    // Change all of the visual layers
    void change_all_layers();

    // Change the color palette
    void change_color();

    // Draw the visual layers on the screen;
    void draw();

};
