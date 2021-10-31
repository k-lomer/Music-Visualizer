#pragma once

#include <atomic>

#include <Audioclient.h>
#include <Audiopolicy.h>
#include <Mmdeviceapi.h>

#include "audio_sink.h"

// Class for recording system audio via WASAPI Loopback
class AudioRecorder {
public:
    AudioRecorder();
    ~AudioRecorder();

    // The status of the initialization process
    // return: bool - whether the initialization was successful
    bool init_successful() const;

    // Record audio data from the system indefinitely
    // param: audio_sink - class which copies the recorded packets
    // param: exit_flag - flag to stop recording (passed by ref so it can be stopped externally)
    void record(AudioSink * audio_sink, std::atomic_bool &exit_flag) const;

    // Getter for the number of channels
    unsigned int get_num_channels() const { return m_num_channels; }

    // Getter for the sample rate
    unsigned long get_sample_rate() const { return m_sample_rate; }

private:
    mutable HRESULT m_hr;
    IMMDeviceEnumerator * m_device_enumerator = nullptr;
    IMMDevice * m_audio_device_endpoint = nullptr;
    IAudioClient * m_audio_client = nullptr;
    IAudioCaptureClient *m_capture_client = nullptr;
    unsigned int m_num_channels;
    unsigned long m_sample_rate;

    static const int s_sleep_time = 10; // Time spent sleeping to wait for new packets
};
