#pragma once
#include "visualizer.h"

#include <iostream>
#include <thread>
#include <vector>

#include "SDL.h"

const std::chrono::seconds Visualizer::s_change_time(10);
const int Visualizer::s_num_layers_init = 1;

Visualizer::Visualizer():
    m_recorder(),
    m_layer_change_timer(s_change_time),
    m_fps_timer(std::chrono::seconds(1)),
    m_signal_box(m_recorder.get_num_channels(), m_recorder.get_sample_rate()),
    m_debug_print_signal_cfg(false),
    m_debug_print_fps(false) {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize the SDL window and renderer.
    m_window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_window_width, m_window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window) {
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
    if (m_renderer) {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
    }

    // Check the audio recorder initialization.
    if (m_recorder.init_successful()) {
        m_recording_thread = std::thread(&AudioRecorder::record, &m_recorder, (AudioSink *)this, std::ref(m_exit_recording_thread_flag));
    }

    // Add visual layers.
    for (int i = 0; i < s_num_layers_init; ++i) {
        add_visual_layer();
    }

    // Configure the signal box.
    m_signal_box.reset(m_signal_box_cfg);
    if (m_debug_print_signal_cfg) {
        std::cout << m_signal_box_cfg << std::endl;
    }
}

Visualizer::~Visualizer()
{
    // Stop recording thread before implicitly destroying AudioRecorder.
    if (m_recording_thread.joinable()) {
        m_exit_recording_thread_flag = true;
        m_recording_thread.join();
    }

    // Destroy SDL window and renderer.
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Visualizer::init_successful() const {
    return (m_renderer && m_recording_thread.joinable());
}

void Visualizer::add_visual_layer() {
    m_visual_layers.push_back(std::move(m_visual_layer_factory.random_visual_layer(m_window_width, m_window_height, m_signal_box_cfg, m_palette)));
}

void Visualizer::remove_visual_layer() {
    if (!m_visual_layers.empty()) {
        m_visual_layers.pop_front();
    }
}

void Visualizer::change_visual_layer() {
    // Remove the layer at the front and add a new one at the back.
    if (!m_visual_layers.empty()) {
        remove_visual_layer();
        add_visual_layer();
    }
}

void Visualizer::change_all_layers() {
    size_t num_layers = m_visual_layers.size();
    for (size_t i = 0; i < num_layers; ++i) {
        change_visual_layer();
    }
    m_signal_box.reset(m_signal_box_cfg);
    if (m_debug_print_signal_cfg) {
        std::cout << m_signal_box_cfg << std::endl;
    }
    m_layer_change_timer.reset();
}

void Visualizer::change_color() {
    m_palette = color::ColorPalette((m_palette + 1) % (color::MAX_CP + 1));
    change_all_layers();
}

void Visualizer::handle_event(const SDL_Event & e) {
    // Window event occured.
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
        // Get new dimensions and repaint on window size change.
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            m_window_width = e.window.data1;
            m_window_height = e.window.data2;
            change_all_layers();
            SDL_RenderPresent(m_renderer);
            break;

        // Redraw on exposure.
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(m_renderer);
            break;

        case SDL_WINDOWEVENT_MINIMIZED:
            m_minimized = true;
            break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            m_minimized = false;
            break;

        case SDL_WINDOWEVENT_RESTORED:
            m_minimized = false;
            break;
        }

    }
    // Keyboard event occurred.
    else if (e.type == SDL_KEYDOWN){
        // Enter exit full screen on return key.
        if (e.key.keysym.sym == SDLK_RETURN) {
            if (m_full_screen) {
                SDL_SetWindowFullscreen(m_window, SDL_FALSE);
                m_full_screen = false;
            }
            else {
                SDL_SetWindowFullscreen(m_window, SDL_TRUE);
                m_full_screen = true;
                m_minimized = false;
            }
        }
        // Change all visuals on space key.
        else if (e.key.keysym.sym == SDLK_SPACE) {
            change_all_layers();
        }
        // Change one visual layer on left or right key.
        else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
            change_visual_layer();
        }
        // Change color on 'c' key.
        else if (e.key.keysym.sym == SDLK_c) {
            change_color();
        }
        // Add another visual layer on up key.
        else if (e.key.keysym.sym == SDLK_UP) {
            add_visual_layer();
        }
        // Remove a visual layer on down key.
        else if (e.key.keysym.sym == SDLK_DOWN) {
                remove_visual_layer();
        }
    }
}

void Visualizer::copy_data(float * data, int channels, int frames) {
    if (data) {
         std::shared_ptr<packet> packet_ptr = std::make_shared<packet>(data, data + channels * frames);
         std::lock_guard<std::mutex>write_guard(m_packet_buffer_mutex);
         m_packet_buffer.push_back(packet_ptr);
    }
    else {
        // use an empty vector if there is no data (silence).
        std::shared_ptr<packet> packet_ptr = std::make_shared<packet>();
        std::lock_guard<std::mutex>write_guard(m_packet_buffer_mutex);
        m_packet_buffer.push_back(packet_ptr);
    }
}

bool Visualizer::update() {
    // Handle events on queue.
    while (SDL_PollEvent(&m_current_event) != 0) {
        if (m_current_event.type == SDL_QUIT) {
            return false;
        }
        handle_event(m_current_event);
    }

    // Change layers if timer has expired.
    if (m_layer_change_timer.expired()) {
        change_all_layers();
        m_layer_change_timer.reset();
    }

    // Do not render if minimized.
    if (m_minimized) {
        return true;
    }

    // Render the visualizer.
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    draw();
    SDL_RenderPresent(m_renderer);

    // Process FPS.
    if (m_debug_print_fps) {
        m_fps_frames_counter += 1;
        if (m_fps_timer.expired()) {
            std::cout << "FPS: " << m_fps_frames_counter << std::endl;
            m_fps_frames_counter = 0;
            m_fps_timer.reset();
        }
    }

    return true;
}

void Visualizer::draw() {
    std::unique_lock<std::mutex>read_write_guard(m_packet_buffer_mutex);
    std::vector<std::shared_ptr<packet>> packet_buffer_copy(m_packet_buffer);
    m_packet_buffer.clear();
    read_write_guard.unlock();

    m_signal_box.update_signal(packet_buffer_copy);

    for (auto & layer : m_visual_layers) {
        layer->draw(m_renderer, m_signal_box.get_wave());
    }
}
