#include "web_audio.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AUDIO_BUFFER_SAMPLES 4096
#define PI_F 3.14159265358979323846f

static s16* audio_buffer = NULL;

bool web_audio_init(WebAudioContext* ctx) {
    if (!ctx) return false;
    memset(ctx, 0, sizeof(*ctx));
    ctx->sample_rate = 22050.0f;
    ctx->master_gain = 0.5f;
    Result r = ndspInit();
    if (R_FAILED(r)) {
        snprintf(ctx->status, sizeof(ctx->status), "NDSP unavailable");
        ctx->ndsp_available = false;
        return false;
    }
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnReset(0);
    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, ctx->sample_rate);
    ndspChnSetFormat(0, NDSP_FORMAT_MONO_PCM16);
    audio_buffer = (s16*)linearAlloc(sizeof(s16) * AUDIO_BUFFER_SAMPLES);
    if (!audio_buffer) {
        snprintf(ctx->status, sizeof(ctx->status), "audio buffer allocation failed");
        return false;
    }
    ctx->initialized = true;
    ctx->ndsp_available = true;
    snprintf(ctx->status, sizeof(ctx->status), "WebAudio ready");
    return true;
}

void web_audio_shutdown(WebAudioContext* ctx) {
    if (audio_buffer) {
        linearFree(audio_buffer);
        audio_buffer = NULL;
    }
    if (ctx && ctx->initialized) {
        ndspExit();
        ctx->initialized = false;
    }
}

void web_audio_tick(WebAudioContext* ctx, float dt) { if (ctx) ctx->current_time += dt; }

WebAudioNode* web_audio_create_oscillator(WebAudioContext* ctx) {
    if (!ctx) return NULL;
    ctx->oscillator.type = AUDIO_NODE_OSCILLATOR;
    ctx->oscillator.oscillator_type = OSC_SINE;
    ctx->oscillator.frequency = 440.0f;
    ctx->oscillator.gain = 1.0f;
    return &ctx->oscillator;
}

WebAudioNode* web_audio_create_gain(WebAudioContext* ctx) {
    if (!ctx) return NULL;
    ctx->gain.type = AUDIO_NODE_GAIN;
    ctx->gain.gain = 1.0f;
    return &ctx->gain;
}

void web_audio_oscillator_set_type(WebAudioNode* node, OscillatorType type) { if (node) node->oscillator_type = type; }
void web_audio_oscillator_set_frequency(WebAudioNode* node, float frequency) { if (node) node->frequency = frequency; }
void web_audio_gain_set_value(WebAudioNode* node, float gain) { if (node) node->gain = gain; }

static float sample_wave(OscillatorType type, float phase) {
    switch (type) {
        case OSC_SQUARE: return phase < 0.5f ? 1.0f : -1.0f;
        case OSC_TRIANGLE: return phase < 0.5f ? (phase * 4.0f - 1.0f) : (3.0f - phase * 4.0f);
        case OSC_SAWTOOTH: return phase * 2.0f - 1.0f;
        case OSC_SINE:
        default: return sinf(phase * 2.0f * PI_F);
    }
}

bool web_audio_start(WebAudioContext* ctx, WebAudioNode* osc) {
    if (!ctx || !osc || !ctx->initialized || !audio_buffer) return false;
    float gain = ctx->master_gain * osc->gain;
    if (ctx->gain.type == AUDIO_NODE_GAIN) gain *= ctx->gain.gain;
    int count = AUDIO_BUFFER_SAMPLES;
    for (int i = 0; i < count; i++) {
        float t = (float)i / ctx->sample_rate;
        float phase = fmodf(t * osc->frequency, 1.0f);
        audio_buffer[i] = (s16)(sample_wave(osc->oscillator_type, phase) * 24000.0f * gain);
    }
    DSP_FlushDataCache(audio_buffer, sizeof(s16) * count);
    ndspWaveBuf wave;
    memset(&wave, 0, sizeof(wave));
    wave.data_vaddr = audio_buffer;
    wave.nsamples = count;
    wave.looping = false;
    ndspChnWaveBufClear(0);
    ndspChnWaveBufAdd(0, &wave);
    osc->started = true;
    snprintf(ctx->status, sizeof(ctx->status), "oscillator %.1fHz", osc->frequency);
    return true;
}

void web_audio_stop(WebAudioContext* ctx, WebAudioNode* osc) {
    if (ctx && ctx->initialized) ndspChnWaveBufClear(0);
    if (osc) osc->started = false;
}

bool web_audio_beep(WebAudioContext* ctx) {
    WebAudioNode* osc = web_audio_create_oscillator(ctx);
    if (!osc) return false;
    web_audio_oscillator_set_frequency(osc, 880.0f);
    return web_audio_start(ctx, osc);
}
