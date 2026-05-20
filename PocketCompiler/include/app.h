#pragma once
#include <3ds.h>
#include <stdbool.h>
#include <stddef.h>

#define APP_SD_DIR "sdmc:/3ds/PocketCompiler"
#define APP_CACHE_DIR "sdmc:/3ds/PocketCompiler/cache"
#define APP_FILE "sdmc:/3ds/PocketCompiler/index.html"

#define EDITOR_MAX 65536
#define PREVIEW_TEXT_MAX 12288
#define URL_MAX 512
#define MAX_URLS 32
#define TOP_W 400
#define TOP_H 240
#define BOT_W 320
#define BOT_H 240

typedef struct {
    char status[256];
    bool running;
    bool dirty;
} AppState;

void app_status(AppState* app, const char* fmt, ...);
