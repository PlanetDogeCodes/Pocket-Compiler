#pragma once
#include <stdbool.h>
#include <stddef.h>

bool fs_make_app_dirs(void);
bool fs_save_text(const char* path, const char* text);
bool fs_load_text(const char* path, char* out, size_t out_size);
