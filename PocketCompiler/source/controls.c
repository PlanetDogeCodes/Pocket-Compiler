#include "controls.h"
#include <stdio.h>
#include <string.h>

void controls_init(ControlState* c) {
    if (!c) return;
    memset(c, 0, sizeof(*c));
    c->mouse_x = BOT_W / 2;
    c->mouse_y = BOT_H / 2;
}

bool controls_mouse_over_code(const ControlState* c) {
    if (!c) return false;
    return c->mouse_x >= CODE_AREA_X &&
           c->mouse_x < CODE_AREA_X + CODE_AREA_W &&
           c->mouse_y >= CODE_AREA_Y &&
           c->mouse_y < CODE_AREA_Y + CODE_AREA_H;
}

static void push_key(DomEventQueue* q, DomEventType type, u32 key, const char* name) {
    DomEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = type;
    ev.raw_key = key;
    snprintf(ev.key, sizeof(ev.key), "%s", name);
    snprintf(ev.name, sizeof(ev.name), "%s", dom_event_type_name(type));
    dom_events_push(q, ev);
}

void controls_update(ControlState* c, DomEventQueue* events) {
    if (!c) return;
    c->prev_mouse_x = c->mouse_x;
    c->prev_mouse_y = c->mouse_y;
    hidScanInput();
    c->down = hidKeysDown();
    c->held = hidKeysHeld();
    c->up = hidKeysUp();
    hidCircleRead(&c->circle);
    hidTouchRead(&c->touch);
    int dx = c->circle.dx / 24;
    int dy = -c->circle.dy / 24;
    if (dx || dy) {
        c->mouse_x += dx;
        c->mouse_y += dy;
        if (c->mouse_x < 0) c->mouse_x = 0;
        if (c->mouse_x >= BOT_W) c->mouse_x = BOT_W - 1;
        if (c->mouse_y < 0) c->mouse_y = 0;
        if (c->mouse_y >= BOT_H) c->mouse_y = BOT_H - 1;
    }
    c->mouse_moved = c->mouse_x != c->prev_mouse_x || c->mouse_y != c->prev_mouse_y;
    c->over_code_area = controls_mouse_over_code(c);
    if (!events) return;
    if (c->down & KEY_UP) push_key(events, DOM_EVENT_KEYDOWN, KEY_UP, "ArrowUp");
    if (c->down & KEY_DOWN) push_key(events, DOM_EVENT_KEYDOWN, KEY_DOWN, "ArrowDown");
    if (c->down & KEY_LEFT) push_key(events, DOM_EVENT_KEYDOWN, KEY_LEFT, "ArrowLeft");
    if (c->down & KEY_RIGHT) push_key(events, DOM_EVENT_KEYDOWN, KEY_RIGHT, "ArrowRight");
    if (c->mouse_moved) {
        DomEvent ev; memset(&ev,0,sizeof(ev));
        ev.type = DOM_EVENT_MOUSEMOVE; ev.x = c->mouse_x; ev.y = c->mouse_y;
        snprintf(ev.name,sizeof(ev.name),"mousemove"); dom_events_push(events, ev);
    }
    if (c->down & KEY_A) {
        DomEvent ev; memset(&ev,0,sizeof(ev));
        ev.type = DOM_EVENT_CLICK; ev.x = c->mouse_x; ev.y = c->mouse_y; ev.button = 0;
        snprintf(ev.name,sizeof(ev.name),"click"); dom_events_push(events, ev);
    }
}

const char* controls_help_text(void) {
    return "DPad: arrows | Circle: mouse | A: click/edit | B: undo | X: save | Y: load | START: run | SELECT: menu";
}
