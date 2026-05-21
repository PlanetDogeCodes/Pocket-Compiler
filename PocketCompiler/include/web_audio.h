#pragma once
#include <3ds.h>
#include <stdbool.h>

typedef enum {
    AUDIO_NODE_NONE = 0,
    AUDIO_NODE_OSCILLATOR,
    AUDIO_NODE_GAIN
} AudioNodeType;

typedef enum {
    OSC_SINE = 0,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAWTOOTH
} OscillatorType;

typedef struct {
    AudioNodeType type;
    OscillatorType oscillator_type;
    float frequency;
    float gain;
    bool started;
} WebAudioNode;

typedef struct {
    bool initialized;
    bool ndsp_available;
    float current_time;
    float sample_rate;
    float master_gain;
    WebAudioNode oscillator;
    WebAudioNode gain;
    char status[128];
} WebAudioContext;

bool web_audio_init(WebAudioContext* ctx);
void web_audio_shutdown(WebAudioContext* ctx);
void web_audio_tick(WebAudioContext* ctx, float dt);
WebAudioNode* web_audio_create_oscillator(WebAudioContext* ctx);
WebAudioNode* web_audio_create_gain(WebAudioContext* ctx);
void web_audio_oscillator_set_type(WebAudioNode* node, OscillatorType type);
void web_audio_oscillator_set_frequency(WebAudioNode* node, float frequency);
void web_audio_gain_set_value(WebAudioNode* node, float gain);
bool web_audio_start(WebAudioContext* ctx, WebAudioNode* oscillator);
void web_audio_stop(WebAudioContext* ctx, WebAudioNode* oscillator);
bool web_audio_beep(WebAudioContext* ctx);
