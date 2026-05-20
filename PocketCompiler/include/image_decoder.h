#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    IMAGE_KIND_UNKNOWN = 0,
    IMAGE_KIND_PNG,
    IMAGE_KIND_JPEG,
    IMAGE_KIND_GIF,
    IMAGE_KIND_BMP
} ImageKind;

typedef struct {
    ImageKind kind;
    int width;
    int height;
    int bits_per_pixel;
    bool decoded_metadata;
} ImageInfo;

bool image_decode_metadata(const unsigned char* data, size_t size, ImageInfo* out);
const char* image_kind_name(ImageKind kind);
