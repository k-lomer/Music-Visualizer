#pragma once

#include <atomic>

#include <Audioclient.h>
#include <Audiopolicy.h>
#include <Mmdeviceapi.h>

#include "audio_sink.h"

// Class for recording system audio via WASAPI Loopback.
class AudioRecorder {
public:
    // AudioRecorder constructor.
    AudioRecorder();
    // Don't allow construction by copy. Bad things can happen with pointer member variables.
    AudioRecorder(const AudioRecorder&) = delete;
    // AudioRecorder destructor.
    ~AudioRecorder();
    // Don't allow assignment. Bad things can happen with pointer member variables.
    AudioRecorder& operator=(AudioRecorder const&) = delete;
    // Don't allow assignment. Bad things can happen with pointer member variables.
    AudioRecorder& operator=(AudioRecorder&&) = delete;

    // The status of the initialization process.
    // return: bool             - whether the initialization was successful
    bool init_successful() const;

    // Reset the AudioRecorder.
    void reset();

    // Record audio data from the system indefinitely.
    // param: audio_sink        - class which copies the recorded packets
    // param: exit_flag         - flag to stop recording (passed by ref so it can be stopped externally)
    void record(AudioSink* audio_sink, std::atomic_bool& exit_flag) const;

    // Getter for the number of channels.
    // return: unsigned int     - the number of audio channels
    unsigned int get_num_channels() const { return m_num_channels; }

    // Getter for the sample rate.
     // return: unsigned int     - the sample rate
    unsigned long get_sample_rate() const { return m_sample_rate; }

private:
    // Initialize the AudioRecorder member variables.
    void init();

    // Terminate the AudioRecorder member variables.
    void terminate();

    // The result flag for audio operations.
    mutable HRESULT m_hr;
    // The audio device enumerator.
    IMMDeviceEnumerator* m_device_enumerator = nullptr;
    // The audio device endpoint.
    IMMDevice* m_audio_device_endpoint = nullptr;
    // The audio client.
    IAudioClient* m_audio_client = nullptr;
    // The audio capture client.
    IAudioCaptureClient* m_capture_client = nullptr;
    // The number of audio channels.
    unsigned int m_num_channels;
    // The sample rate.
    unsigned long m_sample_rate;

    // The time spent sleeping to wait for new packets.
    static const int s_sleep_time = 10;
};
