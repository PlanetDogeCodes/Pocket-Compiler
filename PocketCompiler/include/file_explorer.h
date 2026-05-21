#pragma once
#include "app.h"
#include "editor.h"
#include <stdbool.h>

#define FILE_EXPLORER_MAX_FILES 32
#define FILE_EXPLORER_NAME_MAX 128

typedef struct {
    char names[FILE_EXPLORER_MAX_FILES][FILE_EXPLORER_NAME_MAX];
    int count;
    int selected;
    char last_path[256];
} FileExplorer;

void file_explorer_init(FileExplorer* fx);
bool file_explorer_refresh(FileExplorer* fx);
bool file_explorer_save_dialog(FileExplorer* fx, Editor* editor, AppState* app);
bool file_explorer_load_dialog(FileExplorer* fx, Editor* editor, AppState* app);
