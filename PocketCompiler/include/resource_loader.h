#pragma once
#include "app.h"
#include <stdbool.h>
#include <stddef.h>
#define RES_MAX_ITEMS 24
#define RES_MAX_STATUS 96
#define RES_MAX_CACHE_PATH 256
#define RES_MAX_BYTES (1024*1024)
typedef enum{RES_CSS=0,RES_JS,RES_IMAGE,RES_OTHER}ResourceType;
typedef enum{RES_PENDING=0,RES_CACHED,RES_FAILED,RES_TOO_LARGE}ResourceStatus;
typedef struct{ResourceType type;ResourceStatus status;char url[URL_MAX];char cache_path[RES_MAX_CACHE_PATH];char status_text[RES_MAX_STATUS];size_t size_bytes;}ResourceItem;
typedef struct{ResourceItem items[RES_MAX_ITEMS];int count;int css_count;int js_count;int image_count;int other_count;int cached_count;int failed_count;int too_large_count;int truncated_count;}ResourceManifest;
void resource_manifest_init(ResourceManifest* m);
void resource_scan_html(const char* html,ResourceManifest* m);
void resource_fetch_manifest(ResourceManifest* m,size_t max_bytes);
