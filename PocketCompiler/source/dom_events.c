#include "dom_events.h"
#include <stdio.h>
#include <string.h>

void dom_events_init(DomEventQueue* q) { if (q) memset(q, 0, sizeof(*q)); }

bool dom_events_push(DomEventQueue* q, DomEvent ev) {
    if (!q || q->count >= DOM_EVENT_QUEUE_MAX) return false;
    q->events[q->count++] = ev;
    return true;
}

bool dom_events_pop(DomEventQueue* q, DomEvent* out) {
    if (!q || !out || q->count <= 0) return false;
    *out = q->events[0];
    memmove(&q->events[0], &q->events[1], sizeof(DomEvent) * (DOM_EVENT_QUEUE_MAX - 1));
    q->count--;
    return true;
}

const char* dom_event_type_name(DomEventType type) {
    switch (type) {
        case DOM_EVENT_KEYDOWN: return "keydown";
        case DOM_EVENT_KEYUP: return "keyup";
        case DOM_EVENT_MOUSEMOVE: return "mousemove";
        case DOM_EVENT_MOUSEDOWN: return "mousedown";
        case DOM_EVENT_MOUSEUP: return "mouseup";
        case DOM_EVENT_CLICK: return "click";
        case DOM_EVENT_TOUCHSTART: return "touchstart";
        case DOM_EVENT_TOUCHMOVE: return "touchmove";
        case DOM_EVENT_TOUCHEND: return "touchend";
        default: return "none";
    }
}

void dom_events_dispatch_all(DomEventQueue* q) {
    if (!q) return;
    q->dispatched_count += q->count;
    q->count = 0;
}
