#pragma once
#include "app.h"

typedef struct {
    char text[EDITOR_MAX];
    char undo_text[UNDO_MAX];
    size_t len;
    size_t cursor;
    int scroll_line;
    int clicked_line;
} Editor;

void editor_init(Editor* e);
void editor_set(Editor* e, const char* s);
void editor_snapshot(Editor* e);
bool editor_undo(Editor* e);
bool editor_insert(Editor* e, const char* s);
bool editor_backspace(Editor* e);
void editor_move_up(Editor* e);
void editor_move_down(Editor* e);
void editor_move_left(Editor* e);
void editor_move_right(Editor* e);
int editor_line_from_y(const Editor* e, int y);
bool editor_replace_line(Editor* e, int line, const char* replacement);
bool editor_get_line(const Editor* e, int line, char* out, size_t out_size);
const char* editor_text(const Editor* e);
