#include "fs_io.h"
#include "app.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static bool mk(const char* p) {
    if (mkdir(p, 0777) == 0) return true;
    return errno == EEXIST;
}

bool fs_make_app_dirs(void) {
    bool ok = true;
    ok = mk("sdmc:/3ds") && ok;
    ok = mk(APP_SD_DIR) && ok;
    ok = mk(APP_PROJECT_DIR) && ok;
    return ok;
}

bool fs_save_text(const char* path, const char* text) {
    FILE* f = fopen(path, "wb");
    if (!f) return false;
    if (text) {
        size_t n = strlen(text);
        if (fwrite(text, 1, n, f) != n) {
            fclose(f);
            return false;
        }
    }
    return fclose(f) == 0;
}

bool fs_load_text(const char* path, char* out, size_t out_size) {
    if (!out || !out_size) return false;
    FILE* f = fopen(path, "rb");
    if (!f) {
        out[0] = 0;
        return false;
    }
    size_t n = fread(out, 1, out_size - 1, f);
    out[n] = 0;
    bool ok = !ferror(f);
    fclose(f);
    return ok;
}
