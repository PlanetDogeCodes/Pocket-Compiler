#include <3ds.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "app.h"
#include "editor.h"
#include "engine.h"
#include "fs_io.h"
#include "controls.h"
#include "file_explorer.h"
#include "ui.h"

static const char* sample =
"<!doctype html>\n"
"<html><head><title>Pocket Compiler v0.24</title></head><body>\n"
"<h1>Debug Fixed Controls + Web Audio</h1>\n"
"<script>\n"
"var audio = new AudioContext();\n"
"document.addEventListener('click', function(){ console.log('click'); });\n"
"</script>\n"
"</body></html>";

static Editor ed;
static EngineDoc doc;
static DomEventQueue events;
static ControlState controls;
static FileExplorer files;

void app_status(AppState* app, const char* fmt, ...) {
    if (!app) return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(app->status, sizeof(app->status), fmt, ap);
    va_end(ap);
}

static void run_compile(AppState* app) {
    engine_compile(editor_text(&ed), &doc);
    app_status(app, "Compiled.");
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    gfxInitDefault();
    AppState app;
    memset(&app, 0, sizeof(app));
    app.running = true;
    editor_init(&ed);
    editor_set(&ed, sample);
    dom_events_init(&events);
    controls_init(&controls);
    file_explorer_init(&files);
    fs_make_app_dirs();
    engine_init(&doc);
    ui_init();
    run_compile(&app);
    while (aptMainLoop() && app.running) {
        controls_update(&controls, &events);
        if (controls.down & KEY_START) run_compile(&app);
        if (controls.down & KEY_SELECT) app.show_controls = !app.show_controls;
        if (controls.down & KEY_B) {
            if (editor_undo(&ed)) app_status(&app, "Undo.");
            else app_status(&app, "Nothing to undo.");
        }
        if (controls.down & KEY_X) {
            app.show_file_overlay = true;
            file_explorer_save_dialog(&files, &ed, &app);
            app.show_file_overlay = false;
        }
        if (controls.down & KEY_Y) {
            app.show_file_overlay = true;
            file_explorer_load_dialog(&files, &ed, &app);
            app.show_file_overlay = false;
        }
        if (controls.down & KEY_UP) editor_move_up(&ed);
        if (controls.down & KEY_DOWN) editor_move_down(&ed);
        if (controls.down & KEY_LEFT) editor_move_left(&ed);
        if (controls.down & KEY_RIGHT) editor_move_right(&ed);
        if (controls.down & KEY_A) {
            if (controls_mouse_over_code(&controls)) {
                int line = editor_line_from_y(&ed, controls.mouse_y);
                if (line >= 0) {
                    ui_keyboard_line(&ed, line, &app);
                    app.dirty = true;
                }
            } else {
                app_status(&app, "Mouse click.");
            }
        }
        engine_dispatch_dom_events(&doc, &events);
        engine_tick(&doc);
        ui_draw_top(&app, &doc);
        ui_draw_bottom(&app, &ed, &controls, &files);
    }
    engine_shutdown(&doc);
    ui_shutdown();
    gfxExit();
    return 0;
}
