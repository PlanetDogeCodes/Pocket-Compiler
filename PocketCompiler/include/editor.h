#pragma once
#include "app.h"
typedef struct{char text[EDITOR_MAX];size_t len;size_t cursor;int scroll_line;}Editor;
void editor_init(Editor* e);
void editor_set(Editor* e,const char* s);
bool editor_insert(Editor* e,const char* s);
bool editor_backspace(Editor* e);
void editor_left(Editor* e);
void editor_right(Editor* e);
const char* editor_text(const Editor* e);
