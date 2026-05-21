#include "file_explorer.h"
#include "fs_io.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void file_explorer_init(FileExplorer* fx) { if (fx) memset(fx, 0, sizeof(*fx)); }

bool file_explorer_refresh(FileExplorer* fx) {
    if (!fx) return false;
    fs_make_app_dirs();
    fx->count = 0;
    fx->selected = 0;
    DIR* d = opendir(APP_PROJECT_DIR);
    if (!d) return false;
    struct dirent* de;
    while ((de = readdir(d)) && fx->count < FILE_EXPLORER_MAX_FILES) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
        snprintf(fx->names[fx->count++], FILE_EXPLORER_NAME_MAX, "%s", de->d_name);
    }
    closedir(d);
    return true;
}

static bool ask_filename(char* out, size_t out_size, const char* hint) {
    SwkbdState kbd;
    swkbdInit(&kbd, SWKBD_TYPE_NORMAL, 2, out_size - 1);
    swkbdSetHintText(&kbd, hint);
    swkbdSetButton(&kbd, SWKBD_BUTTON_LEFT, "Cancel", false);
    swkbdSetButton(&kbd, SWKBD_BUTTON_RIGHT, "OK", true);
    return swkbdInputText(&kbd, out, out_size) == SWKBD_BUTTON_RIGHT && out[0];
}

bool file_explorer_save_dialog(FileExplorer* fx, Editor* editor, AppState* app) {
    if (!fx || !editor) return false;
    fs_make_app_dirs();
    char name[FILE_EXPLORER_NAME_MAX] = {0};
    if (!ask_filename(name, sizeof(name), "Save project name")) {
        if (app) app_status(app, "Save cancelled.");
        return false;
    }
    char path[256];
    snprintf(path, sizeof(path), "%s/%s.html", APP_PROJECT_DIR, name);
    if (fs_save_text(path, editor_text(editor))) {
        snprintf(fx->last_path, sizeof(fx->last_path), "%s", path);
        file_explorer_refresh(fx);
        if (app) app_status(app, "Saved: %s.html", name);
        return true;
    }
    if (app) app_status(app, "Save failed.");
    return false;
}

bool file_explorer_load_dialog(FileExplorer* fx, Editor* editor, AppState* app) {
    if (!fx || !editor) return false;
    fs_make_app_dirs();
    file_explorer_refresh(fx);
    char name[FILE_EXPLORER_NAME_MAX] = {0};
    if (!ask_filename(name, sizeof(name), "Load project name")) {
        if (app) app_status(app, "Load cancelled.");
        return false;
    }
    char path[256];
    snprintf(path, sizeof(path), "%s/%s.html", APP_PROJECT_DIR, name);
    char buffer[EDITOR_MAX];
    if (fs_load_text(path, buffer, sizeof(buffer))) {
        editor_set(editor, buffer);
        snprintf(fx->last_path, sizeof(fx->last_path), "%s", path);
        if (app) app_status(app, "Loaded: %s.html", name);
        return true;
    }
    if (app) app_status(app, "Load failed.");
    return false;
}
