#pragma once
#include <stdbool.h>
#include <stddef.h>

bool fs_make_app_dir(void);
bool fs_make_cache_dir(void);
bool fs_save_text(const char* path, const char* text);
bool fs_load_text(const char* path, char* out, size_t out_size);
bool fs_save_bytes(const char* path, const char* data, size_t size);
