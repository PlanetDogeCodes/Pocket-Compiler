#pragma once
#include "app.h"
#include "dom_events.h"
#include <3ds.h>
#include <stdbool.h>

typedef struct {
    int mouse_x;
    int mouse_y;
    int prev_mouse_x;
    int prev_mouse_y;
    bool mouse_moved;
    u32 down;
    u32 held;
    u32 up;
    circlePosition circle;
    touchPosition touch;
    bool over_code_area;
} ControlState;

void controls_init(ControlState* c);
void controls_update(ControlState* c, DomEventQueue* events);
bool controls_mouse_over_code(const ControlState* c);
const char* controls_help_text(void);
