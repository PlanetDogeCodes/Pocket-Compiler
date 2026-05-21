#include "ui.h"
#include <citro2d.h>
#include <citro3d.h>
#include <stdio.h>
#include <string.h>

static C3D_RenderTarget* top_target;
static C3D_RenderTarget* bottom_target;
static C2D_TextBuf tb;
static u32 BG, CY, W, G, Y, DG;

static void draw_text(float x, float y, float s, u32 c, const char* t) {
    if (!t || !*t) return;
    C2D_Text tx;
    C2D_TextParse(&tx, tb, t);
    C2D_TextOptimize(&tx);
    C2D_DrawText(&tx, C2D_WithColor, x, y, 0, s, s, c);
}

static void outline(float x, float y, float w, float h, u32 c) {
    C2D_DrawRectSolid(x, y, 0, w, 1, c);
    C2D_DrawRectSolid(x, y + h - 1, 0, w, 1, c);
    C2D_DrawRectSolid(x, y, 0, 1, h, c);
    C2D_DrawRectSolid(x + w - 1, y, 0, 1, h, c);
}

void ui_init(void) {
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    top_target = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom_target = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    tb = C2D_TextBufNew(8192);
    BG = C2D_Color32(0,0,0,255);
    CY = C2D_Color32(125,211,252,255);
    W = C2D_Color32(255,255,255,255);
    G = C2D_Color32(150,150,150,255);
    Y = C2D_Color32(253,224,71,255);
    DG = C2D_Color32(50,50,60,255);
}

void ui_shutdown(void) {
    if (tb) C2D_TextBufDelete(tb);
    C2D_Fini();
    C3D_Fini();
}

bool ui_keyboard_line(Editor* e, int line, AppState* app) {
    if (!e || line < 0) return false;
    char current[512];
    editor_get_line(e, line, current, sizeof(current));
    SwkbdState kbd;
    char input[512];
    snprintf(input, sizeof(input), "%s", current);
    swkbdInit(&kbd, SWKBD_TYPE_NORMAL, 2, sizeof(input)-1);
    swkbdSetInitialText(&kbd, input);
    swkbdSetHintText(&kbd, "Edit clicked line");
    swkbdSetButton(&kbd, SWKBD_BUTTON_LEFT, "Cancel", false);
    swkbdSetButton(&kbd, SWKBD_BUTTON_RIGHT, "Apply", true);
    if (swkbdInputText(&kbd, input, sizeof(input)) == SWKBD_BUTTON_RIGHT) {
        if (editor_replace_line(e, line, input)) {
            if (app) app_status(app, "Edited line %d.", line + 1);
            return true;
        }
    }
    return false;
}

void ui_draw_top(const AppState* app, const EngineDoc* doc) {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TextBufClear(tb);
    C2D_TargetClear(top_target, BG);
    C2D_SceneBegin(top_target);
    C2D_DrawRectSolid(0,0,0,400,240,BG);
    outline(4,4,392,232,W);
    draw_text(10, 8, .45f, CY, "Pocket Compiler v0.24");
    if (doc) {
        draw_text(10, 30, .34f, W, doc->title);
        char m[192];
        snprintf(m, sizeof(m), "compiled:%d domEvents:%d audio:%d", doc->compile_count, doc->dom_event_count, doc->audio_context_count);
        draw_text(10, 60, .32f, Y, m);
        draw_text(10, 84, .28f, G, doc->audio.status);
    }
    if (app) draw_text(10, 218, .28f, W, app->status);
}

void ui_draw_bottom(const AppState* app, const Editor* e, const ControlState* controls, const FileExplorer* fx) {
    C2D_TargetClear(bottom_target, BG);
    C2D_SceneBegin(bottom_target);
    C2D_DrawRectSolid(0,0,0,320,240,BG);
    outline(4,4,312,232,W);
    draw_text(8, 8, .32f, CY, "Code Area");
    C2D_DrawRectSolid(CODE_AREA_X, CODE_AREA_Y, 0, CODE_AREA_W, CODE_AREA_H, C2D_Color32(6,6,8,255));
    outline(CODE_AREA_X, CODE_AREA_Y, CODE_AREA_W, CODE_AREA_H, DG);
    const char* q = e ? e->text : "";
    int row = 0, ln = 0;
    while (*q && row < 16) {
        const char* s = q;
        int len = 0;
        while (q[len] && q[len] != '\n') len++;
        if (!e || ln >= e->scroll_line) {
            char line[96];
            int n = len < 72 ? len : 72;
            memcpy(line, s, n);
            line[n] = 0;
            draw_text(12, 30 + row*11, .26f, G, line);
            row++;
        }
        q += len;
        if (*q == '\n') q++;
        ln++;
    }
    if (controls) C2D_DrawCircleSolid((float)controls->mouse_x, (float)controls->mouse_y, 0, 3.0f, CY);
    if (app && app->show_controls) {
        C2D_DrawRectSolid(20, 30, 0, 280, 178, C2D_Color32(0,0,0,230));
        outline(20, 30, 280, 178, CY);
        draw_text(28, 38, .30f, CY, "Controls");
        draw_text(28, 58, .24f, W, "DPad: arrows | Circle: mouse");
        draw_text(28, 74, .24f, W, "A: click/edit line | B: undo");
        draw_text(28, 90, .24f, W, "X: save | Y: load");
        draw_text(28, 106, .24f, W, "START: run/compile");
        draw_text(28, 122, .24f, W, "SELECT: close controls");
    }
    if (fx && app && app->show_file_overlay) {
        C2D_DrawRectSolid(24, 34, 0, 272, 160, C2D_Color32(0,0,0,230));
        outline(24, 34, 272, 160, Y);
        draw_text(32, 42, .28f, Y, "Project Files");
        for (int i = 0; i < fx->count && i < 8; i++) draw_text(34, 62 + i*14, .24f, W, fx->names[i]);
    }
    if (app) draw_text(8, 224, .27f, W, app->status);
    C3D_FrameEnd(0);
}
