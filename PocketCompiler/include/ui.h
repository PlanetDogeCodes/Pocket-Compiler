#pragma once
#include "app.h"
#include "editor.h"
#include "engine.h"
#include "controls.h"
#include "file_explorer.h"

void ui_init(void);
void ui_shutdown(void);
void ui_draw_top(const AppState* app, const EngineDoc* doc);
void ui_draw_bottom(const AppState* app, const Editor* e, const ControlState* controls, const FileExplorer* fx);
bool ui_keyboard_line(Editor* e, int line, AppState* app);
