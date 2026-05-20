#include "engine.h"
#include <stdio.h>
#include <string.h>

void engine_init(EngineDoc* doc) {
    if (!doc) return;
    memset(doc, 0, sizeof(*doc));
    web_audio_init(&doc->audio);
}

void engine_shutdown(EngineDoc* doc) {
    if (!doc) return;
    web_audio_shutdown(&doc->audio);
}

void engine_compile(const char* html, EngineDoc* out) {
    if (!out) return;

    snprintf(out->title, sizeof(out->title), "Pocket Compiler v0.23 Phase 11");
    snprintf(out->render_text, sizeof(out->render_text), "%s", html ? html : "");

    out->compile_count++;
    out->dom_event_count = 0;

    if (html && (strstr(html, "AudioContext") || strstr(html, "new Audio") || strstr(html, "<audio"))) {
        out->audio_context_count = 1;
        web_audio_beep(&out->audio);
    }
}

HtmlCheck engine_check(const char* html) {
    (void)html;
    HtmlCheck c;
    c.errors = 0;
    snprintf(c.message, sizeof(c.message), "OK");
    return c;
}

void engine_dispatch_dom_events(EngineDoc* doc, DomEventQueue* events) {
    if (!doc || !events) return;
    doc->dom_event_count += events->count;
    dom_events_dispatch_all(events);
}

void engine_tick(EngineDoc* doc) {
    if (!doc) return;
    web_audio_tick(&doc->audio, 1.0f / 60.0f);
}
