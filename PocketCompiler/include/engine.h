#pragma once
#include "app.h"
#include "dom_events.h"
#include "web_audio.h"

typedef struct {
    char title[128];
    char render_text[PREVIEW_TEXT_MAX];
    int compile_count;
    int dom_event_count;
    int audio_context_count;
    WebAudioContext audio;
} EngineDoc;

typedef struct {
    int errors;
    char message[512];
} HtmlCheck;

void engine_init(EngineDoc* doc);
void engine_shutdown(EngineDoc* doc);
void engine_compile(const char* html, EngineDoc* out);
HtmlCheck engine_check(const char* html);
void engine_dispatch_dom_events(EngineDoc* doc, DomEventQueue* events);
void engine_tick(EngineDoc* doc);
