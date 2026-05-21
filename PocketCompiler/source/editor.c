#include "editor.h"
#include <stdio.h>
#include <string.h>

void editor_init(Editor* e) {
    if (!e) return;
    memset(e, 0, sizeof(*e));
    e->clicked_line = -1;
}

void editor_snapshot(Editor* e) {
    if (!e) return;
    strncpy(e->undo_text, e->text, UNDO_MAX - 1);
    e->undo_text[UNDO_MAX - 1] = 0;
}

void editor_set(Editor* e, const char* s) {
    if (!e) return;
    editor_snapshot(e);
    if (!s) s = "";
    strncpy(e->text, s, EDITOR_MAX - 1);
    e->text[EDITOR_MAX - 1] = 0;
    e->len = strlen(e->text);
    e->cursor = e->len;
    e->scroll_line = 0;
}

bool editor_undo(Editor* e) {
    if (!e || !e->undo_text[0]) return false;
    strncpy(e->text, e->undo_text, EDITOR_MAX - 1);
    e->text[EDITOR_MAX - 1] = 0;
    e->len = strlen(e->text);
    if (e->cursor > e->len) e->cursor = e->len;
    return true;
}

bool editor_insert(Editor* e, const char* s) {
    if (!e || !s) return false;
    size_t n = strlen(s);
    if (!n || e->len + n >= EDITOR_MAX) return false;
    editor_snapshot(e);
    if (e->cursor > e->len) e->cursor = e->len;
    memmove(e->text + e->cursor + n, e->text + e->cursor, e->len - e->cursor + 1);
    memcpy(e->text + e->cursor, s, n);
    e->cursor += n;
    e->len += n;
    e->text[e->len] = 0;
    return true;
}

bool editor_backspace(Editor* e) {
    if (!e || !e->cursor || !e->len) return false;
    editor_snapshot(e);
    if (e->cursor > e->len) e->cursor = e->len;
    memmove(e->text + e->cursor - 1, e->text + e->cursor, e->len - e->cursor + 1);
    e->cursor--;
    e->len--;
    e->text[e->len] = 0;
    return true;
}

void editor_move_left(Editor* e) { if (e && e->cursor > 0) e->cursor--; }
void editor_move_right(Editor* e) { if (e && e->cursor < e->len) e->cursor++; }
void editor_move_up(Editor* e) { if (e && e->scroll_line > 0) e->scroll_line--; }
void editor_move_down(Editor* e) { if (e) e->scroll_line++; }

int editor_line_from_y(const Editor* e, int y) {
    if (!e) return -1;
    if (y < CODE_AREA_Y || y >= CODE_AREA_Y + CODE_AREA_H) return -1;
    return e->scroll_line + (y - CODE_AREA_Y) / 11;
}

bool editor_get_line(const Editor* e, int line, char* out, size_t out_size) {
    if (!e || !out || !out_size || line < 0) return false;
    out[0] = 0;
    const char* p = e->text;
    int current = 0;
    while (*p && current < line) {
        if (*p == '\n') current++;
        p++;
    }
    if (current != line) return false;
    size_t i = 0;
    while (*p && *p != '\n' && i + 1 < out_size) out[i++] = *p++;
    out[i] = 0;
    return true;
}

bool editor_replace_line(Editor* e, int line, const char* replacement) {
    if (!e || line < 0 || !replacement) return false;
    editor_snapshot(e);
    char result[EDITOR_MAX];
    result[0] = 0;
    const char* p = e->text;
    int current = 0;
    bool replaced = false;
    while (*p) {
        const char* start = p;
        while (*p && *p != '\n') p++;
        size_t len = (size_t)(p - start);
        if (current == line) {
            strncat(result, replacement, sizeof(result) - strlen(result) - 1);
            replaced = true;
        } else {
            size_t room = sizeof(result) - strlen(result) - 1;
            strncat(result, start, len < room ? len : room);
        }
        if (*p == '\n') {
            strncat(result, "\n", sizeof(result) - strlen(result) - 1);
            p++;
        }
        current++;
    }
    if (!replaced && current == line) {
        strncat(result, replacement, sizeof(result) - strlen(result) - 1);
        strncat(result, "\n", sizeof(result) - strlen(result) - 1);
        replaced = true;
    }
    if (!replaced) return false;
    strncpy(e->text, result, EDITOR_MAX - 1);
    e->text[EDITOR_MAX - 1] = 0;
    e->len = strlen(e->text);
    e->cursor = e->len;
    return true;
}

const char* editor_text(const Editor* e) { return e ? e->text : ""; }
