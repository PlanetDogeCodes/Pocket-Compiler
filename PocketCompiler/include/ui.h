#pragma once
#include "app.h"
#include "editor.h"
#include "engine.h"

void ui_init(void);
void ui_shutdown(void);
void ui_draw_top(const AppState* app, const EngineDoc* doc);
void ui_draw_bottom(const AppState* app, const Editor* e);
bool ui_keyboard(Editor* e, AppState* app);
