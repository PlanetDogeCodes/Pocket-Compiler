#pragma once
#include <3ds.h>
#include <stdbool.h>

#define DOM_EVENT_QUEUE_MAX 64
#define DOM_EVENT_NAME_MAX 32

typedef enum {
    DOM_EVENT_NONE = 0,
    DOM_EVENT_KEYDOWN,
    DOM_EVENT_KEYUP,
    DOM_EVENT_MOUSEMOVE,
    DOM_EVENT_MOUSEDOWN,
    DOM_EVENT_MOUSEUP,
    DOM_EVENT_CLICK,
    DOM_EVENT_TOUCHSTART,
    DOM_EVENT_TOUCHMOVE,
    DOM_EVENT_TOUCHEND
} DomEventType;

typedef struct {
    DomEventType type;
    char name[DOM_EVENT_NAME_MAX];
    char key[DOM_EVENT_NAME_MAX];
    int x;
    int y;
    int button;
    u32 raw_key;
} DomEvent;

typedef struct {
    DomEvent events[DOM_EVENT_QUEUE_MAX];
    int count;
    int dispatched_count;
} DomEventQueue;

void dom_events_init(DomEventQueue* q);
bool dom_events_push(DomEventQueue* q, DomEvent ev);
bool dom_events_pop(DomEventQueue* q, DomEvent* out);
const char* dom_event_type_name(DomEventType type);
void dom_events_dispatch_all(DomEventQueue* q);
