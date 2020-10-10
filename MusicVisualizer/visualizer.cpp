#pragma once
#include "visualizer.h"

#include <iostream>
#include <thread>
#include <vector>

#include "draw_utilities.h"
#include "SDL.h"
#include "amplitude_circle_layer.h"
#include "wave_layer.h"
#include "polygon_layer.h"
#include "screen_box_layer.h"
#include "moving_wave_layer.h"

const SDL_Color white{ 255, 255, 255, 255 };
const SDL_Color red{ 255, 0, 0, 255 };
const SDL_Color green{ 0, 255, 0, 255 };
const SDL_Color blue{ 0, 0, 255, 255 };

Visualizer::Visualizer(): recorder() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

	if (renderer) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
	}

	if (recorder.init_successful()) {
		recording_thread = std::thread(&AudioRecorder::record, &recorder, (AudioSink *)this, std::ref(exit_recording_thread_flag));
	}
	
	for (int i = 0; i < 10; ++i) {
		visual_layers.push_back(std::move(vl_factory.random_visual_layer(window_width, window_height)));
	}


}

Visualizer::~Visualizer()
{
	// Stop recording thread before implicitly destroying AudioRecorder
	if (recording_thread.joinable()) {
		exit_recording_thread_flag = true;
		recording_thread.join();
	}

	// Destroy SDL window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Visualizer::init_successful() const {
	return (renderer && recording_thread.joinable());
}


void Visualizer::handle_event(const SDL_Event & e) {
	//Window event occured
	if (e.type == SDL_WINDOWEVENT) {
		switch (e.window.event) {
		//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			window_width = e.window.data1;
			window_height = e.window.data2;
			SDL_RenderPresent(renderer);
			break;

		//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;

		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}

	}
	//Enter exit full screen on return key
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (mFullScreen) {
			SDL_SetWindowFullscreen(window, SDL_FALSE);
			mFullScreen = false;
		}
		else {
			SDL_SetWindowFullscreen(window, SDL_TRUE);
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void Visualizer::copy_data(float * data, int channels, int frames) {
	std::lock_guard<std::mutex>write_guard(packet_buffer_mutex);

	if (data) {
		packet_buffer = packet(data, data + channels * frames);
	}
	else {
		// use an empty vector if there is no data (silence)
		packet_buffer = packet();
	}
}


bool Visualizer::update() {
	//Handle events on queue
	while (SDL_PollEvent(&current_event) != 0) {
		if (current_event.type == SDL_QUIT) {
			return false;
		}
		handle_event(current_event);
	}

	// Do not render if minimized
	if (mMinimized) {
		return true;
	}

	// Render visualizer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	draw();
	SDL_RenderPresent(renderer);

	return true;
}

void Visualizer::draw() {
	std::unique_lock<std::mutex>read_guard(packet_buffer_mutex);
	for (auto & layer : visual_layers) {
		layer->draw(renderer, packet_buffer);
	}
}